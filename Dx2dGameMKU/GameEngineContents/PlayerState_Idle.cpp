#include "PrecompileHeader.h"
#include "PlayerState_Idle.h"

#include "KeyMgr.h"
#include "PlayerFSM.h"

const std::string_view PlayerState_Idle::AniName = "Idle";
const std::string_view PlayerState_Idle::AniFileName = "Player_Idle.png";
const std::pair<int, int> PlayerState_Idle::AniCutFrame = std::pair<int, int>(4, 3);
const float PlayerState_Idle::AniInterTime = 0.08f;

PlayerState_Idle::PlayerState_Idle()
{

}

PlayerState_Idle::~PlayerState_Idle()
{

}



void PlayerState_Idle::Start()
{
	PlayerState_MovementBase::Start();

	SetArrowKey();
	LoadAnimation();
	CreateAnimation();
}


void PlayerState_Idle::SetArrowKey()
{
	ArrowKeyNames.reserve(4);
	ArrowKeyNames.push_back(KeyNames::UpArrow);
	ArrowKeyNames.push_back(KeyNames::DownArrow);
	ArrowKeyNames.push_back(KeyNames::RightArrow);
	ArrowKeyNames.push_back(KeyNames::LeftArrow);
}



void PlayerState_Idle::LoadAnimation()
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



void PlayerState_Idle::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime
	});
}




void PlayerState_Idle::EnterState()
{
	PlayerState_MovementBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}




void PlayerState_Idle::Update(float _DeltaTime)
{
	PlayerState_MovementBase::Update(_DeltaTime);
	

	//이동
	for (KeyNames Arrow : ArrowKeyNames)
	{
		if (false == KeyMgr::IsPress(Arrow))
			continue;

		GetFSM()->ChangeState(PlayerStateType::Movement_Walk);
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
		GetFSM()->ChangeState(PlayerStateType::SpecialAttack_AxeKick);
		return;
	}


	//특수 스킬
	if (true == KeyMgr::IsPress(KeyNames::C))
	{
		GetFSM()->ChangeState(PlayerStateType::UniqueAttack_DragonFeet);
		return;
	}


	


	//점프
	if (true == KeyMgr::IsPress(KeyNames::Space))
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_Jump);
		return;
	}

}



