#include "PrecompileHeader.h"
#include "EnemyStateBase.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "EnemyFSMBase.h"
#include "FieldEnemyBase.h"

#include "FieldPlayer.h"
#include "FieldLevelBase.h"
#include "BackGround.h"

EnemyStateBase::EnemyStateBase()
{

}

EnemyStateBase::~EnemyStateBase()
{

}

void EnemyStateBase::Start()
{
	StateBase::Start();

	FsmPtr = GetConvertFSM<EnemyFSMBase>();
	EnemyPtr = FsmPtr->GetEnemy();
	Renderer = EnemyPtr->GetRenderer();
	MainCollider = EnemyPtr->GetMainCollider();

	std::shared_ptr<FieldLevelBase> Level = FieldLevelBase::GetPtr();
	BGPtr = Level->GetBackGround();
}



void EnemyStateBase::EnterState()
{
	StateBase::EnterState();

	ChangeRenderDirection();
}


void EnemyStateBase::ChangeRenderDirection()
{
	if (false == IsLookPlayer)
		return;

	//외부에서 Enemy의 방향을 따로 예약했다면 아래 코드들을 계산하지 않는다
	if (true == EnemyPtr->IsDirRegist())
		return;

	GameEngineTransform* EnemyTransform = EnemyPtr->GetTransform();
	float4 EnemyPos = EnemyTransform->GetWorldPosition();
	float4 PlayerPos = FieldPlayer::GetPtr()->GetTransform()->GetWorldPosition();

	//플레이어가 자신의 오른쪽에 있는 경우
	if (EnemyPos.x < PlayerPos.x)
	{
		EnemyTransform->SetLocalPositiveScaleX();
	}

	//플레이어가 자신의 왼쪽에 있는 경우
	else
	{
		EnemyTransform->SetLocalNegativeScaleX();
	}
}



void EnemyStateBase::Update(float _DeltaTime)
{
	StateBase::Update(_DeltaTime);

	float Height = EnemyPtr->GetHeight();
	Renderer->GetTransform()->SetLocalPosition(float4::Up * Height);
	MainCollider->GetTransform()->SetLocalPosition(float4::Up * Height);
}



float4 EnemyStateBase::GetVecToPlayer(bool _Is2D /*= false*/)
{
	GameEngineTransform* ThisTrans = EnemyPtr->GetTransform();
	float4 ThisWorldPosition = ThisTrans->GetWorldPosition();
	return GetVecToPlayer(ThisWorldPosition, _Is2D);
}


float4 EnemyStateBase::GetVecToPlayer(const float4& _Pos, bool _Is2D /*= false*/)
{
	GameEngineTransform* PlayerTrans = FieldPlayer::GetPtr()->GetTransform();
	float4 PlayerWorldPosition = PlayerTrans->GetWorldPosition();

	float4 CheckPos = _Pos;
	if (true == _Is2D)
	{
		CheckPos.z = 0.f;
		PlayerWorldPosition.z = 0.f;
	}

	return (PlayerWorldPosition - CheckPos);
}


bool EnemyStateBase::IsRightDir()
{
	GameEngineTransform* EnemyTrans = EnemyPtr->GetTransform();
	return (0.f < EnemyTrans->GetLocalScale().x);
}






void EnemyStateBase::Update_SinJump(float _Duration, float _MaxHeight /*= 80.f*/)
{
	Update_SinJump(GetLiveTime(), _Duration, _MaxHeight);
}



void EnemyStateBase::Update_SinJump(float _Timer, float _Duration, float _MaxHeight)
{
	float Ratio = (_Timer / _Duration);
	Ratio = std::clamp(Ratio, 0.f, 1.f);

	float SinValue = std::sinf(GameEngineMath::PIE * Ratio);

	float NowHeight = _MaxHeight * SinValue;
	EnemyPtr->SetHeight(NowHeight);
}


void EnemyStateBase::Update_SinHalfJump(float _Duration, float _MaxHeight /*= 80.f*/)
{
	Update_SinHalfJump(GetLiveTime(), _Duration, _MaxHeight);
}



void EnemyStateBase::Update_SinHalfJump(float _Timer, float _Duration, float _MaxHeight)
{
	float Ratio = (_Timer / _Duration);
	Ratio = std::clamp(Ratio, 0.f, 1.f);

	float SinValue = std::sinf(GameEngineMath::PIE * 0.5f * Ratio);

	float NowHeight = _MaxHeight * SinValue;
	EnemyPtr->SetHeight(NowHeight);
}



void EnemyStateBase::Update_SinHalfFall(float _Duration, float _MaxHeight /*= 80.f*/)
{
	Update_SinHalfFall(GetLiveTime(), _Duration, _MaxHeight);
}



void EnemyStateBase::Update_SinHalfFall(float _Timer, float _Duration, float _MaxHeight)
{
	float Ratio = (_Timer / _Duration);
	Ratio = std::clamp(Ratio, 0.f, 1.f);

	float HalfPI = GameEngineMath::PIE * 0.5f;

	//0.5파이 ~ 1파이
	float SinInput = HalfPI + (HalfPI * Ratio);
	float SinValue = std::sinf(SinInput);

	float NowHeight = _MaxHeight * SinValue;
	EnemyPtr->SetHeight(NowHeight);
}





bool EnemyStateBase::Update_AccMove(
	float _DeltaTime, float _Ratio, 
	const float4& _Dir, float _StartAcc)
{
	GameEngineTransform* EnemyTrans = EnemyPtr->GetTransform();

	_Ratio = std::clamp(_Ratio, 0.f, 1.f);
	float NowAcc = _StartAcc * (1.f - _Ratio);

	//다음에 움직일 위치
	float4 NextPos = EnemyTrans->GetLocalPosition();
	NextPos += (_Dir * NowAcc * _DeltaTime);

	//갈수 없는 곳이면 움직이지 않는다
	if (true == BGPtr->IsBlockPos(NextPos))
		return false;

	//갈수 없는 그리드라면 움직이지 않는다
	std::pair<int, int> NextGridPos = BGPtr->GetGridFromPos(NextPos);
	if (true == BGPtr->IsBlockGrid(NextGridPos.first, NextGridPos.second))
		return false;

	//움직인다
	EnemyTrans->SetLocalPosition(NextPos);
	return true;
}

void EnemyStateBase::OffMainCollider()
{
	MainCollider->Off();
}

void EnemyStateBase::OnMainCollider() 
{
	MainCollider->On();
}

bool EnemyStateBase::FarAttackExcute(int _Percent)
{
	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, 100);

	//확률을 뚫지 못한 경우
	if (_Percent < RandValue)
		return false;

	size_t FarAttack = GetEnemyFsm()->GetRandomFarAttack();

	//해당 Phase에서는 원거리 공격이 없는 경우
	if (-1 == FarAttack)
		return false;

	GetFSM()->ChangeState(FarAttack);
	return true;
}

