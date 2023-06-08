#include "PrecompileHeader.h"
#include "FieldPlayer.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "RCG_GameCore.h"
#include "RCGEnums.h"
#include "KeyMgr.h"

#include "HitEffect.h"


FieldPlayer* FieldPlayer::GPtr = nullptr;

FieldPlayer::FieldPlayer()
{
	//Start�κ��� ���� ���⼭�� ����
	GPtr = this;
}

FieldPlayer::~FieldPlayer()
{
	if (this == GPtr)
	{
		GPtr = nullptr;
	}
}





void FieldPlayer::Start()
{
	FieldActorBase::Start();

	FieldActorBase::CreateColliders(CollisionOrder::PlayerMain);
	Fsm.Init();
}



void FieldPlayer::Update(float _DeltaTime) 
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	//FSM�� �̿��� �����̱� �� ��ġ�� ����(���� �������� ��ġ��)
	PrevPos = GetTransform()->GetWorldPosition();

	FieldActorBase::Update(_DeltaTime);
	CheckDirection();
	Fsm.Update(_DeltaTime);
}


void FieldPlayer::CheckDirection()
{
	if (true == IsFixedDirection)
	{
		IsFixedDirection = false;
		return;
	}

	//�̹� �������� �÷��̾� ����, true�϶� ������, false�� ����
	bool NowDir = RenderDir;

	if (true == KeyMgr::IsPress(KeyNames::RightArrow))
	{
		NowDir = true;
	}
	else if (true == KeyMgr::IsPress(KeyNames::LeftArrow))
	{
		NowDir = false;
	}

	RenderDir = NowDir;
}




void FieldPlayer::SetDirection(bool IsRight)
{
	RenderDir = IsRight;
	IsFixedDirection = true;

	GameEngineTransform* TransPtr = GetTransform();
	if (true == RenderDir)
	{
		TransPtr->SetLocalPositiveScaleX();
	}
	else
	{
		TransPtr->SetLocalNegativeScaleX();
	}
}



void FieldPlayer::Render(float _DeltaTime)
{
	FieldActorBase::Render(_DeltaTime);

	Fsm.Render(_DeltaTime);
}




bool FieldPlayer::IsDashing() const
{
	//����  ��� ���¶�� true
	PlayerStateType NowState = Fsm.GetNowState<PlayerStateType>();
	if (PlayerStateType::Movement_Dash == NowState)
		return true;
	
	//������, �������� ���°� �ƴ϶�� false (Jump, Fall �϶��� ���� ���� �ϴ� �κ��� ����)
	if ((PlayerStateType::Movement_Jump != NowState) && (PlayerStateType::Movement_Fall != NowState))
		return false;

	//���� Jump, Fall �鼭 ������ �������� ��ø� true
	PlayerStateType LastMoveType = Fsm.GetLastMovement();
	if (PlayerStateType::Movement_Dash == LastMoveType)
		return true;

	return false;
}







//TODO List
	//����ϰ� �ִ� �����϶�,
	//�̹� ���ݹް� �ִ� �����϶�,
	//�и����϶�
	//����׿� ���ñ� ���
	//���߿� �� �������� �ָ� ������ Damaged


bool FieldPlayer::OnDamage_Face(bool _IsDefenceBreak/* = false*/)
{
	if (false == CanPlayerDamage(_IsDefenceBreak))
		return false;

	CreateDamageEffect(DamageEffect_FaceOffset);

	//���߿� �� ������ ���󰡱�
	if (0.f < GetHeight())
	{
		Fsm.ChangeState(static_cast<size_t>(PlayerStateType::Damaged_BlowBack));
		return true;
	}


	Fsm.ChangeState(static_cast<size_t>(PlayerStateType::NormalDamaged_Face));
	return true;
}

bool FieldPlayer::OnDamage_Stomach(bool _IsDefenceBreak /*= false*/)
{
	if (false == CanPlayerDamage(_IsDefenceBreak))
		return false;

	CreateDamageEffect(DamageEffect_StomachOffset);

	//���߿� �� ������ ���󰡱�
	if (0.f < GetHeight())
	{
		Fsm.ChangeState(static_cast<size_t>(PlayerStateType::Damaged_BlowBack));
		return true;
	}


	Fsm.ChangeState(static_cast<size_t>(PlayerStateType::NormalDamaged_Stomach));
	return true;
}

bool FieldPlayer::OnDamage_Jaw(bool _IsDefenceBreak /*= false*/)
{
	if (false == CanPlayerDamage(_IsDefenceBreak))
		return false;

	CreateDamageEffect(DamageEffect_JawOffset);

	//���߿� �� ������ ���󰡱�
	if (0.f < GetHeight())
	{
		Fsm.ChangeState(static_cast<size_t>(PlayerStateType::Damaged_BlowBack));
		return true;
	}


	Fsm.ChangeState(static_cast<size_t>(PlayerStateType::NormalDamaged_Jaw));
	return true;
}

bool FieldPlayer::OnDamage_BlowBack(bool _IsDefenceBreak /*= false*/)
{
	if (false == CanPlayerDamage(_IsDefenceBreak))
		return false;

	CreateDamageEffect(DamageEffect_BlowBackOffset);

	Fsm.ChangeState(static_cast<size_t>(PlayerStateType::Damaged_BlowBack));
	return true;
}

bool FieldPlayer::OnDamage_Stun(bool _IsDefenceBreak /*= false*/)
{
	if (false == CanPlayerDamage(_IsDefenceBreak))
		return false;

	CreateDamageEffect(DamageEffect_FaceOffset);

	Fsm.ChangeState(static_cast<size_t>(PlayerStateType::Damaged_Stun));
	return true;
}


bool FieldPlayer::CanPlayerDamage(bool _IsBreakDefence /*= false*/)
{
	//��� ���ð� �ƴϸ鼭, �÷��̾ ������϶�
	if (false == _IsBreakDefence)
	{
		if (true == Fsm.OnDamageInBlock())
			return false;
	}

	//�������ִ� �����϶�
	if (PlayerStateType::Damaged_BlowBack == Fsm.GetNowState<PlayerStateType>())
		return false;

	return true;
}

void FieldPlayer::CreateDamageEffect(const float4& _Offset)
{
	std::shared_ptr<HitEffect> Effect = GetLevel()->CreateActor<HitEffect>(UpdateOrder::Effect);
	GameEngineTransform* EffectTrans = Effect->GetTransform();
	float4 EffectPos = GetTransform()->GetWorldPosition() + _Offset;
	EffectTrans->SetLocalPosition(EffectPos);
	Effect->OffHitAir();
}

void FieldPlayer::LevelChangeEnd()
{
	FieldActorBase::LevelChangeEnd();

	//�÷��̾� ���̵� ���·� ����
	Fsm.ChangeState(static_cast<size_t>(PlayerStateType::Movement_Idle));
}



float4 FieldPlayer::GetMoveDirVec()
{
	float4 NowPos = GetTransform()->GetWorldPosition();
	return (NowPos - PrevPos);
}