#include "PrecompileHeader.h"
#include "EndingLoseActor.h"

#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "FontMgr.h"
#include "RCGEnums.h"
#include "RCGDefine.h"
#include "GUIManager.h"
#include "SoundMgr.h"

#include "UIFontRenderer.h"
#include "PlayerState_KnockDown.h"
#include "GameEngineActorGUI.h"

const float4 EndingLoseActor::TextPos = float4{ 0.f, 200.f };

EndingLoseActor::EndingLoseActor()
{

}

EndingLoseActor::~EndingLoseActor()
{

}


void EndingLoseActor::Start() 
{
	GameEngineActor::Start();

	LoadImgRes();
	CreateRenders();
}


void EndingLoseActor::LoadImgRes()
{
	if (nullptr == GameEngineSprite::Find(PlayerState_KnockDown::AniFileName))
	{
		GameEngineDirectory Dir;
		RCGDefine::MoveContentPath(Dir, ResType::Image);
		Dir.Move("Character");
		Dir.Move("Player");
		Dir.Move("Damaged");
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName(PlayerState_KnockDown::AniFileName).GetFullPath(), 5, 10);
	}

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	Dir.Move("Ending_Lose");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({".png"});
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}
}



void EndingLoseActor::CreateRenders()
{
	std::shared_ptr<GameEngineSpriteRenderer> BackGround = nullptr;
	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->ColorOptionValue.MulColor = float4{ 0.f,0.f, 0.f , 1.f };
	GameEngineTransform* BackGroundTrans = BackGround->GetTransform();
	BackGroundTrans->SetWorldPosition(float4::Zero);
	BackGroundTrans->SetWorldScale(GameEngineWindow::GetScreenSize());


	const std::string_view Light_FileName = "EndingLose_StopLight.png";
	const float4 PlayerScale = float4{ 1000.f, 1000.f };
	const float4 PlayerOffset = float4{ 0.f, -300.f };

	Player = CreateComponent<GameEngineSpriteRenderer>();
	Player->CreateAnimation
	({
		.AnimationName = PlayerState_KnockDown::AniFileName,
		.SpriteName = PlayerState_KnockDown::AniFileName,
		.Start = 30,
		.End = 49,
		.FrameInter = 0.07f,
		.Loop = false,
	});
	Player->ChangeAnimation(PlayerState_KnockDown::AniFileName);

	GameEngineTransform* PlayerTrans = Player->GetTransform();
	PlayerTrans->SetLocalScale(PlayerScale);
	PlayerTrans->SetLocalPosition(PlayerOffset);
	Player->ColorOptionValue.MulColor.a = 0.1f;
	Player->SetAnimPauseOn();



	const float4 LightOffset = float4{ 0.f, 0.f };

	Light = CreateComponent<GameEngineSpriteRenderer>();
	Light->SetScaleToTexture("EndingLose_StopLight.png");
	GameEngineTransform* LightTrans = Light->GetTransform();
	LightTrans->SetLocalPosition(LightOffset);
	Light->Off();


	Text = CreateComponent<UIFontRenderer>();
	Text->SetFont(FontMgr::GetFontName(FontType::Binggrae));
	Text->SetScale(80);
	Text->SetText("Game Over");
	Text->SetColor(float4::Null);
	Text->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
	Text->Off();
}


void EndingLoseActor::Update(float _DeltaTime)
{
	GameEngineActor::Update(_DeltaTime);

	switch (CurState)
	{
	case EndingLoseActor::State::EnterWait:
		Update_EnterWait(_DeltaTime);
		break;
	case EndingLoseActor::State::MovePlayer:
		Update_MovePlayer(_DeltaTime);
		break;
	case EndingLoseActor::State::MoveText:
		Update_MoveText(_DeltaTime);
		break;
	case EndingLoseActor::State::ExitWait:
		Update_ExitWait(_DeltaTime);
		break;
	}
}


void EndingLoseActor::Update_EnterWait(float _DeltaTime)
{
	static const float Duration = 3.0f;
	if (GetLiveTime() < Duration)
		return;

	ResetLiveTime();
	CurState = State::MovePlayer;

	Player->ColorOptionValue.MulColor = float4{ 1.f, 1.f, 1.f, 1.f };
	Player->SetAnimPauseOff();
	Light->On();
}

void EndingLoseActor::Update_MovePlayer(float _DeltaTime)
{
	if (false == Player->IsAnimationEnd())
		return;

	ResetLiveTime();
	CurState = State::MoveText;

	Text->On();
	Text->SetColor(float4::Null);
}

void EndingLoseActor::Update_MoveText(float _DeltaTime)
{
	static const float Duration = 1.f;
	float Ratio = GetLiveTime() / Duration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	float SinValue = sinf(GameEngineMath::PIE * 0.5f * ClampRatio);

	float4 NextPos = float4::Lerp(float4::Zero, TextPos, SinValue);
	float4 Color = float4::White;
	Color.a = SinValue;

	Text->GetTransform()->SetLocalPosition(NextPos);
	Text->SetColor(Color);

	if (Ratio < 1.f)
		return;

	ResetLiveTime();
	CurState = State::ExitWait;
	SoundMgr::BgmFadeOut(3.f);
}

void EndingLoseActor::Update_ExitWait(float _DeltaTime) 
{
	static const float Duration = 3.f;
	float Ratio = GetLiveTime() / Duration;

	float4 Color = float4::LerpClamp(float4::White, float4::Null, Ratio);
	Text->SetColor(Color);
	Light->ColorOptionValue.MulColor = Color;
	Player->ColorOptionValue.MulColor = Color;

	if (Ratio < 1.f)
		return;

	GameEngineWindow::AppOff();
}


void EndingLoseActor::SetGuiTarget(GameEngineTransform* _Target)
{
	MsgTextBox("EndingLoseActor에서 TransformGUI를 실행합니다");
	GUIManager::CreateGui<GameEngineActorGUI>()->SetTarget(_Target);
}

