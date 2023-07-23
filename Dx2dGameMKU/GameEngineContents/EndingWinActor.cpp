#include "PrecompileHeader.h"
#include "EndingWinActor.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "FontMgr.h"
#include "SoundMgr.h"

#include "GUIManager.h"
#include "GameEngineActorGUI.h"
#include "Fader.h"


const std::string_view EndingWinActor::Background_FileName = "EndingWin_Background";

const std::string_view EndingWinActor::KyokoTexNames[2] =
{
	"EndingWin_Kyoko1.png",
	"EndingWin_Kyoko2.png",
};

const std::string_view EndingWinActor::MisakoTexNames[2] = 
{
	"EndingWin_Misako1.png",
	"EndingWin_Misako2.png",
};

const std::string_view EndingWinActor::What_FileName = "EndingWin_What";

EndingWinActor::EndingWinActor()
{

}

EndingWinActor::~EndingWinActor()
{

}


void EndingWinActor::Start() 
{
	GameEngineActor::Start();

	LoadImgRes();
	CreateRenders();
}


void EndingWinActor::LoadImgRes()
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	Dir.Move("Ending_Win");

	GameEnginePath BackgroundFile = Dir.GetPlusFileName(Background_FileName);
	GameEnginePath WhatUIFile = Dir.GetPlusFileName(What_FileName);
	Dir.Move("EndingWin_Character");

	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}

	GameEngineSprite::LoadFolder(BackgroundFile.GetFullPath());
	GameEngineSprite::LoadFolder(WhatUIFile.GetFullPath());
}

void EndingWinActor::CreateRenders()
{
	CreateBackground();
	CreateCharacters();
	CreateEffects();
	CreateText();
}

void EndingWinActor::CreateBackground()
{
	BackGround = CreateComponent<GameEngineSpriteRenderer>();
	BackGround->CreateAnimation
	({
		.AnimationName = Background_FileName,
		.SpriteName = Background_FileName,
		.FrameInter = 0.04f,
		.Loop = false,
		.ScaleToImage = true,
	});

	BackGround->ChangeAnimation(Background_FileName);
	BackGround->SetAnimPauseOn();
}


void EndingWinActor::CreateCharacters()
{
	const float4 KyokoOffset = float4{ -435.f, -130.f };
	const float4 MisakoOffset = float4{ 454.f, -175.f };

	Kyoko = CreateComponent<GameEngineSpriteRenderer>();
	Kyoko->SetScaleToTexture(KyokoTexNames[0]);
	Misako = CreateComponent<GameEngineSpriteRenderer>();
	Misako->SetScaleToTexture(MisakoTexNames[0]);

	GameEngineTransform* KyokoTrans = Kyoko->GetTransform();
	GameEngineTransform* MisakoTrans = Misako->GetTransform();

	KyokoTrans->SetLocalPosition(KyokoOffset);
	MisakoTrans->SetLocalPosition(MisakoOffset);
}

void EndingWinActor::CreateEffects() 
{
	const float4 SpeechOffset = float4{ 50.f, 100.f };

	WhatSpeech = CreateComponent<GameEngineSpriteRenderer>();
	WhatSpeech->CreateAnimation
	({
		.AnimationName = What_FileName,
		.SpriteName = What_FileName,
		.FrameInter = 0.07f,
		.Loop = false,
		.ScaleToImage = true,
	});

	WhatSpeech->ChangeAnimation(What_FileName);
	GameEngineTransform* SpeechTrans = WhatSpeech->GetTransform();
	SpeechTrans->SetLocalPosition(SpeechOffset);
	WhatSpeech->Off();

	RingEffect = CreateEffect("EndingWin_Ring.png", Kyoko, { -560.f, 25.f });
	SleepEffect = CreateEffect("EndingWin_Sleep.png", Misako, { 500.f, 60.f });
	AwakeEffect = CreateEffect("EndingWin_Awake.png", Kyoko, { 530.f, 60.f });

	SleepEffect->On();
}

std::shared_ptr<GameEngineSpriteRenderer> EndingWinActor::CreateEffect(
	const std::string_view& _TexName,
	std::shared_ptr<GameEngineSpriteRenderer> _Parent,
	const float4& _Offset,
	bool _IsGui /*= false*/)
{
	std::shared_ptr<GameEngineSpriteRenderer> Effect = nullptr;
	Effect = CreateComponent<GameEngineSpriteRenderer>();
	Effect->SetScaleToTexture(_TexName);

	GameEngineTransform* EffectTrans = Effect->GetTransform();
	EffectTrans->SetLocalPosition(_Offset);
	EffectTrans->SetParent(_Parent->GetTransform());
	Effect->Off();

	if (true == _IsGui)
	{
		EffectTrans->SetParent(GetTransform());
		SetGuiTarget(EffectTrans);
	}

	return Effect;
}


