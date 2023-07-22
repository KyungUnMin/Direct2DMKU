#include "PrecompileHeader.h"
#include "FieldEnemy_SchoolGirl.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCG_GameCore.h"
#include "RCGDefine.h"



FieldEnemy_SchoolGirl::FieldEnemy_SchoolGirl()
{

}

FieldEnemy_SchoolGirl::~FieldEnemy_SchoolGirl()
{

}



void FieldEnemy_SchoolGirl::Start()
{
	FieldEnemyBase::Start();
	SetStartHp(20);
	Fsm.Init(this);
}

void FieldEnemy_SchoolGirl::SitDown()
{
	Fsm.ChangeState(SchoolGirlStateType::Ready);
}


void FieldEnemy_SchoolGirl::Update(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldEnemyBase::Update(_DeltaTime);

	Fsm.Update(_DeltaTime);
}

void FieldEnemy_SchoolGirl::Render(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldEnemyBase::Render(_DeltaTime);

	Fsm.Render(_DeltaTime);
}


bool FieldEnemy_SchoolGirl::OnDamage_Face(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (SchoolGirlStateType::Damaged_KnockDown == Fsm.GetNowState<SchoolGirlStateType>())
			return false;

		Fsm.ChangeState(SchoolGirlStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(SchoolGirlStateType::NormalDamaged_Face);
	return true;
}

bool FieldEnemy_SchoolGirl::OnDamage_Stomach(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (SchoolGirlStateType::Damaged_KnockDown == Fsm.GetNowState<SchoolGirlStateType>())
			return false;

		Fsm.ChangeState(SchoolGirlStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(SchoolGirlStateType::NormalDamaged_Stomach);
	return true;
}

bool FieldEnemy_SchoolGirl::OnDamage_Jaw(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (SchoolGirlStateType::Damaged_KnockDown == Fsm.GetNowState<SchoolGirlStateType>())
			return false;

		Fsm.ChangeState(SchoolGirlStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(SchoolGirlStateType::NormalDamaged_Jaw);
	return true;
}

bool FieldEnemy_SchoolGirl::OnDamage_BlowBack(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (SchoolGirlStateType::Damaged_KnockDown == Fsm.GetNowState<SchoolGirlStateType>())
			return false;

		Fsm.ChangeState(SchoolGirlStateType::Damaged_KnockDown);
		return true;
	}

	Fsm.ChangeState(SchoolGirlStateType::Damaged_BlowBack);
	return true;
}


void FieldEnemy_SchoolGirl::LevelChangeEnd()
{
	FieldEnemyBase::LevelChangeEnd();

	if (SchoolGirlStateType::Damaged_KnockDown == Fsm.GetNowState<SchoolGirlStateType>())
		return;

	Fsm.ChangeState(SchoolGirlStateType::Idle);
}