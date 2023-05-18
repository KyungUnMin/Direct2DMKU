#include "PrecompileHeader.h"
#include "SchoolBoyState_Attack_AxeKick.h"

#include "SchoolBoyFSM.h"
#include "FieldEnemyBase.h"
#include "FieldPlayer.h"
#include "DataMgr.h"

const std::string_view SchoolBoyState_Attack_AxeKick::AniName = "Attack_AxeKick";
const std::string_view SchoolBoyState_Attack_AxeKick::AniFileName = "SchoolBoy_Axe_Kick.png";
const std::pair<int, int> SchoolBoyState_Attack_AxeKick::AniCutFrame = std::pair<int, int>(5, 2);
const float SchoolBoyState_Attack_AxeKick::AniInterTime = 0.08f;

SchoolBoyState_Attack_AxeKick::SchoolBoyState_Attack_AxeKick()
{

}

SchoolBoyState_Attack_AxeKick::~SchoolBoyState_Attack_AxeKick()
{

}

void SchoolBoyState_Attack_AxeKick::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void SchoolBoyState_Attack_AxeKick::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("SchoolBoy");
	Dir.Move("Attack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void SchoolBoyState_Attack_AxeKick::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> EnemyRender = GetRenderer();

	EnemyRender->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 8,
		.FrameInter = AniInterTime
	});

	EnemyState_AttackBase::SetAttackCheckFrame(AniName, 3);
}




void SchoolBoyState_Attack_AxeKick::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue(float4::Right * 50.f);
}



void SchoolBoyState_Attack_AxeKick::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(SchoolBoyStateType::Elbow);
}


void SchoolBoyState_Attack_AxeKick::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage(PlayerStateType::NormalDamaged_Stomach);
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(-5);
}
