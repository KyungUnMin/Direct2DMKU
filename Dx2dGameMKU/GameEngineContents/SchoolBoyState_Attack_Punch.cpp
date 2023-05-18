#include "PrecompileHeader.h"
#include "SchoolBoyState_Attack_Punch.h"


#include "SchoolBoyFSM.h"
#include "FieldPlayer.h"

const std::string_view SchoolBoyState_Attack_Punch::AniName = "Attack_Punch";
const std::string_view SchoolBoyState_Attack_Punch::AniFileName = "SchoolBoy_Punch.png";
const std::pair<int, int> SchoolBoyState_Attack_Punch::AniCutFrame = std::pair<int, int>(5, 2);
const float SchoolBoyState_Attack_Punch::AniInterTime = 0.08f;

SchoolBoyState_Attack_Punch::SchoolBoyState_Attack_Punch()
{

}

SchoolBoyState_Attack_Punch::~SchoolBoyState_Attack_Punch()
{

}

void SchoolBoyState_Attack_Punch::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void SchoolBoyState_Attack_Punch::LoadAnimation()
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

void SchoolBoyState_Attack_Punch::CreateAnimation()
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


void SchoolBoyState_Attack_Punch::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue(float4::Right * 50.f);
}



void SchoolBoyState_Attack_Punch::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(SchoolBoyStateType::SideKick);

	//TODO
	//GetRenderer()
}



void SchoolBoyState_Attack_Punch::Attack()
{
	bool Result = FieldPlayer::GetPtr()->OnDamage(PlayerStateType::NormalDamaged_Face);
}