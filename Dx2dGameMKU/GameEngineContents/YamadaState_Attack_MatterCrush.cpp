#include "PrecompileHeader.h"
#include "YamadaState_Attack_MatterCrush.h"

#include "DataMgr.h"

#include "YamadaFSM.h"
#include "FieldPlayer.h"
#include "FieldCamController.h"

const std::string_view YamadaState_Attack_MatterCrush::AniName = "Attack_MatterCrusher";
const std::string_view YamadaState_Attack_MatterCrush::AniFileName = "Yamada_MatterCrusher.png";
const std::pair<int, int> YamadaState_Attack_MatterCrush::AniCutFrame = std::pair<int, int>(5, 4);
const float YamadaState_Attack_MatterCrush::AniInterTime = 0.08f;

YamadaState_Attack_MatterCrush::YamadaState_Attack_MatterCrush()
{

}

YamadaState_Attack_MatterCrush::~YamadaState_Attack_MatterCrush()
{

}

void YamadaState_Attack_MatterCrush::Start()
{
	BossState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void YamadaState_Attack_MatterCrush::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Yamada");
	Dir.Move("Attack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void YamadaState_Attack_MatterCrush::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 17,
		.FrameInter = AniInterTime,
		.Loop = false,
	});
}




void YamadaState_Attack_MatterCrush::EnterState()
{
	BossState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}



void YamadaState_Attack_MatterCrush::Update(float _DeltaTime)
{
	BossState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//일정 범위 밖에 있다면 idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(YamadaStateType::Idle);
		return;
	}

	//1/n로 Idle, 나머지는 현재와 다른 공격
	YamadaStateType RandomAttack = static_cast<YamadaStateType>(GetEnemyFsm()->GetRandomAttack());
	if (GetStateEnum<YamadaStateType>() == RandomAttack)
	{
		GetFSM()->ChangeState(YamadaStateType::Idle);
	}
	else
	{
		GetFSM()->ChangeState(RandomAttack);
	}
}



//
//
//
//void YamadaState_Attack_MatterCrush::Attack()
//{
//	bool Result = FieldPlayer::GetPtr()->OnDamage_Face();
//	if (false == Result)
//		return;
//
//	DataMgr::MinusPlayerHP(Damage);
//}
