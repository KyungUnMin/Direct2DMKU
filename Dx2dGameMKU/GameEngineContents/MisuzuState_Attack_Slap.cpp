#include "PrecompileHeader.h"
#include "MisuzuState_Attack_Slap.h"

#include "DataMgr.h"

#include "MisuzuFSM.h"
#include "FieldPlayer.h"
#include "FieldCamController.h"

const std::string_view MisuzuState_Attack_Slap::AniName = "Attack_Slap";
const std::string_view MisuzuState_Attack_Slap::AniFileName = "Misuzu_Slap.png";
const std::pair<int, int> MisuzuState_Attack_Slap::AniCutFrame = std::pair<int, int>(5, 3);
const float MisuzuState_Attack_Slap::AniInterTime = 0.08f;
const int MisuzuState_Attack_Slap::Damage = 5;
const int MisuzuState_Attack_Slap::AttackFrm = 8;

MisuzuState_Attack_Slap::MisuzuState_Attack_Slap()
{

}

MisuzuState_Attack_Slap::~MisuzuState_Attack_Slap()
{

}

void MisuzuState_Attack_Slap::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void MisuzuState_Attack_Slap::LoadAnimation()
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

void MisuzuState_Attack_Slap::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 13,
		.FrameInter = AniInterTime,
		.Loop = false,
		});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, AttackFrm);
}




void MisuzuState_Attack_Slap::EnterState()
{
	BossState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue(float4{50.f, 50.f}, float4::One * 150.f);
}



void MisuzuState_Attack_Slap::Update(float _DeltaTime)
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



void MisuzuState_Attack_Slap::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_Face();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}
