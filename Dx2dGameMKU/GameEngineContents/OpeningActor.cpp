#include "PrecompileHeader.h"
#include "OpeningActor.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "RCGDefine.h"
#include "KeyMgr.h"
#include "LevelMgr.h"
#include "RCGEnums.h"

#include "Fader.h"

OpeningActor::OpeningActor()
{

}

OpeningActor::~OpeningActor()
{

}

void OpeningActor::Start()
{
	//배경
	CreateBackImage();

	//캐릭터 렌더러 생성
	CreateCharecters();

	//배경 테두리 프레임
	CreateFrame();

	//텍스트 렌더러 생성
	CreateTitles();

	//비디오가 끝나고 나오는 배경화면
	CraeteBrightImages();
}


void OpeningActor::CreateBackImage()
{
	std::shared_ptr <GameEngineSpriteRenderer> RendererPtr0 = CreateComponent<GameEngineSpriteRenderer>();
	RendererPtr0->SetScaleToTexture("UI_FrontEnd_CharacterSelect_004-BG.png");
}

void OpeningActor::CreateCharecters()
{
	const std::string_view Kyoko_ImgName = "fx_battle_portraits_kyoko.png";
	const std::string_view Misako_ImgName = "fx_battle_portraits_misako.png";

	Kyoko = CreateComponent<GameEngineSpriteRenderer>();
	Misako = CreateComponent<GameEngineSpriteRenderer>();
	Kyoko->SetScaleToTexture(Kyoko_ImgName);
	Misako->SetScaleToTexture(Misako_ImgName);
	GameEngineTransform* MisakoTrans = Misako->GetTransform();
	const float4 FlipScale = MisakoTrans->GetLocalScale() * float4 { -1.f, 1.f, 1.f };
	MisakoTrans->SetLocalScale(FlipScale);

	//캐릭터 렌더러 이동에 관련된 설정
	const float CharOffsetY = 50.f;
	const float4 CharPivotPos = float4::Down * CharOffsetY;
	const float MisakoOffsetX = 100.f;
	const float KyokoOffsetX = 400.f;
	KyokoEndPos = CharPivotPos + (float4::Right * KyokoOffsetX);
	MisakoEndPos = CharPivotPos + (float4::Right * MisakoOffsetX);

	ScreenSize = GameEngineWindow::GetScreenSize();
	Kyoko->GetTransform()->SetLocalPosition(ScreenSize);
	Misako->GetTransform()->SetLocalPosition(ScreenSize);

	Kyoko->Off();
	Misako->Off();
}

void OpeningActor::CreateFrame()
{
	std::shared_ptr <GameEngineSpriteRenderer> RendererPtr1 = CreateComponent<GameEngineSpriteRenderer>();
	RendererPtr1->SetScaleToTexture("UI_FrontEnd_FileSelect_002-LETTERBOX.png");
}

void OpeningActor::CreateTitles() 
{
	const std::string_view TextRiver_ImgName = "fx_int_RIVER-01.png";
	const std::string_view TextCity_ImgName = "fx_int_CITY-01.png";
	const std::string_view TextGirls_ImgName = "fx_int_GIRLS-02.png";
	const std::string_view TextFull_ImgName = "fx_int_FULL LOGO.png";

	Text_River = CreateComponent<GameEngineSpriteRenderer>();
	Text_City = CreateComponent<GameEngineSpriteRenderer>();
	Text_Girls = CreateComponent<GameEngineSpriteRenderer>();
	Text_Full = CreateComponent<GameEngineSpriteRenderer>();

	Text_River->SetScaleToTexture(TextRiver_ImgName);
	Text_City->SetScaleToTexture(TextCity_ImgName);
	Text_Girls->SetScaleToTexture(TextGirls_ImgName);
	Text_Full->SetScaleToTexture(TextFull_ImgName);


	//텍스트 렌더러 위치 조정
	const float4 TextPivotPos = { -ScreenSize.x * 0.25f, ScreenSize.y * 0.25f };
	const float TextOffset = 75.f;
	Text_Full->GetTransform()->SetLocalPosition(TextPivotPos);
	Text_River->GetTransform()->SetLocalPosition(TextPivotPos + float4{ -TextOffset, TextOffset });
	Text_City->GetTransform()->SetLocalPosition(TextPivotPos + float4{ TextOffset, TextOffset });
	Text_Girls->GetTransform()->SetLocalPosition(TextPivotPos + float4{ 0.f, -TextOffset });
	TextScale = Text_Girls->GetTransform()->GetLocalScale();

	Text_River->Off();
	Text_City->Off();
	Text_Girls->Off();
	Text_Full->Off();
}



