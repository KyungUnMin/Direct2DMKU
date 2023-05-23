#include "PrecompileHeader.h"
#include "CheerleaderState_Attack_SideKick.h"

#include "DataMgr.h"

#include "CheerleaderFSM.h"
#include "FieldPlayer.h"

const std::string_view CheerleaderState_Attack_SideKick::AniName = "Attack_SideKick";
const std::string_view CheerleaderState_Attack_SideKick::AniFileName = "Cheerleader_Side_Kick.png";
const std::pair<int, int> CheerleaderState_Attack_SideKick::AniCutFrame = std::pair<int, int>(5, 2);
const float CheerleaderState_Attack_SideKick::AniInterTime = 0.08f;
const int CheerleaderState_Attack_SideKick::Damage = 5;

CheerleaderState_Attack_SideKick::CheerleaderState_Attack_SideKick()
{

}

CheerleaderState_Attack_SideKick::~CheerleaderState_Attack_SideKick()
{

}

void CheerleaderState_Attack_SideKick::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void CheerleaderState_Attack_SideKick::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Cheerleader");
	Dir.Move("Attack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void CheerleaderState_Attack_SideKick::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 6,
		.FrameInter = AniInterTime
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 2);
}


void CheerleaderState_Attack_SideKick::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue();
}


void CheerleaderState_Attack_SideKick::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//���� ���� �ۿ� �ִٸ� idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(CheerleaderStateType::Idle);
		return;
	}

	//1/n�� Idle, �������� ����� �ٸ� ����
	CheerleaderStateType RandomAttack = CheerleaderFSM::GetRandomAttack();
	if (GetStateEnum<CheerleaderStateType>() == RandomAttack)
	{
		GetFSM()->ChangeState(CheerleaderStateType::Idle);
	}
	else
	{
		GetFSM()->ChangeState(RandomAttack);
	}
}




void CheerleaderState_Attack_SideKick::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_BlowBack();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}
