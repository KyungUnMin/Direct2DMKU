#include "PrecompileHeader.h"
#include "FieldBossBase.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

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
	//���� UI ����
}

bool FieldBossBase::OnDamage(int _Damege)
{
	if (false == FieldEnemyBase::OnDamage(_Damege))
		return false;

	//UI���� ü�� ���� ��Ű��
	return true;
}