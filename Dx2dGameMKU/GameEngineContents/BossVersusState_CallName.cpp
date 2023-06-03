#include "PrecompileHeader.h"
#include "BossVersusState_CallName.h"

#include <GameEnginePlatform/GameEngineWindow.h>

#include "BossVersus.h"
#include "SelfRenderer.h"

const std::string_view BossVersusState_CallName::NameTag_FileName = "VersusPortrait_NameTag.png";
const float4 BossVersusState_CallName::NameDestPos = float4{ -300.f, -200.f };
const float4 BossVersusState_CallName::NameTagDestPos = float4{ -388.f, -227.f };


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
	CreateNameTags();


	SettingMovePoint();
}


void BossVersusState_CallName::BindNameRenders()
{
	BossVersus* VersusUI = BossVersus::GetPtr();

	PlayerName = VersusUI->GetPlayerName();
	BossName = VersusUI->GetBossName();

	//테스트 코드
	{
		const float4 LocalScale = float4{ 800.f, 400.f };
		PlayerName->GetTransform()->SetLocalScale(LocalScale);
		BossName->GetTransform()->SetLocalScale(LocalScale);
	}
}


void BossVersusState_CallName::CreateNameTags()
{
	BossVersus* VersusUI = BossVersus::GetPtr();

	//네임태그 렌더러 생성
	PlayerNameTag = VersusUI->CreataEngineUIRender(NameTag_FileName, BossVersusUIRenderOrder::NameTag);
	BossNameTag = VersusUI->CreataEngineUIRender(NameTag_FileName, BossVersusUIRenderOrder::NameTag);
	PlayerNameTag ->Off();
	BossNameTag->Off();

	//임시코드
	{
		GameEngineTransform* PlayerNameTagTrans = PlayerNameTag->GetTransform();
		GameEngineTransform* BossNameTagTrans = BossNameTag->GetTransform();

		const float4 Scale = float4{ 1000.f, 300.f };
		PlayerNameTagTrans->SetLocalScale(Scale);
		BossNameTagTrans->SetLocalScale(Scale);
	}

	BossNameTag->GetTransform()->SetLocalNegativeScaleX();
}





void BossVersusState_CallName::SettingMovePoint()
{
	NameStartPos = NameDestPos + float4::Left * 500.f;
	NameTagStartPos = NameTagDestPos + float4::Left * 400.f;

	GameEngineTransform* PlayerNameTrans = PlayerName->GetTransform();
	GameEngineTransform* BossNameTrans = BossName->GetTransform();
	GameEngineTransform* PlayerNameTagTrans = PlayerNameTag->GetTransform();
	GameEngineTransform* BossNameTagTrans = BossNameTag->GetTransform();

	PlayerNameTrans->SetLocalPosition(NameStartPos);
	BossNameTrans->SetLocalPosition(PosFlip(NameStartPos));
	PlayerNameTagTrans->SetLocalPosition(NameTagStartPos);
	BossNameTagTrans->SetLocalPosition(PosFlip(NameTagStartPos));
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

	float Ratio = GetLiveTime() / Duration;
	float SinValue = sinf(GameEngineMath::PIE * 0.5f * Ratio);

	float4 NameNowPos = float4::LerpClamp(NameStartPos, NameDestPos, SinValue);
	float4 NameTagNowPos = float4::LerpClamp(NameTagStartPos, NameTagDestPos, SinValue);

	GameEngineTransform* PlayerNameTrans = PlayerName->GetTransform();
	GameEngineTransform* BossNameTrans = BossName->GetTransform();
	GameEngineTransform* PlayerNameTagTrans = PlayerNameTag->GetTransform();
	GameEngineTransform* BossNameTagTrans = BossNameTag->GetTransform();

	PlayerNameTrans->SetLocalPosition(NameNowPos);
	BossNameTrans->SetLocalPosition(PosFlip(NameNowPos));
	PlayerNameTagTrans->SetLocalPosition(NameTagNowPos);
	BossNameTagTrans->SetLocalPosition(PosFlip(NameTagNowPos));

	if (Ratio < 1.f)
		return;

	GetFSM()->ChangeState(BossVersusStateType::Wait);
}
