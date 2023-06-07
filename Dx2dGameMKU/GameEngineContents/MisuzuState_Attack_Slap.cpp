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
const int MisuzuState_Attack_Slap::Damage = 10;
const int MisuzuState_Attack_Slap::AttackFrm = 8;

MisuzuState_Attack_Slap::MisuzuState_Attack_Slap()
{

}

MisuzuState_Attack_Slap::~MisuzuState_Attack_Slap()
{

}

void MisuzuState_Attack_Slap::Start()
{
	EnemyState_AttackBase::Start();

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
		.FrameInter = AniInterTime
		});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, AttackFrm);
}




void MisuzuState_Attack_Slap::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue();
}



void MisuzuState_Attack_Slap::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//���� ���� �ۿ� �ִٸ� idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(MisuzuStateType::Idle);
		return;
	}

	//1/n�� Idle, �������� ����� �ٸ� ����
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
