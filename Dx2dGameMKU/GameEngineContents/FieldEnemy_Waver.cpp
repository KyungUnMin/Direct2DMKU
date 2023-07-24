#include "PrecompileHeader.h"
#include "FieldEnemy_Waver.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCG_GameCore.h"
#include "RCGDefine.h"



FieldEnemy_Waver::FieldEnemy_Waver()
{

}

FieldEnemy_Waver::~FieldEnemy_Waver()
{

}



void FieldEnemy_Waver::Start()
{
	FieldEnemyBase::Start();
	SetStartHp(80);
	Fsm.Init(this);
}



void FieldEnemy_Waver::Update(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldEnemyBase::Update(_DeltaTime);

	Fsm.Update(_DeltaTime);
}

void FieldEnemy_Waver::Render(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldEnemyBase::Render(_DeltaTime);

	Fsm.Render(_DeltaTime);
}


bool FieldEnemy_Waver::OnDamage_Face(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (WaverStateType::Damaged_KnockDown == Fsm.GetNowState<WaverStateType>())
			return false;

		Fsm.ChangeState(WaverStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(WaverStateType::NormalDamaged_Face);
	return true;
}

bool FieldEnemy_Waver::OnDamage_Stomach(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (WaverStateType::Damaged_KnockDown == Fsm.GetNowState<WaverStateType>())
			return false;

		Fsm.ChangeState(WaverStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(WaverStateType::NormalDamaged_Stomach);
	return true;
}

bool FieldEnemy_Waver::OnDamage_Jaw(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (WaverStateType::Damaged_KnockDown == Fsm.GetNowState<WaverStateType>())
			return false;

		Fsm.ChangeState(WaverStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(WaverStateType::NormalDamaged_Jaw);
	return true;
}

bool FieldEnemy_Waver::OnDamage_BlowBack(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (WaverStateType::Damaged_KnockDown == Fsm.GetNowState<WaverStateType>())
			return false;

		Fsm.ChangeState(WaverStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(WaverStateType::Damaged_BlowBack);
	return true;
}

void FieldEnemy_Waver::LevelChangeEnd()
{
	FieldEnemyBase::LevelChangeEnd();

	if (WaverStateType::Damaged_KnockDown == Fsm.GetNowState<WaverStateType>())
		return;

	Fsm.ChangeState(WaverStateType::Idle);
}