void EndingWinActor::CreateText()
{
	const float4 Offset = float4{ 0.f, 220.f };

	ThankMsg = CreateComponent<GameEngineFontRenderer>();

	ThankMsg->SetFont(FontMgr::GetFontName(FontType::Binggrae));
	ThankMsg->SetScale(80);
	ThankMsg->SetText("Thank you for playing");
	ThankMsg->SetColor(float4{1.f, 1.f, 1.f, 0.f});
	ThankMsg->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);

	ThankMsg->GetTransform()->SetLocalPosition(Offset);
}


void EndingWinActor::Update(float _DeltaTime)
{
	GameEngineActor::Update(_DeltaTime);

	switch (CurState)
	{
	case EndingWinActor::State::MsgFadeIn:
		Update_MsgFadeIn(_DeltaTime);
		break;
	case EndingWinActor::State::MsgFadeOut:
		Update_MsgFadeOut(_DeltaTime);
		break;
	case EndingWinActor::State::Ring:
		Update_Ring(_DeltaTime);
		break;
	case EndingWinActor::State::Scream:
		Update_Scream(_DeltaTime);
		break;
	case EndingWinActor::State::GameEnd:
		
		break;
	}
}


void EndingWinActor::Update_MsgFadeIn(float _DeltaTime) 
{
	static const float Duration = 2.5f;

	float Ratio = GetLiveTime() / Duration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	float4 Color = float4::White;
	Color.a = ClampRatio;
	ThankMsg->SetColor(Color);

	if (Ratio < 1.f)
		return;

	ResetLiveTime();
	CurState = State::MsgFadeOut;
}

void EndingWinActor::Update_MsgFadeOut(float _DeltaTime)
{
	static const float Duration = 1.f;

	float Ratio = GetLiveTime() / Duration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	float4 Color = float4::White;
	Color.a = (1.f - ClampRatio);
	ThankMsg->SetColor(Color);

	if (Ratio < 1.f)
		return;

	ResetLiveTime();
	CurState = State::Ring;

	RingEffect->On();
}


void EndingWinActor::Update_Ring(float _DeltaTime)
{
	static const float Duration = 1.f;

	if (GetLiveTime() < Duration)
		return;

	ResetLiveTime();
	CurState = State::Scream;

	RingEffect->Off();
	SleepEffect->Off();
	AwakeEffect->On();
	WhatSpeech->On();

	Kyoko->SetScaleToTexture(KyokoTexNames[1]);
	Misako->SetScaleToTexture(MisakoTexNames[1]);

	BackGround->SetAnimPauseOff();

	KyokoOriginPos = Kyoko->GetTransform()->GetLocalPosition();
	MisakoOriginPos = Misako->GetTransform()->GetLocalPosition();
}

void EndingWinActor::Update_Scream(float _DeltaTime)
{
	static const float ShakeRange = 10.f;

	GameEngineTransform* KyokoTrans = Kyoko->GetTransform();
	GameEngineTransform* MisakoTrans = Misako->GetTransform();
	
	float XOffset = GameEngineRandom::MainRandom.RandomFloat(-ShakeRange, ShakeRange);
	float YOffset = GameEngineRandom::MainRandom.RandomFloat(-ShakeRange, ShakeRange);

	KyokoTrans->SetLocalPosition(KyokoOriginPos + float4{ XOffset , YOffset });
	MisakoTrans->SetLocalPosition(MisakoOriginPos + float4{ XOffset , YOffset });

	if (false == BackGround->IsAnimationEnd())
		return;

	ResetLiveTime();
	CurState = State::GameEnd;

	static const float FadeTime = 2.f;
	std::shared_ptr<Fader> Fade = nullptr;
	Fade = GetLevel()->CreateActor<Fader>(UpdateOrder::UI);
	Fade->Init(float4::Null, FadeTime, []()
	{
		GameEngineWindow::AppOff();
	});
	Fade->DontDestory();

	KyokoTrans->SetLocalPosition(KyokoOriginPos);
	MisakoTrans->SetLocalPosition(MisakoOriginPos);
	SoundMgr::BgmFadeOut(FadeTime);
}



void EndingWinActor::SetGuiTarget(class GameEngineTransform* _Target)
{
	MsgTextBox("EndingWinActor에서 TransformGUI를 실행합니다");
	GUIManager::CreateGui<GameEngineActorGUI>()->SetTarget(_Target);
}