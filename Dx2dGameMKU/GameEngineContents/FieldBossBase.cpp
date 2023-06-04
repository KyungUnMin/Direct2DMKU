#include "PrecompileHeader.h"
#include "FieldBossBase.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCGEnums.h"

#include "BossHUD.h"

const float4 FieldBossBase::RenderScale = float4{ 300.f, 300.f } *2.5f;

FieldBossBase::FieldBossBase()
{

}

FieldBossBase::~FieldBossBase()
{

}


void FieldBossBase::Start()
{
	FieldEnemyBase::Start();

	GetRenderer()->GetTransform()->SetLocalScale(RenderScale);
	HpBar = GetLevel()->CreateActor<BossHUD>(UpdateOrder::UI);
	GameEngineTransform* HpBarTrans = HpBar->GetTransform();
	HpBarTrans->AddLocalPosition(float4::Down * 265.f);
}

bool FieldBossBase::OnDamage(int _Damege)
{
	if (false == FieldEnemyBase::OnDamage(_Damege))
		return false;

	//UI에서 체력 감소 시키기
	return true;
}