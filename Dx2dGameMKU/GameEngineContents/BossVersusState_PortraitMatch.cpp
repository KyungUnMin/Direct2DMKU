#include "PrecompileHeader.h"
#include "BossVersusState_PortraitMatch.h"

#include <GameEnginePlatform/GameEngineWindow.h>


#include "RCGDefine.h"
#include "RCGEnums.h"
#include "SoundMgr.h"


#include "BossVersus.h"
#include "BossVersusUIFSM.h"
#include "SelfRenderer.h"

const std::string_view BossVersusState_PortraitMatch::LinkCBufferName = "LinkColor";


BossVersusState_PortraitMatch::BossVersusState_PortraitMatch()
{

}

BossVersusState_PortraitMatch::~BossVersusState_PortraitMatch()
{

}



void BossVersusState_PortraitMatch::Start()
{
	StateBase::Start();

	CreateRenderers();
	SettingValue();
}




void BossVersusState_PortraitMatch::CreateRenderers()
{
	BossVersus* VersusUI = BossVersus::GetPtr();

	//플레이어 초상화
	PlayerPortrait = VersusUI->GetPlayerPortrait();
	//보스 초상화
	BossPortrait = VersusUI->GetBossPortrait();

	//화면 전체적인 이펙트 색상
	const float4& ScreenSize = GameEngineWindow::GetScreenSize();
	UILightRender = VersusUI->CreateComponent<SelfRenderer>(BossVersusUIRenderOrder::ScreenLight);
	UILightRender->SetCamera(RCG_CamNumType::BossUI);

	UILightRender->SetMesh("Rect");
	UILightRender->SetPipeLine(RCGDefine::GetPipeName(PipeType::DirectColor));
	UILightRender->GetShaderResHelper().SetConstantBufferLink(LinkCBufferName, UILightColor);
	UILightRender->GetTransform()->SetLocalScale(ScreenSize);
}


void BossVersusState_PortraitMatch::SettingValue()
{
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	const float PortOffsetY = 30.f;

	PortraitStartPos = float4{ ScreenSize.hx(), -PortOffsetY };
	PortraitEndPos = PortraitStartPos + (float4::Left * 300.f);
}

void BossVersusState_PortraitMatch::EnterState()
{
	StateBase::EnterState();
	//SoundMgr::PlaySFX("BossVersus_Explo.mp3");
}


void BossVersusState_PortraitMatch::Update(float _DeltaTime)
{
	StateBase::Update(_DeltaTime);

	float Ratio = (GetLiveTime() / Duration);

	const float4 NowPortraitPos = float4::LerpClamp(PortraitStartPos, PortraitEndPos, Ratio);
	PlayerPortrait->GetTransform()->SetLocalPosition(NowPortraitPos * float4{ -1.f, 1.f, 1.f });
	BossPortrait->GetTransform()->SetLocalPosition(NowPortraitPos);
	//PlayerPortrait->GetTransform()->SetLocalPosition(PortraitEndPos * float4{ -1.f, 1.f, 1.f });
	//BossPortrait->GetTransform()->SetLocalPosition(PortraitEndPos);

	float ColorRatio = (1.f - Ratio);
	UILightColor = float4{ ColorRatio, ColorRatio , 1.f, ColorRatio };

	if (Ratio < 1.f)
		return;

	GetFSM()->ChangeState(BossVersusStateType::Corner);
}


