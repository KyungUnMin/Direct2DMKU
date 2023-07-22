#include "PrecompileHeader.h"
#include "FieldEnemy_SchoolBoy.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCG_GameCore.h"
#include "RCGDefine.h"



FieldEnemy_SchoolBoy::FieldEnemy_SchoolBoy()
{

}

FieldEnemy_SchoolBoy::~FieldEnemy_SchoolBoy()
{

}



void FieldEnemy_SchoolBoy::Start()
{
	FieldEnemyBase::Start();
	SetStartHp(30);
	Fsm.Init(this);
}

void FieldEnemy_SchoolBoy::SitDown()
{
	Fsm.ChangeState(SchoolBoyStateType::Ready);
}


void FieldEnemy_SchoolBoy::Update(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldEnemyBase::Update(_DeltaTime);

	Fsm.Update(_DeltaTime);
}

void FieldEnemy_SchoolBoy::Render(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldEnemyBase::Render(_DeltaTime);

	Fsm.Render(_DeltaTime);
}


bool FieldEnemy_SchoolBoy::OnDamage_Face(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (SchoolBoyStateType::Damaged_KnockDown == Fsm.GetNowState<SchoolBoyStateType>())
			return false;

		Fsm.ChangeState(SchoolBoyStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(SchoolBoyStateType::NormalDamaged_Face);
	return true;
}

bool FieldEnemy_SchoolBoy::OnDamage_Stomach(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (SchoolBoyStateType::Damaged_KnockDown == Fsm.GetNowState<SchoolBoyStateType>())
			return false;

		Fsm.ChangeState(SchoolBoyStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(SchoolBoyStateType::NormalDamaged_Stomach);
	return true;
}

bool FieldEnemy_SchoolBoy::OnDamage_Jaw(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (SchoolBoyStateType::Damaged_KnockDown == Fsm.GetNowState<SchoolBoyStateType>())
			return false;

		Fsm.ChangeState(SchoolBoyStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(SchoolBoyStateType::NormalDamaged_Jaw);
	return true;
}

bool FieldEnemy_SchoolBoy::OnDamage_BlowBack(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (SchoolBoyStateType::Damaged_KnockDown == Fsm.GetNowState<SchoolBoyStateType>())
			return false;

		Fsm.ChangeState(SchoolBoyStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(SchoolBoyStateType::Damaged_BlowBack);
	return true;
}

void FieldEnemy_SchoolBoy::LevelChangeEnd()
{
	FieldEnemyBase::LevelChangeEnd();

	if (SchoolBoyStateType::Damaged_KnockDown == Fsm.GetNowState<SchoolBoyStateType>())
		return;

	Fsm.ChangeState(SchoolBoyStateType::Idle);
}