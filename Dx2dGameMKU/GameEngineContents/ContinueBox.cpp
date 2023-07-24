#include "PrecompileHeader.h"
#include "ContinueBox.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>


#include "RCGEnums.h"
#include "RCG_GameCore.h"
#include "RCGDefine.h"
#include "FontMgr.h"
#include "KeyMgr.h"
#include "LevelMgr.h"
#include "SoundMgr.h"

#include "UIFontRenderer.h"
#include "Fader.h"
#include "FieldLevelBase.h"

const std::vector<std::string_view> ContinueBox::Box_Textures =
{
	"UI_Continue_Background_Drip_01.png",
	"UI_Continue_Background_Drip_02.png",
	"UI_Continue_Background_Drip_03.png",
	"UI_Continue_Background_Drip_04.png",
	"UI_Continue_Background_Drip_05.png",
	"UI_Continue_Background_Drip_06.png",
	"UI_Continue_Background_Drip_07.png",
	"UI_Continue_Background_Drip_08.png",
	"UI_Continue_Background_Drip_09.png",
};

const std::string_view ContinueBox::Cursor_FileName = "Continue_Select.png";

const float4 ContinueBox::CursorOffsets[2] =
{
	float4{-200.f, 0.f},
	float4{200.f, 0.f},
};

const std::pair<float4, float4> ContinueBox::MoveOffsets =
{
	float4{0.f, -700.f},
	float4{0.f, 0.f},
};

GameEngineTime ContinueBox::NewTime;
const float ContinueBox::MoveDuration = 0.5f;

ContinueBox::ContinueBox()
{
	FieldLevelBase::GetPtr()->OffPhone();
}

ContinueBox::~ContinueBox()
{
	FieldLevelBase::GetPtr()->OnPhone();
}


void ContinueBox::Start() 
{
	UIBase::Start();

	LoadResImage();
	CreateRenders();
	CreateTexts();

	GameEngineTime::GlobalTime.SetGlobalTimeScale(0.f);
	NewTime.Reset();

	RCG_GameCore::SetCurGameState(GameState::PlayerKO);
	SoundMgr::BgmPauseOn();
	SoundMgr::PlaySFX("ContinueOpen.wav");
}

void ContinueBox::LoadResImage()
{
	if (nullptr != GameEngineTexture::Find(Cursor_FileName))
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("UI");
	Dir.Move("Continue");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}
}


void ContinueBox::CreateRenders()
{
	BoxRender = CreateComponent<GameEngineUIRenderer>(FieldUIRenderOrder::Continue);
	BoxRender->SetScaleToTexture(Box_Textures[BoxAniIndex]);
	
	CursorRender = CreateComponent<GameEngineUIRenderer>(FieldUIRenderOrder::Continue);
	CursorRender->SetScaleToTexture(Cursor_FileName);
	CursorRender->GetTransform()->SetLocalPosition(CursorOffsets[CursorIndex]);
}


void ContinueBox::CreateTexts()
{
	const float4 TitleOffset = float4{ 0.f, 250.f };

	std::shared_ptr<UIFontRenderer> TitleRender = nullptr;
	TitleRender = CreateComponent<UIFontRenderer>(FieldUIRenderOrder::Continue);
	TitleRender->SetFont(FontMgr::GetFontName(FontType::Binggrae));
	TitleRender->SetScale(100);
	TitleRender->SetText("재도전?");
	TitleRender->SetColor(float4::White);
	TitleRender->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
	TitleRender->GetTransform()->SetLocalPosition(TitleOffset);


	LeftSelectRender = CreateComponent<UIFontRenderer>(FieldUIRenderOrder::Continue);
	LeftSelectRender->SetFont(FontMgr::GetFontName(FontType::Binggrae));
	LeftSelectRender->SetScale(60);
	LeftSelectRender->SetText("계속하기");
	LeftSelectRender->SetColor(float4::White);
	LeftSelectRender->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
	LeftSelectRender->GetTransform()->SetLocalPosition(CursorOffsets[0]);


	RightSelectRender = CreateComponent<UIFontRenderer>(FieldUIRenderOrder::Continue);
	RightSelectRender->SetFont(FontMgr::GetFontName(FontType::Binggrae));
	RightSelectRender->SetScale(60);
	RightSelectRender->SetText("포기하기");
	RightSelectRender->SetColor(float4::Black);
	RightSelectRender->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
	RightSelectRender->GetTransform()->SetLocalPosition(CursorOffsets[1]);
}

