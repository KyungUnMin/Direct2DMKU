#include "PrecompileHeader.h"
#include "FieldEnemy_TigerMan.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCG_GameCore.h"
#include "RCGDefine.h"


FieldEnemy_TigerMan::FieldEnemy_TigerMan()
{

}

FieldEnemy_TigerMan::~FieldEnemy_TigerMan()
{

}



void FieldEnemy_TigerMan::Start()
{
	FieldEnemyBase::Start();
	Fsm.Init(this);
}



void FieldEnemy_TigerMan::Update(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldEnemyBase::Update(_DeltaTime);

	Fsm.Update(_DeltaTime);
}

void FieldEnemy_TigerMan::Render(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldEnemyBase::Render(_DeltaTime);

	Fsm.Render(_DeltaTime);
}


bool FieldEnemy_TigerMan::OnDamage_Face(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (TigerManStateType::Damaged_KnockDown == Fsm.GetNowState<TigerManStateType>())
			return false;

		Fsm.ChangeState(TigerManStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(TigerManStateType::NormalDamaged_Face);
	return true;
}

bool FieldEnemy_TigerMan::OnDamage_Stomach(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (TigerManStateType::Damaged_KnockDown == Fsm.GetNowState<TigerManStateType>())
			return false;

		Fsm.ChangeState(TigerManStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(TigerManStateType::NormalDamaged_Stomach);
	return true;
}

bool FieldEnemy_TigerMan::OnDamage_Jaw(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (TigerManStateType::Damaged_KnockDown == Fsm.GetNowState<TigerManStateType>())
			return false;

		Fsm.ChangeState(TigerManStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(TigerManStateType::NormalDamaged_Jaw);
	return true;
}

bool FieldEnemy_TigerMan::OnDamage_BlowBack(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (TigerManStateType::Damaged_KnockDown == Fsm.GetNowState<TigerManStateType>())
			return false;

		Fsm.ChangeState(TigerManStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(TigerManStateType::Damaged_BlowBack);
	return true;
}

void FieldEnemy_TigerMan::LevelChangeEnd()
{
	FieldEnemyBase::LevelChangeEnd();

	if (TigerManStateType::Damaged_KnockDown == Fsm.GetNowState<TigerManStateType>())
		return;

	Fsm.ChangeState(TigerManStateType::Idle);
}