void OpeningActor::CraeteBrightImages()
{
	BrightBack = CreateComponent<GameEngineSpriteRenderer>();
	BrightBack->SetScaleToTexture("UI_FrontEnd_CharacterSelect_003-HALFTONE.png");
}




void OpeningActor::Update(float _DeltaTime)
{
	switch (CurState)
	{
	case OpeningActor::State::Video:
		//외부에서 상태를 변경해주기 전까지 아무것도 안 한다
		break;
	case OpeningActor::State::Bright:
		Update_Bright(_DeltaTime);
		break;
	case OpeningActor::State::Text:
		Update_Text(_DeltaTime);
		break;
	case OpeningActor::State::Char:
		Update_Char(_DeltaTime);
		break;
	case OpeningActor::State::Ready:
		Update_Ready();
		break;
	default:
		break;
	}
}






//State가 Video에서 Bright로 넘어가는 순간
void OpeningActor::VideoOff()
{
	if (State::Video != CurState)
	{
		MsgAssert("오프닝을 실행하는 순서가 잘못되었습니다");
		return;
	}

	//만약 사운드가 재생중이지 않았다면 재생시키기
	//TODO
	CurState = State::Bright;
}



void OpeningActor::Update_Bright(float _DeltaTime)
{
	static float Timer = 0.f;
	const float StartTime = 0.3f;
	const float EndTime = 1.0f;

	Timer += _DeltaTime;
	if ((nullptr != BrightBack) && (StartTime < Timer))
	{
		BrightBack->Off();
		BrightBack->Death();
		BrightBack = nullptr;

		std::shared_ptr<Fader> FadePtr = GetLevel()->CreateActor<Fader>(static_cast<int>(UpdateOrder::UI));
		FadePtr->Init(float4{ 1.f,1.f, 1.f, 1.f }, EndTime - StartTime);
	}


	if (Timer < EndTime)
		return;

	CurState = State::Text;
	Text_River->On();
	Text_City->On();
	Text_Girls->On();
}





void OpeningActor::Update_Text(float _DeltaTime)
{
	static float Timer = 0.f;
	const float Duration = 0.3f;
	Timer += _DeltaTime;

	float Ratio = (Timer / Duration);

	float4 NowScale = float4::LerpClamp(TextScale * 5.f, TextScale, Ratio);
	Text_River->GetTransform()->SetLocalScale(NowScale);
	Text_City->GetTransform()->SetLocalScale(NowScale);
	Text_Girls->GetTransform()->SetLocalScale(NowScale);

	if (Timer < Duration)
		return;
	
	Text_River->Off();
	Text_City->Off();
	Text_Girls->Off();
	Text_Full->On();

	Kyoko->On();
	Misako->On();

	CurState = OpeningActor::State::Char;
}




void OpeningActor::Update_Char(float _DeltaTime)
{
	static float Timer = 0.f;
	const float Duration = 0.5f;
	Timer += _DeltaTime;

	float Ratio = (Timer / Duration);

	const float CharPosY = KyokoEndPos.y;
	float4 NowKyokoPos = float4::LerpClamp(float4{ ScreenSize.x, CharPosY }, KyokoEndPos, Ratio);
	float4 NowMisakoPos = float4::LerpClamp(float4{ -ScreenSize.x, CharPosY }, MisakoEndPos, Ratio);

	Kyoko->GetTransform()->SetLocalPosition(NowKyokoPos);
	Misako->GetTransform()->SetLocalPosition(NowMisakoPos);

	if (Timer < Duration)
		return;

	CurState = State::Ready;
}



void OpeningActor::Update_Ready()
{
	if (false == KeyMgr::IsDown(KeyNames::Esc))
		return;

	//Sound off, TODO

	LevelMgr::ChangeLevel(LevelNames::SchoolEntryLevel);
}


void OpeningActor::Release()
{
	// TODO
}