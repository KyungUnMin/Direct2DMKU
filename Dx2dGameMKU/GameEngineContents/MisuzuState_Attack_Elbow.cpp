#include "PrecompileHeader.h"
#include "MisuzuState_Attack_Elbow.h"

#include "DataMgr.h"
#include "SoundMgr.h"

#include "MisuzuFSM.h"
#include "FieldPlayer.h"

const std::string_view MisuzuState_Attack_Elbow::AniName = "Attack_Elbow";
const std::string_view MisuzuState_Attack_Elbow::AniFileName = "Misuzu_Elbow.png";
const std::pair<int, int> MisuzuState_Attack_Elbow::AniCutFrame = std::pair<int, int>(5, 3);
const float MisuzuState_Attack_Elbow::AniInterTime = 0.08f;
const int MisuzuState_Attack_Elbow::Damage = 5;

MisuzuState_Attack_Elbow::MisuzuState_Attack_Elbow()
{
	
}

MisuzuState_Attack_Elbow::~MisuzuState_Attack_Elbow()
{

}

void MisuzuState_Attack_Elbow::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void MisuzuState_Attack_Elbow::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Misuzu");
	Dir.Move("Attack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void MisuzuState_Attack_Elbow::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 10,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	Render->SetAnimationStartEvent(AniName, 4, []()
	{
		SoundMgr::PlaySFX("Enemy_CommonAttack.wav");
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 5);
}


void MisuzuState_Attack_Elbow::EnterState()
{
	BossState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);

	EnemyState_AttackBase::SetAttackColValue();
}



void MisuzuState_Attack_Elbow::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;


	//일정 범위 밖에 있다면 idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(MisuzuStateType::Idle);
		return;
	}

	//1/n로 Idle, 나머지는 현재와 다른 공격
	MisuzuStateType RandomAttack = static_cast<MisuzuStateType>(GetEnemyFsm()->GetRandomAttack());
	if (GetStateEnum<MisuzuStateType>() == RandomAttack)
	{
		GetFSM()->ChangeState(MisuzuStateType::Idle);
	}
	else
	{
		GetFSM()->ChangeState(RandomAttack);
	}
}



void MisuzuState_Attack_Elbow::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_Face(Damage);
	
}
