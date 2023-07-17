#include "PrecompileHeader.h"
#include "FieldPlayer.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>



#include "RCG_GameCore.h"
#include "RCGEnums.h"
#include "RCGDefine.h"
#include "KeyMgr.h"
#include "DataMgr.h"

#include "HitEffect.h"
#include "FieldLevelBase.h"


FieldPlayer* FieldPlayer::GPtr = nullptr;
const std::string_view FieldPlayer::LevelUpText_FileName = "PlayerLevelUpHeadUI.png";

FieldPlayer::FieldPlayer()
{
	//Start부분을 위해 여기서도 설정
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
	CreateLevelUpRender();
}

void FieldPlayer::CreateLevelUpRender()
{
	if (nullptr == GameEngineSprite::Find(LevelUpText_FileName))
	{
		GameEngineDirectory Dir;
		RCGDefine::MoveContentPath(Dir, ResType::Image);
		Dir.Move("Character");
		Dir.Move("Player");
		GameEnginePath Path = Dir.GetPlusFileName(LevelUpText_FileName);
		GameEngineSprite::LoadSheet(Path.GetFullPath(), 5, 1);
	}

	LevelUpText = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	LevelUpText->CreateAnimation
	({
		.AnimationName = LevelUpText_FileName,
		.SpriteName = LevelUpText_FileName,
		.Loop = false,
		.FrameTime = {0.1f, 0.1f,0.1f,1.f,0.1f},
	});

	LevelUpText->Off();
	LevelUpText->SetAnimationStartEvent(LevelUpText_FileName, 4, [this]()
	{
		LevelUpText->Off();
	});

	
	const float4 RenderOffset = { 0.f, 250.f };
	const float4 RenderScale = float4{ 256.f, 256.f, 1.f };

	GameEngineTransform* RenderTrans = LevelUpText->GetTransform();
	RenderTrans->SetLocalPosition(RenderOffset);
	RenderTrans->SetWorldScale(RenderScale);

	DataMgr::PushLevelUpCallBack([this]() ->bool
	{
		if (GetLevel() != FieldLevelBase::GetPtr().get())
			return false;

		LevelUpText->On();
		LevelUpText->ChangeAnimation(LevelUpText_FileName);
		return false;
	});
}



void FieldPlayer::Update(float _DeltaTime) 
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	//FSM을 이용해 움직이기 전 위치값 저장(이전 프레임의 위치값)
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

	//이번 프레임의 플레이어 방향, true일때 오른쪽, false면 왼쪽
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
	//지금  대시 상태라면 true
	PlayerStateType NowState = Fsm.GetNowState<PlayerStateType>();
	if (PlayerStateType::Movement_Dash == NowState)
		return true;
	
	//점프나, 떨어지는 상태가 아니라면 false (Jump, Fall 일때는 따로 봐야 하는 부분이 있음)
	if ((PlayerStateType::Movement_Jump != NowState) && (PlayerStateType::Movement_Fall != NowState))
		return false;

	//지금 Jump, Fall 면서 마지막 움직임이 대시면 true
	PlayerStateType LastMoveType = Fsm.GetLastMovement();
	if (PlayerStateType::Movement_Dash == LastMoveType)
		return true;

	return false;
}




bool FieldPlayer::OnDamage_Face(bool _IsDefenceBreak/* = false*/, bool _IsIgnoreBlow /*= false*/)
{
	if (false == CanPlayerDamage(_IsDefenceBreak, _IsIgnoreBlow))
		return false;

	CreateDamageEffect(DamageEffect_FaceOffset);

	//공중에 떠 있을땐 날라가기
	if (0.f < GetHeight())
	{
		Fsm.ChangeState(static_cast<size_t>(PlayerStateType::Damaged_BlowBack));
		return true;
	}


	Fsm.ChangeState(static_cast<size_t>(PlayerStateType::NormalDamaged_Face));
	return true;
}

bool FieldPlayer::OnDamage_Stomach(bool _IsDefenceBreak /*= false*/, bool _IsIgnoreBlow /*= false*/)
{
	if (false == CanPlayerDamage(_IsDefenceBreak, _IsIgnoreBlow))
		return false;

	CreateDamageEffect(DamageEffect_StomachOffset);

	//공중에 떠 있을땐 날라가기
	if (0.f < GetHeight())
	{
		Fsm.ChangeState(static_cast<size_t>(PlayerStateType::Damaged_BlowBack));
		return true;
	}


	Fsm.ChangeState(static_cast<size_t>(PlayerStateType::NormalDamaged_Stomach));
	return true;
}

bool FieldPlayer::OnDamage_Jaw(bool _IsDefenceBreak /*= false*/, bool _IsIgnoreBlow /*= false*/)
{
	if (false == CanPlayerDamage(_IsDefenceBreak, _IsIgnoreBlow))
		return false;

	CreateDamageEffect(DamageEffect_JawOffset);

	//공중에 떠 있을땐 날라가기
	if (0.f < GetHeight())
	{
		Fsm.ChangeState(static_cast<size_t>(PlayerStateType::Damaged_BlowBack));
		return true;
	}


	Fsm.ChangeState(static_cast<size_t>(PlayerStateType::NormalDamaged_Jaw));
	return true;
}

bool FieldPlayer::OnDamage_BlowBack(bool _IsDefenceBreak /*= false*/, bool _IsIgnoreBlow /*= false*/)
{
	if (false == CanPlayerDamage(_IsDefenceBreak, _IsIgnoreBlow))
		return false;

	CreateDamageEffect(DamageEffect_BlowBackOffset);

	Fsm.ChangeState(static_cast<size_t>(PlayerStateType::Damaged_BlowBack));
	return true;
}

bool FieldPlayer::OnDamage_Stun(bool _IsDefenceBreak /*= false*/, bool _IsIgnoreBlow /*= false*/)
{
	if (false == CanPlayerDamage(_IsDefenceBreak, _IsIgnoreBlow))
		return false;

	CreateDamageEffect(DamageEffect_FaceOffset);

	Fsm.ChangeState(static_cast<size_t>(PlayerStateType::Damaged_Stun));
	return true;
}


bool FieldPlayer::CanPlayerDamage(bool _IsBreakDefence /*= false*/, bool _IsIgnoreBlow /*= false*/)
{
	//방어 무시가 아니면서, 플레이어가 방어중일때
	if (false == _IsBreakDefence)
	{
		if (true == Fsm.OnDamageInBlock())
			return false;
	}

	//쓰러져있는 상태를 무시하지 않으면서
	if (false == _IsIgnoreBlow)
	{
		//쓰러져있는 상태일때
		if (PlayerStateType::Damaged_BlowBack == Fsm.GetNowState<PlayerStateType>())
			return false;
	}

	

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

	//플레이어 아이들 상태로 변경
	Fsm.ChangeState(static_cast<size_t>(PlayerStateType::Movement_Idle));
	LevelUpText->Off();
}



float4 FieldPlayer::GetMoveDirVec()
{
	float4 NowPos = GetTransform()->GetWorldPosition();
	return (NowPos - PrevPos);
}




bool FieldPlayer::IsBlowing() const
{
	return PlayerStateType::Damaged_BlowBack == Fsm.GetNowState<PlayerStateType>();
}

bool FieldPlayer::IsStuned() const
{
	return PlayerStateType::Damaged_Stun == Fsm.GetNowState<PlayerStateType>();
}

void FieldPlayer::Look(const float4& _LookPos)
{
	FieldActorBase::Look(_LookPos);

	//true일때 오른쪽을 바라본다
	RenderDir = (0.f < GetTransform()->GetLocalScale().x);
}