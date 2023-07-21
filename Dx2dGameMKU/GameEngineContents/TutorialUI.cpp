#include "PrecompileHeader.h"
#include "TutorialUI.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineUIRenderer.h>


#include "RCGDefine.h"
#include "RCGEnums.h"
#include "FontMgr.h"
#include "KeyMgr.h"
#include "RCG_GameCore.h"
#include "SoundMgr.h"

#include "UIFontRenderer.h"
#include "FieldLevelBase.h"


GameEngineTime TutorialUI::NewTime;

const std::vector<std::string_view> TutorialUI::TexFileNames =
{
	"TutorialBox0.png",
	"TutorialBox1.png",
};

const float4 TutorialUI::MoveStart = float4{ -900.f, -190.f };
const float4 TutorialUI::MoveDest = float4{ -388.f, -190.f };


TutorialUI::TutorialUI()
{
	if (nullptr != TutorialPtr)
	{
		MsgAssert("2개 이상의 튜토리얼UI가 동시에 켜져있습니다");
		return;
	}

	TutorialPtr = this;
}

TutorialUI::~TutorialUI()
{
	if (this != TutorialPtr)
	{
		MsgAssert("2개 이상의 튜토리얼UI가 동시에 켜져있습니다");
		return;
	}

	TutorialPtr = nullptr;
}


void TutorialUI::Start() 
{
	UIBase::Start();

	LoadImgRes();
	CreateRenders();

	RCG_GameCore::SetCurGameState(GameState::Tutorial);
	GameEngineTime::GlobalTime.SetGlobalTimeScale(0.f);
	NewTime.Reset();

	FieldLevelBase::GetPtr()->OffPhone();
	SoundMgr::PlaySFX("Tutorial.wav");
}


void TutorialUI::LoadImgRes()
{
	if (nullptr != GameEngineTexture::Find(TexFileNames.front()))
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("UI");
	Dir.Move("Tutorial");
	for (size_t i = 0; i < TexFileNames.size(); ++i)
	{
		GameEnginePath Path =  Dir.GetPlusFileName(TexFileNames[i]);
		GameEngineTexture::Load(Path.GetFullPath());
	}
}



void TutorialUI::CreateRenders()
{
	//Back Image
	{
		BoxRender = CreateComponent<GameEngineUIRenderer>(FieldUIRenderOrder::Tutorial);
		BoxRender->SetScaleToTexture(TexFileNames.front());
	}

	//Title Text
	{
		const float4 Offset = float4{ -250.f, 60.f };

		TitleRender = CreateComponent<UIFontRenderer>(FieldUIRenderOrder::Tutorial);
		TitleRender->SetFont(FontMgr::GetFontName(FontType::Binggrae));
		TitleRender->SetScale(30);
		TitleRender->SetColor(float4::White);
		TitleRender->SetFontFlag(FW1_TEXT_FLAG::FW1_LEFT);

		TitleRender->GetTransform()->SetLocalPosition(Offset);
	}
	
	//Description Text
	{
		const float4 Offset = float4{ -240.f, -6.f };

		DescRender = CreateComponent<UIFontRenderer>(FieldUIRenderOrder::Tutorial);
		DescRender->SetFont(FontMgr::GetFontName(FontType::NanumSquare));
		DescRender->SetScale(20);
		DescRender->SetColor(float4::Black);
		DescRender->SetFontFlag(FW1_TEXT_FLAG::FW1_LEFT);

		DescRender->GetTransform()->SetLocalPosition(Offset);
	}
}



void TutorialUI::Init(const std::string_view& _Title, const std::string_view& _Desc)
{
	TitleRender->SetText(_Title);
	DescRender->SetText(_Desc);
}



void TutorialUI::Update(float _DeltaTime) 
{
	UIBase::Update(0.f);

	if (true == KeyMgr::IsDown(KeyNames::Esc))
	{
		Death();
		return;
	}

	const float DeltaTime = NewTime.TimeCheck();
	Update_Ani(DeltaTime);

	switch (CurState)
	{
	case TutorialUI::State::MoveIn:
		Update_MoveIn(DeltaTime);
		break;
	case TutorialUI::State::Wait:
		Update_Wait(DeltaTime);
		break;
	case TutorialUI::State::MoveOut:
		Update_MoveOut(DeltaTime);
		break;
	}
}

void TutorialUI::Update_Ani(float _DeltaTime)
{
	AniTimer += _DeltaTime;
	if (AniTimer < AniDuration)
		return;

	AniTimer = 0.f;
	++TexIndex;
	BoxRender->SetScaleToTexture(TexFileNames[TexIndex % 2]);
}

void TutorialUI::Update_MoveIn(float _DeltaTime)
{
	if (false == Update_Move(_DeltaTime, MoveStart, MoveDest))
		return;

	CurState = State::Wait;
}



void TutorialUI::Update_Wait(float _DeltaTime)
{
	MoveTimer += _DeltaTime;
	if (MoveTimer < WaitDuration)
		return;

	MoveTimer = 0.f;
	CurState = State::MoveOut;
}

void TutorialUI::Update_MoveOut(float _DeltaTime) 
{
	if (false == Update_Move(_DeltaTime, MoveDest, MoveStart))
		return;

	Death();
}


bool TutorialUI::Update_Move(float _DeltaTime, const float4& _Start, const float4& _Dest)
{
	MoveTimer += _DeltaTime;
	float Ratio = (MoveTimer / MoveDuration);
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	float SinValue = sinf(GameEngineMath::PIE * 0.5f * ClampRatio);

	float4 NextPos = float4::Lerp(_Start, _Dest, SinValue);
	GetTransform()->SetLocalPosition(NextPos);

	if (Ratio < 1.f)
		return false;

	MoveTimer = 0.f;
	return true;
}



void TutorialUI::Destroy()
{
	UIBase::Destroy();

	GameEngineTime::GlobalTime.SetGlobalTimeScale(1.f);
	RCG_GameCore::SetCurGameState(GameState::OnField);
	FieldLevelBase::GetPtr()->OnPhone(1.f);
}