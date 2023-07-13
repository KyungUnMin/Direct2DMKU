#include "PrecompileHeader.h"
#include "FieldEnemy_Misuzu.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCG_GameCore.h"
#include "RCGDefine.h"

//const int FieldEnemy_Misuzu::MaxHp = 450;
const int FieldEnemy_Misuzu::MaxHp = 60;

FieldEnemy_Misuzu::FieldEnemy_Misuzu()
{

}

FieldEnemy_Misuzu::~FieldEnemy_Misuzu()
{

}



void FieldEnemy_Misuzu::Start()
{
	FieldBossBase::Start();

	Fsm.Init(this);
	SetStartHp(MaxHp);
	FieldActorBase::SetShadowScale(1.5f);
}

void FieldEnemy_Misuzu::SetStartHp(int _Hp)
{
	FieldBossBase::SetStartHp(_Hp);
	Fsm.SetMaxHp(_Hp);
}


void FieldEnemy_Misuzu::Update(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldBossBase::Update(_DeltaTime);

	Fsm.Update(_DeltaTime);

	RageRender(_DeltaTime);
}

void FieldEnemy_Misuzu::RageRender(float _DeltaTime)
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





void FieldEnemy_Misuzu::Render(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldBossBase::Render(_DeltaTime);

	Fsm.Render(_DeltaTime);
}



void FieldEnemy_Misuzu::OnDamage(int _Damege)
{
	FieldBossBase::OnDamage(_Damege);
	Fsm.CalPhase(GetHp());
}

bool FieldEnemy_Misuzu::OnDamage_Face(int _Damage)
{
	OnDamage(_Damage);
	ExceptionType Result = OnDamageException();

	if (ExceptionType::DamageOk_StateChanged == Result)
		return true;

	if (ExceptionType::DamageOk_StateKeep == Result)
		return true;

	if (ExceptionType::DamageNo == Result)
		return false;

	Fsm.ChangeState(MisuzuStateType::NormalDamaged_Face);
	return true;
}

bool FieldEnemy_Misuzu::OnDamage_Stomach(int _Damage)
{
	OnDamage(_Damage);
	ExceptionType Result = OnDamageException();

	if (ExceptionType::DamageOk_StateChanged == Result)
		return true;

	if (ExceptionType::DamageOk_StateKeep == Result)
		return true;

	if (ExceptionType::DamageNo == Result)
		return false;

	Fsm.ChangeState(MisuzuStateType::NormalDamaged_Stomach);
	return true;
}

bool FieldEnemy_Misuzu::OnDamage_Jaw(int _Damage)
{
	OnDamage(_Damage);
	ExceptionType Result = OnDamageException();

	if (ExceptionType::DamageOk_StateChanged == Result)
		return true;

	if (ExceptionType::DamageOk_StateKeep == Result)
		return true;

	if (ExceptionType::DamageNo == Result)
		return false;

	Fsm.ChangeState(MisuzuStateType::NormalDamaged_Jaw);
	return true;
}

bool FieldEnemy_Misuzu::OnDamage_BlowBack(int _Damage)
{
	OnDamage(_Damage);
	ExceptionType Result = OnDamageException();

	if (ExceptionType::DamageOk_StateChanged == Result)
		return true;

	if (ExceptionType::DamageOk_StateKeep == Result)
		return true;

	if (ExceptionType::DamageNo == Result)
		return false;
	

	Fsm.ChangeState(MisuzuStateType::Damaged_BlowBack);
	return true;
}



FieldEnemy_Misuzu::ExceptionType FieldEnemy_Misuzu::OnDamageException()
{
	MisuzuStateType CurState = Fsm.GetNowState<MisuzuStateType>();

	//데미지 처리후 KO된 경우
	if (true == IsKO())
	{
		//이미 Ko된 경우
		if (MisuzuStateType::Damaged_KnockDown == CurState)
			return ExceptionType::DamageNo;

		//KnockDown상태로 변경
		Fsm.ChangeState(MisuzuStateType::Damaged_KnockDown);
		return ExceptionType::DamageOk_StateChanged;
	}

	//스턴 상태인 경우
	else if (MisuzuStateType::Damaged_Dizzy == CurState)
	{
		Fsm.ChangeState(MisuzuStateType::Damaged_GroundHit);
		return ExceptionType::DamageOk_StateChanged;
	}

	//현재 상태가 슈퍼아머 상태인 경우 FSM은 변화시키지 않고 데미지만 처리
	else if (true == Fsm.IsUnbeatableState())
		return ExceptionType::DamageOk_StateKeep;

	//마지막 페이즈인 경우 FSM은 변화시키지 않고 데미지만 처리
	else if (true == Fsm.IsLastPhase())
		return ExceptionType::DamageOk_StateKeep;


	return ExceptionType::NoException;
}

/*
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
	else if (true == Fsm.IsLastPhase())
	{
		Fsm.ChangeState(MisuzuStateType::NormalDamaged_Stomach);
		return true;
	}
*/


void FieldEnemy_Misuzu::LevelChangeEnd()
{
	FieldEnemyBase::LevelChangeEnd();

	if (MisuzuStateType::Damaged_KnockDown == Fsm.GetNowState<MisuzuStateType>())
		return;

	Fsm.ChangeState(MisuzuStateType::Idle);
}

