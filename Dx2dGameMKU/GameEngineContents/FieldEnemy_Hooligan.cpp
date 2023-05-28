#include "PrecompileHeader.h"
#include "FieldEnemy_Hooligan.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCG_GameCore.h"
#include "RCGDefine.h"



FieldEnemy_Hooligan::FieldEnemy_Hooligan()
{

}

FieldEnemy_Hooligan::~FieldEnemy_Hooligan()
{

}



void FieldEnemy_Hooligan::Start()
{
	FieldEnemyBase::Start();
	Fsm.Init(this);
}




void FieldEnemy_Hooligan::Update(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldEnemyBase::Update(_DeltaTime);

	Fsm.Update(_DeltaTime);
}

void FieldEnemy_Hooligan::Render(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldEnemyBase::Render(_DeltaTime);

	Fsm.Render(_DeltaTime);
}


bool FieldEnemy_Hooligan::OnDamage_Face(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (HooliganStateType::Damaged_KnockDown == Fsm.GetNowState<HooliganStateType>())
			return false;

		Fsm.ChangeState(HooliganStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(HooliganStateType::NormalDamaged_Face);
	return true;
}

bool FieldEnemy_Hooligan::OnDamage_Stomach(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (HooliganStateType::Damaged_KnockDown == Fsm.GetNowState<HooliganStateType>())
			return false;

		Fsm.ChangeState(HooliganStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(HooliganStateType::NormalDamaged_Stomach);
	return true;
}

bool FieldEnemy_Hooligan::OnDamage_Jaw(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (HooliganStateType::Damaged_KnockDown == Fsm.GetNowState<HooliganStateType>())
			return false;

		Fsm.ChangeState(HooliganStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(HooliganStateType::NormalDamaged_Jaw);
	return true;
}

bool FieldEnemy_Hooligan::OnDamage_BlowBack(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (HooliganStateType::Damaged_KnockDown == Fsm.GetNowState<HooliganStateType>())
			return false;

		Fsm.ChangeState(HooliganStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(HooliganStateType::Damaged_BlowBack);
	return true;
}

void FieldEnemy_Hooligan::LevelChangeEnd()
{
	FieldEnemyBase::LevelChangeEnd();

	if (HooliganStateType::Damaged_KnockDown == Fsm.GetNowState<HooliganStateType>())
		return;

	Fsm.ChangeState(HooliganStateType::Idle);
}