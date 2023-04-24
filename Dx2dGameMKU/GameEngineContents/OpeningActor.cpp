#include "PrecompileHeader.h"
#include "OpeningActor.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>

#include "RCGDefine.h"
#include "KeyMgr.h"

OpeningActor::OpeningActor()
{

}

OpeningActor::~OpeningActor()
{

}



std::shared_ptr<GameEngineRenderer> OpeningActor::CreateEngineTex(const std::string_view& _ResName)
{
	std::shared_ptr<GameEngineRenderer> RendererPtr = CreateComponent<GameEngineRenderer>();
	RendererPtr->SetPipeLine(RCGDefine::EnginePipeName);
	RendererPtr->GetShaderResHelper().SetTexture(RCGDefine::EngineTexName, _ResName);

	return RendererPtr;
}


void OpeningActor::Start()
{
	std::shared_ptr<GameEngineRenderer> RendererPtr0 = CreateEngineTex("UI_FrontEnd_CharacterSelect_004-BG.png");
	std::shared_ptr<GameEngineRenderer> RendererPtr1 = CreateEngineTex("UI_FrontEnd_FileSelect_002-LETTERBOX.png");

	//배경 렌더러 생성
	ScreenSize = GameEngineWindow::GetScreenSize();
	RendererPtr0->GetTransform()->SetLocalScale({ ScreenSize.x, ScreenSize.y});
	RendererPtr1->GetTransform()->SetLocalScale({ ScreenSize.x, ScreenSize.y});

	//캐릭터 렌더러 생성
	Kyoko = CreateEngineTex("fx_battle_portraits_kyoko.png");
	Misako = CreateEngineTex("fx_battle_portraits_misako.png");

	const float4 CharScale = float4{ 653.f, 983.f } *RCGDefine::ResolutionConvertor;
	Kyoko->GetTransform()->SetLocalScale(CharScale);
	Misako->GetTransform()->SetLocalScale(CharScale);

	const float4 CharPivotPos = float4{ ScreenSize.x * 0.25f, 0.f };
	const float CharOffsetX = 100.f;
	const float CharOffsetY = 50.f;
	KyokoEndPos = CharPivotPos + float4{ CharOffsetX, -CharOffsetY };
	MisakoEndPos = CharPivotPos + float4{ -CharOffsetX, -CharOffsetY };

	//텍스트 렌더러 생성
	Text_River = CreateEngineTex("fx_int_RIVER-01.png");
	Text_City = CreateEngineTex("fx_int_CITY-01.png");
	Text_Girls = CreateEngineTex("fx_int_GIRLS-02.png");
	Text_Full = CreateEngineTex("fx_int_FULL LOGO.png");
	TextScale = float4{ 1024.f, 512.f } *RCGDefine::ResolutionConvertor;

	//텍스트 렌더러 위치 조정
	const float4 TextPivotPos = { -ScreenSize.x * 0.25f, ScreenSize.y * 0.25f };
	const float TextOffset = 75.f;
	Text_Full->GetTransform()->SetLocalPosition(TextPivotPos);
	Text_River->GetTransform()->SetLocalPosition(TextPivotPos + float4{-TextOffset, TextOffset });
	Text_City->GetTransform()->SetLocalPosition(TextPivotPos + float4{ TextOffset, TextOffset });
	Text_Girls->GetTransform()->SetLocalPosition(TextPivotPos + float4{ 0.f, -TextOffset });
}


void OpeningActor::Update(float _DeltaTime)
{
	switch (CurState)
	{
	case OpeningActor::State::Video:
		Update_Video();
		break;
	case OpeningActor::State::Text:
		Update_Text(_DeltaTime);
		break;
	case OpeningActor::State::Char:
		Update_Char(_DeltaTime);
		break;
	case OpeningActor::State::Ready:

		break;
	default:
		break;
	}
}



void OpeningActor::Update_Video()
{
	if (false == KeyMgr::IsDown(KeyNames::Esc))
		return;

	CurState = State::Text;
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
	
	Text_River->GetTransform()->SetLocalScale(float4::Zero);
	Text_City->GetTransform()->SetLocalScale(float4::Zero);
	Text_Girls->GetTransform()->SetLocalScale(float4::Zero);
	Text_Full->GetTransform()->SetLocalScale(TextScale);
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