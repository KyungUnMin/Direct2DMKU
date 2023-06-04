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
	HpBar->Init(GetHp());
}

void FieldBossBase::SetStartHp(int _Hp)
{
	FieldEnemyBase::SetStartHp(_Hp);
	HpBar->Init(_Hp);
}



void FieldBossBase::OnDamage(int _Damege)
{
	FieldEnemyBase::OnDamage(_Damege);

	//UI���� ü�� ���� ��Ű��
	HpBar->SetHp(GetHp());
}

