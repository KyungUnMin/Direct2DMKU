#include "PrecompileHeader.h"
#include "FieldEnemy_Cheerleader.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCG_GameCore.h"
#include "RCGDefine.h"



FieldEnemy_Cheerleader::FieldEnemy_Cheerleader()
{

}

FieldEnemy_Cheerleader::~FieldEnemy_Cheerleader()
{

}



void FieldEnemy_Cheerleader::Start()
{
	FieldEnemyBase::Start();
	Fsm.Init(this);
}

void FieldEnemy_Cheerleader::Update(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldEnemyBase::Update(_DeltaTime);

	Fsm.Update(_DeltaTime);
}

void FieldEnemy_Cheerleader::Render(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldEnemyBase::Render(_DeltaTime);

	Fsm.Render(_DeltaTime);
}


bool FieldEnemy_Cheerleader::OnDamage_Face(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (CheerleaderStateType::Damaged_KnockDown == Fsm.GetNowState<CheerleaderStateType>())
			return false;

		Fsm.ChangeState(CheerleaderStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(CheerleaderStateType::NormalDamaged_Face);
	return true;
}

bool FieldEnemy_Cheerleader::OnDamage_Stomach(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (CheerleaderStateType::Damaged_KnockDown == Fsm.GetNowState<CheerleaderStateType>())
			return false;

		Fsm.ChangeState(CheerleaderStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(CheerleaderStateType::NormalDamaged_Stomach);
	return true;
}

bool FieldEnemy_Cheerleader::OnDamage_Jaw(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (CheerleaderStateType::Damaged_KnockDown == Fsm.GetNowState<CheerleaderStateType>())
			return false;

		Fsm.ChangeState(CheerleaderStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(CheerleaderStateType::NormalDamaged_Jaw);
	return true;
}

bool FieldEnemy_Cheerleader::OnDamage_BlowBack(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (CheerleaderStateType::Damaged_KnockDown == Fsm.GetNowState<CheerleaderStateType>())
			return false;

		Fsm.ChangeState(CheerleaderStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(CheerleaderStateType::Damaged_BlowBack);
	return true;
}

