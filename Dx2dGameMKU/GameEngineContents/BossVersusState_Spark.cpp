#include "PrecompileHeader.h"
#include "BossVersusState_Spark.h"

#include <GameEnginePlatform/GameEngineWindow.h>

#include "RCGDefine.h"

#include "BossVersus.h"
#include "SelfRenderer.h"



BossVersusState_Spark::BossVersusState_Spark()
{

}

BossVersusState_Spark::~BossVersusState_Spark()
{

}


void BossVersusState_Spark::Start() 
{
	StateBase::Start();

	ScreenSize = GameEngineWindow::GetScreenSize();
	CraeteBackImg();
	CreateRenders();
}

void BossVersusState_Spark::CraeteBackImg()
{
	BossVersus* VersusUI = BossVersus::GetPtr();

	BackImg = VersusUI->CreateComponent<SelfRenderer>(BossVersusUIRenderOrder::ScreenLight);
	BackImg->SetCamera(RCG_CamNumType::BossUI);
	BackImg->SetMesh("Rect");
	BackImg->SetPipeLine(RCGDefine::GetPipeName(PipeType::DirectColor));
	BackImg->GetShaderResHelper().SetConstantBufferLink("LinkColor", BackImgColor);


	BackImg->GetTransform()->SetLocalScale(ScreenSize);
	BackImg->Off();
}

void BossVersusState_Spark::CreateRenders()
{
	const std::string_view Spark1_FileName = "VersusSpark1.png";
	const std::string_view Spark2_FileName = "VersusSpark2.png";
	const std::string_view Versus_FileName = "VS_LOGO.png";
	const float4 VersusScale = float4{ 400.f, 200.f };

	BossVersus* VersusUI = BossVersus::GetPtr();

	
	Spark1 = VersusUI->CreataEngineUIRender(Spark1_FileName, BossVersusUIRenderOrder::ScreenLight);
	Spark2 = VersusUI->CreataEngineUIRender(Spark2_FileName, BossVersusUIRenderOrder::ScreenLight);
	Spark2->GetTransform()->SetLocalScale(ScreenSize);

	Spark1->ColorOptionValue.PlusColor = float4{ 0.f, 0.f, 1.0f, 0.f };
	Spark2->ColorOptionValue.PlusColor = float4{ 0.f, 0.f, 1.0f, 0.f };

	Spark1->Off();
	Spark2->Off();

	VersusLogo = VersusUI->CreataEngineUIRender(Versus_FileName, BossVersusUIRenderOrder::ScreenLight);
	VersusLogo->GetTransform()->SetLocalScale(VersusScale);
	VersusLogo->Off();
}



void BossVersusState_Spark::EnterState()
{
	StateBase::EnterState();

	Spark1->On();
}

void BossVersusState_Spark::Update(float _DeltaTime) 
{
	StateBase::Update(_DeltaTime);

	switch (CurState)
	{
	case BossVersusState_Spark::State::Act_Spark1:
		Update_Spark1(_DeltaTime);
		break;
	case BossVersusState_Spark::State::Act_Spark2:
		Update_Spark2(_DeltaTime);
		break;
	}
}

void BossVersusState_Spark::Update_Spark1(float _DeltaTime)
{
	float Timer = GetLiveTime();
	float Ratio = (Timer / Duration_Spark1);


	//정의역 0 ~ Pi 사이, Ratio에 따라 0 -> 1 -> 0으로 이동
	float SinValue = sinf(GameEngineMath::PIE * Ratio);
	float4 NowScale = float4::LerpClamp(ScreenSize * float4::Right, ScreenSize, SinValue);
	Spark1->GetTransform()->SetLocalScale(NowScale);

	if (Ratio < 1.f)
		return;

	Spark1->Off();
	CurState = State::Act_Spark2;
	StateChangeTime = Timer;
	BackImg->On();
	Spark2->On();
	VersusLogo->On();
}

void BossVersusState_Spark::Update_Spark2(float _DeltaTime) 
{
	float Timer = GetLiveTime() - StateChangeTime;
	float Ratio = (Timer / Duration_Spark2);

	Spark2->ColorOptionValue.MulColor = float4::One * (1.f - Ratio);

	if (Ratio < 1.f)
		return;

	Spark2->Off();
	GetFSM()->ChangeState(BossVersusStateType::CallName);
}
