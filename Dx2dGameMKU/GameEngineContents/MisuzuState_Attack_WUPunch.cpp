#include "PrecompileHeader.h"
#include "MisuzuState_Attack_WUPunch.h"

#include "DataMgr.h"

#include "MisuzuFSM.h"
#include "FieldPlayer.h"
#include "FieldLevelBase.h"
#include "FieldCamController.h"

const std::string_view MisuzuState_Attack_WUPunch::AniName = "Attack_WUPunch";
const std::string_view MisuzuState_Attack_WUPunch::AniFileName = "Misuzu_WUPunch.png";
const std::pair<int, int> MisuzuState_Attack_WUPunch::AniCutFrame = std::pair<int, int>(5, 6);
const float MisuzuState_Attack_WUPunch::AniInterTime = 0.08f;
const int MisuzuState_Attack_WUPunch::Damage = 30;
const int MisuzuState_Attack_WUPunch::AttackFrm = 17;

MisuzuState_Attack_WUPunch::MisuzuState_Attack_WUPunch()
{

}

MisuzuState_Attack_WUPunch::~MisuzuState_Attack_WUPunch()
{

}

void MisuzuState_Attack_WUPunch::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();

	CamCtrl = &(FieldLevelBase::GetPtr()->GetCameraController());
}

void MisuzuState_Attack_WUPunch::LoadAnimation()
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

void MisuzuState_Attack_WUPunch::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 26,
		.FrameInter = AniInterTime
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, AttackFrm);
	Render->SetAnimationStartEvent(AniName, AttackFrm + 1, [this]()
	{
		CamCtrl->SetZoom(CamCtrl->ZoomOrigin, 0.1f);
	});
}




void MisuzuState_Attack_WUPunch::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue();
	
	CamCtrl->SetZoom(0.95f, AniInterTime * static_cast<float>(AttackFrm));
}



void MisuzuState_Attack_WUPunch::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

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



void MisuzuState_Attack_WUPunch::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage_BlowBack();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}

void MisuzuState_Attack_WUPunch::ExitState()
{
	EnemyState_AttackBase::ExitState();

	CamCtrl->SetZoom(CamCtrl->ZoomOrigin, 0.1f);
}