void ContinueBox::Update(float _DeltaTime) 
{
	UIBase::Update(0.f);

	float DeltaTime = NewTime.TimeCheck(); 
	NewLiveTime += DeltaTime;

	switch (CurState)
	{
	case ContinueBox::State::Raise:
		Update_Raise();
		break;
	case ContinueBox::State::Wait:
		Update_BoxAni(DeltaTime);
		Update_Wait();
		break;
	case ContinueBox::State::Sink:
		Update_Sink();
		break;
	}
}

void ContinueBox::Update_Raise()
{
	if (false == Update_Move(MoveOffsets.first, MoveOffsets.second))
		return;

	CurState = State::Wait;
	NewLiveTime = 0.f;
}

void ContinueBox::Update_BoxAni(float _DeltaTime)
{
	static const float AniDuration = 0.1f;
	
	BoxAniTimer += _DeltaTime;
	if (BoxAniTimer < AniDuration)
		return;
	
	BoxAniTimer = 0.f;

	if (Box_Textures.size() <= BoxAniIndex)
		return;
	
	BoxRender->SetScaleToTexture(Box_Textures[BoxAniIndex++]);
}

void ContinueBox::Update_Wait() 
{
	bool IsCursorMoved = false;
	if (true == KeyMgr::IsDown(KeyNames::LeftArrow))
	{
		CursorIndex = (CursorIndex == 0) ? 1 : 0;
		IsCursorMoved = true;
	}
	else if (true == KeyMgr::IsDown(KeyNames::RightArrow))
	{
		CursorIndex = (CursorIndex + 1) % 2;
		IsCursorMoved = true;
	}

	if (true == IsCursorMoved)
	{
		CursorRender->GetTransform()->SetLocalPosition(CursorOffsets[CursorIndex]);
		if (0 == CursorIndex)
		{
			LeftSelectRender->SetColor(float4::White);
			RightSelectRender->SetColor(float4::Black);
		}
		else
		{
			LeftSelectRender->SetColor(float4::Black);
			RightSelectRender->SetColor(float4::White);
		}

		SoundMgr::PlaySFX("Continue_CursorMove.wav");
		return;
	}
	
	bool IsSelected = false;
	IsSelected |= KeyMgr::IsDown(KeyNames::Z);
	IsSelected |= KeyMgr::IsDown(KeyNames::X);
	IsSelected |= KeyMgr::IsDown(KeyNames::C);

	if (false == IsSelected)
		return;

	CurState = State::Sink;
	NewLiveTime = 0.f;

	if (0 == CursorIndex)
	{
		SoundMgr::PlaySFX("Continue_Retry.wav");
	}
	else
	{
		SoundMgr::PlaySFX("Continue_Stop.wav");
	}
}

void ContinueBox::Update_Sink()
{
	if (false == Update_Move(MoveOffsets.second, MoveOffsets.first))
		return;

	if (0 == CursorIndex)
	{
		if (nullptr == ContinueCallBack)
		{
			MsgAssert("컨티뉴를 선택할 시 해야할 작업을 등록해주지 않았습니다");
		}
		else
		{
			ContinueCallBack();
		}
	}
	else
	{
		std::shared_ptr<Fader> Fade = nullptr;
		Fade = GetLevel()->CreateActor<Fader>(UpdateOrder::UI);
		Fade->Init(float4::Null, 0.5f, []()
		{
			LevelMgr::ChangeLevel(LevelNames::EndingLevel_Lose);
		});

		Fade->DontDestory();
	}

	GameEngineTime::GlobalTime.SetGlobalTimeScale(1.f);
	RCG_GameCore::SetCurGameState(GameState::OnField);
	SoundMgr::BgmPauseOff();
	Death();
}

bool ContinueBox::Update_Move(const float4& _Start, const float4& _Dest)
{
	float Ratio = (NewLiveTime / MoveDuration);
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	float SinValue = sinf(GameEngineMath::PIE * 0.5f * ClampRatio);

	float4 NextPos = float4::Lerp(_Start, _Dest, SinValue);
	GetTransform()->SetLocalPosition(NextPos);

	return (1.f <= Ratio);
}