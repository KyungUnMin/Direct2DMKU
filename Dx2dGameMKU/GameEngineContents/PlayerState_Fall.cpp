#include "PrecompileHeader.h"
#include "PlayerState_Fall.h"

#include "FieldPlayer.h"
#include "PlayerFSM.h"
#include "PlayerState_Dash.h"

const std::string_view PlayerState_Fall::AniName = "Fall";
const std::string_view PlayerState_Fall::AniFileName = "Player_Fall.png";
const std::pair<int, int> PlayerState_Fall::AniCutFrame = std::pair<int, int>(2, 1);
const float PlayerState_Fall::AniInterTime = 0.08f;

PlayerState_Fall::PlayerState_Fall()
{

}

PlayerState_Fall::~PlayerState_Fall()
{

}

void PlayerState_Fall::Start()
{
	PlayerState_MovementBase::Start();

	FsmPtr = GetConvertFSM<PlayerFSM>();
	LoadAnimation();
	CreateAnimation();
}


void PlayerState_Fall::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Player");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}


void PlayerState_Fall::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime,
		.Loop = false
	});
}



void PlayerState_Fall::EnterState()
{
	PlayerState_MovementBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnterHeight = FieldPlayer::GetPtr()->GetHeight();

	//이전에 움직임이 대시였는지 걷기였는지
	PrevMoveState = static_cast<size_t>(FsmPtr->GetLastMovement());
}


void PlayerState_Fall::Update(float _DeltaTime)
{
	PlayerState_MovementBase::Update(_DeltaTime);

	float Ratio = (GetLiveTime() / Duration);
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);

	float CosRadian = GameEngineMath::PIE * ClampRatio * 0.5f;
	float NowHeight = EnterHeight * cosf(CosRadian);

	FieldPlayer::GetPtr()->SetHeight(NowHeight);


	//이전에 움직임이 대시였는지 걷기였는지
	PlayerStateType PrevMoveStyle = static_cast<PlayerStateType>(PrevMoveState);
	if (1.f < Ratio)
	{
		//이전에 Dash였으면 대시로 상태 변경
		if (PlayerStateType::Movement_Dash == PrevMoveStyle)
		{
			GetFSM()->ChangeState(PlayerStateType::Movement_Dash);
		}
		//이전에 Walk였으면 대시로 상태 변경
		else
		{
			GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
		}

		return;
	}

	//이전에 Dash였으면 대시 속도로 이동
	if (PlayerStateType::Movement_Dash == PrevMoveStyle)
	{
		PlayerState_MovementBase::Update_Move(_DeltaTime, PlayerState_Dash::DashSpeed);
	}

	//이전에 Walk였으면 걷기 속도로 이동
	else
	{
		PlayerState_MovementBase::Update_Move(_DeltaTime);
	}
}

