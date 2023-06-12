#include "PrecompileHeader.h"
#include "FieldEnemy_Yamada.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCG_GameCore.h"
#include "RCGDefine.h"

const int FieldEnemy_Yamada::MaxHp = 450;

FieldEnemy_Yamada::FieldEnemy_Yamada()
{

}

FieldEnemy_Yamada::~FieldEnemy_Yamada()
{

}



void FieldEnemy_Yamada::Start()
{
	FieldBossBase::Start();

	Fsm.Init(this);
	SetStartHp(MaxHp);
	//FieldActorBase::SetShadowScale(1.5f);
}

void FieldEnemy_Yamada::SetStartHp(int _Hp)
{
	FieldBossBase::SetStartHp(_Hp);
	Fsm.SetMaxHp(_Hp);
}


void FieldEnemy_Yamada::Update(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldBossBase::Update(_DeltaTime);

	Fsm.Update(_DeltaTime);

	RageRender(_DeltaTime);
}

void FieldEnemy_Yamada::RageRender(float _DeltaTime)
{
	if (false == Fsm.IsLastPhase())
		return;

	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	if (0 == GetHp())
	{
		Render->ColorOptionValue.PlusColor = float4::Null;
		return;
	}

	float LiveTime = GetLiveTime();
	float RedValue = abs(sinf(LiveTime)) * 0.25f;
	Render->ColorOptionValue.PlusColor = float4{ RedValue, 0.f, 0.f, 0.f };
}





void FieldEnemy_Yamada::Render(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldBossBase::Render(_DeltaTime);

	Fsm.Render(_DeltaTime);
}



void FieldEnemy_Yamada::OnDamage(int _Damege)
{
	FieldBossBase::OnDamage(_Damege);
	Fsm.CalPhase(GetHp());
}

bool FieldEnemy_Yamada::OnDamage_Face(int _Damage)
{
	OnDamage(_Damage);
	ExceptionType Result = OnDamageException();

	if (ExceptionType::DamageOk_StateChanged == Result)
		return true;

	if (ExceptionType::DamageOk_StateKeep == Result)
		return true;

	if (ExceptionType::DamageNo == Result)
		return false;

	Fsm.ChangeState(YamadaStateType::NormalDamaged_Face);
	return true;
}

bool FieldEnemy_Yamada::OnDamage_Stomach(int _Damage)
{
	OnDamage(_Damage);
	ExceptionType Result = OnDamageException();

	if (ExceptionType::DamageOk_StateChanged == Result)
		return true;

	if (ExceptionType::DamageOk_StateKeep == Result)
		return true;

	if (ExceptionType::DamageNo == Result)
		return false;

	Fsm.ChangeState(YamadaStateType::NormalDamaged_Stomach);
	return true;
}

bool FieldEnemy_Yamada::OnDamage_Jaw(int _Damage)
{
	OnDamage(_Damage);
	ExceptionType Result = OnDamageException();

	if (ExceptionType::DamageOk_StateChanged == Result)
		return true;

	if (ExceptionType::DamageOk_StateKeep == Result)
		return true;

	if (ExceptionType::DamageNo == Result)
		return false;

	Fsm.ChangeState(YamadaStateType::NormalDamaged_Jaw);
	return true;
}

bool FieldEnemy_Yamada::OnDamage_BlowBack(int _Damage)
{
	OnDamage(_Damage);
	ExceptionType Result = OnDamageException();

	if (ExceptionType::DamageOk_StateChanged == Result)
		return true;

	if (ExceptionType::DamageOk_StateKeep == Result)
		return true;

	if (ExceptionType::DamageNo == Result)
		return false;
	

	Fsm.ChangeState(YamadaStateType::Damaged_BlowBack);
	return true;
}



FieldEnemy_Yamada::ExceptionType FieldEnemy_Yamada::OnDamageException()
{
	YamadaStateType CurState = Fsm.GetNowState<YamadaStateType>();

	//������ ó���� KO�� ���
	if (true == IsKO())
	{
		//�̹� Ko�� ���
		if (YamadaStateType::Damaged_KnockDown == CurState)
			return ExceptionType::DamageNo;

		//KnockDown���·� ����
		Fsm.ChangeState(YamadaStateType::Damaged_KnockDown);
		return ExceptionType::DamageOk_StateChanged;
	}

	//���� ������ ���
	else if (YamadaStateType::Damaged_Dizzy == CurState)
	{
		Fsm.ChangeState(YamadaStateType::Damaged_GroundHit);
		return ExceptionType::DamageOk_StateChanged;
	}

	//���� ���°� ���۾Ƹ� ������ ��� FSM�� ��ȭ��Ű�� �ʰ� �������� ó��
	else if (true == Fsm.IsUnbeatableState())
		return ExceptionType::DamageOk_StateKeep;

	//������ �������� ��� FSM�� ��ȭ��Ű�� �ʰ� �������� ó��
	else if (true == Fsm.IsLastPhase())
		return ExceptionType::DamageOk_StateKeep;


	return ExceptionType::NoException;
}

/*
if (true == IsKO())
	{
		if (YamadaStateType::Damaged_KnockDown == Fsm.GetNowState<YamadaStateType>())
			return false;

		Fsm.ChangeState(YamadaStateType::Damaged_KnockDown);
		return true;
	}
	else if (YamadaStateType::Damaged_Dizzy == Fsm.GetNowState<YamadaStateType>())
	{
		Fsm.ChangeState(YamadaStateType::Damaged_GroundHit);
		return true;
	}
	else if (true == Fsm.IsLastPhase())
	{
		Fsm.ChangeState(YamadaStateType::NormalDamaged_Stomach);
		return true;
	}
*/


void FieldEnemy_Yamada::LevelChangeEnd()
{
	FieldEnemyBase::LevelChangeEnd();

	if (YamadaStateType::Damaged_KnockDown == Fsm.GetNowState<YamadaStateType>())
		return;

	Fsm.ChangeState(YamadaStateType::Idle);
}

