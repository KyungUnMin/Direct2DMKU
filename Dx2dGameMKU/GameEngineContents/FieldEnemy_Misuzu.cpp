#include "PrecompileHeader.h"
#include "FieldEnemy_Misuzu.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCG_GameCore.h"
#include "RCGDefine.h"



FieldEnemy_Misuzu::FieldEnemy_Misuzu()
{

}

FieldEnemy_Misuzu::~FieldEnemy_Misuzu()
{

}



void FieldEnemy_Misuzu::Start()
{
	FieldBossBase::Start();

	//юс╫ц
	//FieldBossBase::SetStartHp(200);

	Fsm.Init(this);
}



void FieldEnemy_Misuzu::Update(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldBossBase::Update(_DeltaTime);

	Fsm.Update(_DeltaTime);
}

void FieldEnemy_Misuzu::Render(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldBossBase::Render(_DeltaTime);

	Fsm.Render(_DeltaTime);
}


bool FieldEnemy_Misuzu::OnDamage_Face(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (MisuzuStateType::Damaged_KnockDown == Fsm.GetNowState<MisuzuStateType>())
			return false;

		Fsm.ChangeState(MisuzuStateType::Damaged_KnockDown);
		return true;
	}
	else if (MisuzuStateType::Damaged_Dizzy == Fsm.GetNowState<MisuzuStateType>())
	{
		Fsm.ChangeState(MisuzuStateType::Damaged_GroundHit);
		return true;
	}

	Fsm.ChangeState(MisuzuStateType::NormalDamaged_Face);
	return true;
}

bool FieldEnemy_Misuzu::OnDamage_Stomach(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (MisuzuStateType::Damaged_KnockDown == Fsm.GetNowState<MisuzuStateType>())
			return false;

		Fsm.ChangeState(MisuzuStateType::Damaged_KnockDown);
		return true;
	}
	else if (MisuzuStateType::Damaged_Dizzy == Fsm.GetNowState<MisuzuStateType>())
	{
		Fsm.ChangeState(MisuzuStateType::Damaged_GroundHit);
		return true;
	}

	Fsm.ChangeState(MisuzuStateType::NormalDamaged_Stomach);
	return true;
}

bool FieldEnemy_Misuzu::OnDamage_Jaw(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (MisuzuStateType::Damaged_KnockDown == Fsm.GetNowState<MisuzuStateType>())
			return false;

		Fsm.ChangeState(MisuzuStateType::Damaged_KnockDown);
		return true;
	}
	else if (MisuzuStateType::Damaged_Dizzy == Fsm.GetNowState<MisuzuStateType>())
	{
		Fsm.ChangeState(MisuzuStateType::Damaged_GroundHit);
		return true;
	}

	Fsm.ChangeState(MisuzuStateType::NormalDamaged_Jaw);
	return true;
}

bool FieldEnemy_Misuzu::OnDamage_BlowBack(int _Damage)
{
	OnDamage(_Damage);
	if (true == IsKO())
	{
		if (MisuzuStateType::Damaged_KnockDown == Fsm.GetNowState<MisuzuStateType>())
			return false;

		Fsm.ChangeState(MisuzuStateType::Damaged_KnockDown);
		return true;
	}
	else if (MisuzuStateType::Damaged_Dizzy == Fsm.GetNowState<MisuzuStateType>())
	{
		Fsm.ChangeState(MisuzuStateType::Damaged_GroundHit);
		return true;
	}

	Fsm.ChangeState(MisuzuStateType::Damaged_BlowBack);
	return true;
}

void FieldEnemy_Misuzu::LevelChangeEnd()
{
	FieldEnemyBase::LevelChangeEnd();

	if (MisuzuStateType::Damaged_KnockDown == Fsm.GetNowState<MisuzuStateType>())
		return;

	Fsm.ChangeState(MisuzuStateType::Idle);
}