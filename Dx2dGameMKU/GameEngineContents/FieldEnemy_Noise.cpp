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

	//������ ó���� KO�� ���
	if (true == IsKO())
	{
		//�̹� Ko�� ���
		if (NoiseStateType::Damaged_KnockDown == CurState)
			return ExceptionType::DamageNo;

		//KnockDown���·� ����
		Fsm.ChangeState(NoiseStateType::Damaged_KnockDown);
		return ExceptionType::DamageOk_StateChanged;
	}

	//��� �������� Phase�� ����� ���
	else if (PrevPhase != Fsm.GetCurPhase())
	{
		PrevPhase = Fsm.GetCurPhase();

		//KnockDown���·� ����
		Fsm.ChangeState(NoiseStateType::JumpToStage);
		return ExceptionType::DamageOk_StateChanged;
	}

	//���� ���°� ���۾Ƹ� ������ ��� FSM�� ��ȭ��Ű�� �ʰ� �������� ó��
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

