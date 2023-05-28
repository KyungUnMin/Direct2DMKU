#include "PrecompileHeader.h"
#include "FieldEnemy_Cop.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCG_GameCore.h"
#include "RCGDefine.h"



FieldEnemy_Cop::FieldEnemy_Cop()
{

}

FieldEnemy_Cop::~FieldEnemy_Cop()
{

}



void FieldEnemy_Cop::Start()
{
	FieldEnemyBase::Start();
	Fsm.Init(this);
}



void FieldEnemy_Cop::Update(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldEnemyBase::Update(_DeltaTime);

	Fsm.Update(_DeltaTime);
}

void FieldEnemy_Cop::Render(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldEnemyBase::Render(_DeltaTime);

	Fsm.Render(_DeltaTime);
}


bool FieldEnemy_Cop::OnDamage_Face(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (CopStateType::Damaged_KnockDown == Fsm.GetNowState<CopStateType>())
			return false;

		Fsm.ChangeState(CopStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(CopStateType::NormalDamaged_Face);
	return true;
}

bool FieldEnemy_Cop::OnDamage_Stomach(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (CopStateType::Damaged_KnockDown == Fsm.GetNowState<CopStateType>())
			return false;

		Fsm.ChangeState(CopStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(CopStateType::NormalDamaged_Stomach);
	return true;
}

bool FieldEnemy_Cop::OnDamage_Jaw(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (CopStateType::Damaged_KnockDown == Fsm.GetNowState<CopStateType>())
			return false;

		Fsm.ChangeState(CopStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(CopStateType::NormalDamaged_Jaw);
	return true;
}

bool FieldEnemy_Cop::OnDamage_BlowBack(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (CopStateType::Damaged_KnockDown == Fsm.GetNowState<CopStateType>())
			return false;

		Fsm.ChangeState(CopStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(CopStateType::Damaged_BlowBack);
	return true;
}

void FieldEnemy_Cop::LevelChangeEnd()
{
	FieldEnemyBase::LevelChangeEnd();

	if (CopStateType::Damaged_KnockDown == Fsm.GetNowState<CopStateType>())
		return;

	Fsm.ChangeState(CopStateType::Idle);
}