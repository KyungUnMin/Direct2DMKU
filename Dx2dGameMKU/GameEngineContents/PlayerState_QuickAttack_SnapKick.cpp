#include "PrecompileHeader.h"
#include "PlayerState_QuickAttack_SnapKick.h"

#include "KeyMgr.h"
#include "DataMgr.h"

#include "PlayerFSM.h"
#include "FieldEnemyBase.h"

const std::string_view PlayerState_QuickAttack_SnapKick::AniName = "QuickAttack_SnapKick";
const std::string_view PlayerState_QuickAttack_SnapKick::AniFileName = "Player_QuickAttack_SnapKick_02.png";
const std::pair<int, int> PlayerState_QuickAttack_SnapKick::AniCutFrame = std::pair<int, int>(4, 2);
const float PlayerState_QuickAttack_SnapKick::AniInterTime = 0.06f;
const int PlayerState_QuickAttack_SnapKick::Damage = 5;

PlayerState_QuickAttack_SnapKick::PlayerState_QuickAttack_SnapKick()
{

}

PlayerState_QuickAttack_SnapKick::~PlayerState_QuickAttack_SnapKick()
{

}


void PlayerState_QuickAttack_SnapKick::Start()
{
	PlayerState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_QuickAttack_SnapKick::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Player");
	Dir.Move("Attack");
	Dir.Move("QuickAttack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void PlayerState_QuickAttack_SnapKick::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 6,
		.FrameInter = AniInterTime,
		.Loop = false
	});

	PlayerState_AttackBase::SetAttackCheckFrame(AniName, 2);
}

void PlayerState_QuickAttack_SnapKick::EnterState()
{
	PlayerState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	PlayerState_AttackBase::SetAttackColValue();
	TotalDamage = Damage + DataMgr::GetPlayerAtt();
}




void PlayerState_QuickAttack_SnapKick::Update(float _DeltaTime)
{
	PlayerState_AttackBase::Update(_DeltaTime);

	if (true == KeyMgr::IsDown(KeyNames::Z))
	{
		IsReserveChainAttack = true;
	}

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	if (false == IsReserveChainAttack)
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
		return;
	}

	GetFSM()->ChangeState(PlayerStateType::QuickAttack_BackKick);
	return;

	//TODO
}


void PlayerState_QuickAttack_SnapKick::ExitState()
{
	PlayerState_AttackBase::ExitState();

	IsReserveChainAttack = false;
}

void PlayerState_QuickAttack_SnapKick::Attack(FieldEnemyBase* _Enemy)
{
	DataMgr::PlusPlayerMP(Damage);
	_Enemy->OnDamage_Stomach(TotalDamage);
}
