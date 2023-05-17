#include "PrecompileHeader.h"
#include "SchoolBoyState_Attack_AxeKick.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "SchoolBoyFSM.h"
#include "FieldEnemyBase.h"

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
	EnemyStateBase::Start();

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
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 8,
		.FrameInter = AniInterTime
	});
}



void SchoolBoyState_Attack_AxeKick::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void SchoolBoyState_Attack_AxeKick::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(SchoolBoyStateType::Elbow);

	//TODO
	//GetRenderer()
}



