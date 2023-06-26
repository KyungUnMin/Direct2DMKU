#include "PrecompileHeader.h"
#include "FieldEnemy_Noise.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCG_GameCore.h"
#include "RCGDefine.h"

const int FieldEnemy_Noise::MaxHp = 330;

FieldEnemy_Noise::FieldEnemy_Noise()
{

}

FieldEnemy_Noise::~FieldEnemy_Noise()
{

}



void FieldEnemy_Noise::Start()
{
	FieldBossBase::Start();

	Fsm.Init(this);
	SetStartHp(MaxHp);
	FieldActorBase::SetShadowScale(1.5f);
}

void FieldEnemy_Noise::SetStartHp(int _Hp)
{
	FieldBossBase::SetStartHp(_Hp);
	Fsm.SetMaxHp(_Hp);
}


void FieldEnemy_Noise::Update(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldBossBase::Update(_DeltaTime);

	Fsm.Update(_DeltaTime);
}





void FieldEnemy_Noise::Render(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldBossBase::Render(_DeltaTime);

	Fsm.Render(_DeltaTime);
}



void FieldEnemy_Noise::OnDamage(int _Damege)
{
	FieldBossBase::OnDamage(_Damege);
	Fsm.CalPhase(GetHp());
}

bool FieldEnemy_Noise::OnDamage_Face(int _Damage)
{
	OnDamage(_Damage);
	ExceptionType Result = OnDamageException();

	if (ExceptionType::DamageOk_StateChanged == Result)
		return true;

	if (ExceptionType::DamageOk_StateKeep == Result)
		return true;

	if (ExceptionType::DamageNo == Result)
		return false;

	Fsm.ChangeState(NoiseStateType::NormalDamaged_Face);
	return true;
}

bool FieldEnemy_Noise::OnDamage_Stomach(int _Damage)
{
	OnDamage(_Damage);
	ExceptionType Result = OnDamageException();

	if (ExceptionType::DamageOk_StateChanged == Result)
		return true;

	if (ExceptionType::DamageOk_StateKeep == Result)
		return true;

	if (ExceptionType::DamageNo == Result)
		return false;

	Fsm.ChangeState(NoiseStateType::NormalDamaged_Stomach);
	return true;
}

bool FieldEnemy_Noise::OnDamage_Jaw(int _Damage)
{
	OnDamage(_Damage);
	ExceptionType Result = OnDamageException();

	if (ExceptionType::DamageOk_StateChanged == Result)
		return true;

	if (ExceptionType::DamageOk_StateKeep == Result)
		return true;

	if (ExceptionType::DamageNo == Result)
		return false;

	Fsm.ChangeState(NoiseStateType::NormalDamaged_Jaw);
	return true;
}

bool FieldEnemy_Noise::OnDamage_BlowBack(int _Damage)
{
	OnDamage(_Damage);
	ExceptionType Result = OnDamageException();

	if (ExceptionType::DamageOk_StateChanged == Result)
		return true;

	if (ExceptionType::DamageOk_StateKeep == Result)
		return true;

	if (ExceptionType::DamageNo == Result)
		return false;
	

	Fsm.ChangeState(NoiseStateType::Damaged_BlowBack);
	return true;
}

void FieldEnemy_Noise::JumpForSing()
{
	Fsm.ChangeState(NoiseStateType::JumpToStage);
}



FieldEnemy_Noise::ExceptionType FieldEnemy_Noise::OnDamageException()
{
	NoiseStateType CurState = Fsm.GetNowState<NoiseStateType>();

	//데미지 처리후 KO된 경우
	if (true == IsKO())
	{
		//이미 Ko된 경우
		if (NoiseStateType::Damaged_KnockDown == CurState)
			return ExceptionType::DamageNo;

		//KnockDown상태로 변경
		Fsm.ChangeState(NoiseStateType::Damaged_KnockDown);
		return ExceptionType::DamageOk_StateChanged;
	}

	//방금 공격으로 Phase가 변경된 경우
	else if (PrevPhase != Fsm.GetCurPhase())
	{
		PrevPhase = Fsm.GetCurPhase();

		//KnockDown상태로 변경
		Fsm.ChangeState(NoiseStateType::JumpToStage);
		return ExceptionType::DamageOk_StateChanged;
	}

	//현재 상태가 슈퍼아머 상태인 경우 FSM은 변화시키지 않고 데미지만 처리
	else if (true == Fsm.IsUnbeatableState())
		return ExceptionType::DamageOk_StateKeep;

	return ExceptionType::NoException;
}




void FieldEnemy_Noise::LevelChangeEnd()
{
	FieldEnemyBase::LevelChangeEnd();

	if (NoiseStateType::Damaged_KnockDown == Fsm.GetNowState<NoiseStateType>())
		return;

	Fsm.ChangeState(NoiseStateType::Idle);
}

