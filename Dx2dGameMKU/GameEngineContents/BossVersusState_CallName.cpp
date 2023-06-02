#include "PrecompileHeader.h"
#include "BossVersusState_CallName.h"

#include <GameEnginePlatform/GameEngineWindow.h>

#include "BossVersus.h"
#include "SelfRenderer.h"

const std::string_view BossVersusState_CallName::NameTag_FileName = "VersusPortrait_NameTag.png";
const float4 BossVersusState_CallName::NameTagScale = float4{ 800.f, 400.f };
const float4 BossVersusState_CallName::NameTagOffset = float4{ -500.f, -300.f };


BossVersusState_CallName::BossVersusState_CallName()
{

}

BossVersusState_CallName::~BossVersusState_CallName()
{

}

void BossVersusState_CallName::Start() 
{
	StateBase::Start();

	BindNameRenders();
	ScreenSize = GameEngineWindow::GetScreenSize();
	SettingTrans();
	CreateNameTags();
}




void BossVersusState_CallName::BindNameRenders()
{
	BossVersus* VersusUI = BossVersus::GetPtr();

	PlayerName = VersusUI->GetPlayerName();
	BossName = VersusUI->GetBossName();
}


void BossVersusState_CallName::SettingTrans()
{
	float WidthHalf = ScreenSize.hx();
	float HeightHalf = ScreenSize.hy();


	//테스트 코드
	{
		const float HeightScale = 400.f;
		const float4 LocalScale = float4{ HeightScale * 2.f, HeightScale };
		PlayerName->GetTransform()->SetLocalScale(LocalScale);
		BossName->GetTransform()->SetLocalScale(LocalScale);
	}

	float4 DestPos = -ScreenSize.half() * 0.5f;
	float4 FlipPos = { -DestPos.x, DestPos.y };

	PlayerName->GetTransform()->SetLocalPosition(DestPos);
	BossName->GetTransform()->SetLocalPosition(FlipPos);
}



void BossVersusState_CallName::CreateNameTags()
{
	BossVersus* VersusUI = BossVersus::GetPtr();

	//네임태그 렌더러 생성
	PlayerNameTag = VersusUI->CreataEngineUIRender(NameTag_FileName, BossVersusUIRenderOrder::NameTag);
	BossNameTag = VersusUI->CreataEngineUIRender(NameTag_FileName, BossVersusUIRenderOrder::NameTag);
	PlayerNameTag ->Off();
	BossNameTag->Off();

	GameEngineTransform* PlayerNameTagTrans = PlayerNameTag->GetTransform();
	GameEngineTransform* BossNameTagTrans = BossNameTag->GetTransform();

	//위치 조정
	PlayerNameTagTrans->SetLocalPosition(NameTagOffset);
	BossNameTagTrans->SetLocalPosition(float4{ -NameTagOffset.x,  NameTagOffset.y });

	//크기 조정
	PlayerNameTagTrans->SetLocalScale(NameTagScale);
	BossNameTagTrans->SetLocalScale(NameTagScale);
	BossNameTagTrans->SetLocalNegativeScaleX();
}



void BossVersusState_CallName::EnterState()
{
	StateBase::EnterState();

	PlayerName->On();
	BossName->On();
	PlayerNameTag->On();
	BossNameTag->On();
}

void BossVersusState_CallName::Update(float _DelatTime)
{
	StateBase::Update(_DelatTime);


}
