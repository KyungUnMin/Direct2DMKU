#include "PrecompileHeader.h"
#include "PlayerState_Walk.h"

#include "DataMgr.h"

#include "FieldPlayer.h"
#include "PlayerFSM.h"
#include "PlayerState_UniqueAttack_HyrricaneKick.h"
#include "PlayerState_UniqueAttack_DragonFeet.h"



const std::string_view PlayerState_Walk::AniName = "Walk";
const std::string_view PlayerState_Walk::AniFileName = "Player_Walk.png";
const std::pair<int, int> PlayerState_Walk::AniCutFrame = std::pair<int, int>(4, 3);
const float PlayerState_Walk::AniInterTime = 0.06f;

std::vector<KeyNames>  PlayerState_Walk::CheckArrows =
{
	KeyNames::RightArrow,
	KeyNames::LeftArrow,
	KeyNames::UpArrow,
	KeyNames::DownArrow,
};

PlayerState_Walk::PlayerState_Walk()
{

}

PlayerState_Walk::~PlayerState_Walk()
{

}

void PlayerState_Walk::Start()
{
	PlayerState_MovementBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void PlayerState_Walk::LoadAnimation()
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

void PlayerState_Walk::CreateAnimation() 
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime
	});
}


void PlayerState_Walk::EnterState()
{
	PlayerState_MovementBase::EnterState();

	CheckPressArrow(PressArrow);
	GetRenderer()->ChangeAnimation(AniName);
}



void PlayerState_Walk::CheckPressArrow(KeyNames& _SettingEnum)
{
	for (const KeyNames Arrow : CheckArrows)
	{
		if (false == KeyMgr::IsPress(Arrow))
			continue;

		_SettingEnum = Arrow;
	}
}


void PlayerState_Walk::Update(float _DeltaTime)
{
	PlayerState_MovementBase::Update(_DeltaTime);


	float NowTime = GetFSM()->GetFsmTime();

	//상하 이동을 빠르게 누른 경우
	if (NowTime < (LastTime + 0.1f) && (PressArrow == LastArrow))
	{
		if ((KeyNames::UpArrow == PressArrow) || (KeyNames::DownArrow == PressArrow))
		{
			GetFSM()->ChangeState(PlayerStateType::Movement_Avoid);
			return;
		}
	}


	//대시, 회피처리
	if (NowTime < (LastTime + 0.1f) && (PressArrow == LastArrow))
	{
		//좌우이동을 빠르게 누른 경우
		if ((KeyNames::RightArrow == PressArrow) || (KeyNames::LeftArrow == PressArrow))
		{
			IsNextDash = true;
			GetFSM()->ChangeState(PlayerStateType::Movement_Dash);
			return;
		}
	}

	

	//아이들 처리
	if (true == Check_Idle())
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
		return;
	}

	//방어
	if (true == KeyMgr::IsPress(KeyNames::LeftShift))
	{
		GetFSM()->ChangeState(PlayerStateType::Damaged_Block);
		return;
	}

	//일반 기본 공격
	if (true == KeyMgr::IsPress(KeyNames::Z))
	{
		GetFSM()->ChangeState(PlayerStateType::QuickAttack_Chop);
		return;
	}

	//특수 공격
	if (true == KeyMgr::IsPress(KeyNames::X))
	{
		GetFSM()->ChangeState(PlayerStateType::SpecialAttack_DAP);
		return;
	}


	//특수 스킬
	if (true == KeyMgr::IsPress(KeyNames::C))
	{
		int CurMp = DataMgr::GetPlayerMP();

		//허리케인 킥
		if (true == KeyMgr::IsPress(KeyNames::DownArrow))
		{
			if (PlayerState_UniqueAttack_HyrricaneKick::NeedMp <= CurMp)
			{
				GetFSM()->ChangeState(PlayerStateType::UniqueAttack_HyrricaneKick);
				return;
			}
		}

		//드래곤 킥
		else
		{
			if (PlayerState_UniqueAttack_DragonFeet::NeedMp <= CurMp)
			{
				GetFSM()->ChangeState(PlayerStateType::UniqueAttack_DragonFeet);
				return;
			}
		}

	}


	//점프 처리
	if (true == KeyMgr::IsPress(KeyNames::Space))
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_Jump);
		return;
	}
	
	


	

	//실제 이동
	PlayerState_MovementBase::Update_Move(_DeltaTime);
}


void PlayerState_Walk::ExitState()
{
	PlayerState_MovementBase::ExitState();

	LastArrow = PressArrow;
			
	if(true == IsNextDash)
	{
		IsNextDash = false;
		LastTime = GetFSM()->GetFsmTime() + 0.5f;
	}
	else
	{
		LastTime = GetFSM()->GetFsmTime();
	}
}

