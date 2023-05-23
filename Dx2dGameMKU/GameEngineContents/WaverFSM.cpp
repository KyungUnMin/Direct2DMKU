#include "PrecompileHeader.h"
#include "WaverFSM.h"

#include <GameEngineBase/GameEngineRandom.h>

//Movement
#include "WaverState_Idle.h"
#include "WaverState_Walk.h"
#include "WaverState_Ready.h"

//Attack
#include "WaverState_Attack_AxeKick.h"
#include "WaverState_Attack_Elbow.h"
#include "WaverState_Attack_Punch.h"
#include "WaverState_Attack_SideKick.h"

//Damaged
#include "WaverState_NormalDamaged_Face.h"
#include "WaverState_NormalDamaged_Stomach.h"
#include "WaverState_NormalDamaged_Jaw.h"
#include "WaverState_Damaged_BlowBack.h"
#include "WaverState_Damaged_KnockDown.h"
#include "WaverState_Damaged_WallHit.h"
#include "WaverState_Damaged_WallOut.h"
#include "WaverState_Damaged_Dazed.h"


const  std::string_view WaverFSM::NormalDamaged_FileName = "Waver_Get_Hits.png";


const std::vector<WaverStateType> WaverFSM::AttackGroup =
{
	WaverStateType::AxeKick,
	WaverStateType::Elbow,
	WaverStateType::Punch,
	WaverStateType::SideKick
};

WaverStateType WaverFSM::GetRandomAttack()
{
	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(AttackGroup.size() - 1));
	return AttackGroup[RandValue];
}




WaverFSM::WaverFSM()
{

}

WaverFSM::~WaverFSM()
{

}



void WaverFSM::Init(FieldEnemyBase* _Enemy)
{
	EnemyFSMBase::Init(_Enemy);
	FSMBase::ResizeStates(WaverStateType::COUNT);


	//Movement
	FSMBase::CreateState<WaverState_Idle>(WaverStateType::Idle);
	FSMBase::CreateState<WaverState_Walk>(WaverStateType::Walk);
	FSMBase::CreateState<WaverState_Ready>(WaverStateType::Ready);


	//Attack
	FSMBase::CreateState<WaverState_Attack_AxeKick>(WaverStateType::AxeKick);
	FSMBase::CreateState<WaverState_Attack_Elbow>(WaverStateType::Elbow);
	FSMBase::CreateState<WaverState_Attack_Punch>(WaverStateType::Punch);
	FSMBase::CreateState<WaverState_Attack_SideKick>(WaverStateType::SideKick);


	//Damaged
	FSMBase::CreateState<WaverState_NormalDamaged_Face>(WaverStateType::NormalDamaged_Face);
	FSMBase::CreateState<WaverState_NormalDamaged_Stomach>(WaverStateType::NormalDamaged_Stomach);
	FSMBase::CreateState<WaverState_NormalDamaged_Jaw>(WaverStateType::NormalDamaged_Jaw);
	FSMBase::CreateState<WaverState_Damaged_BlowBack>(WaverStateType::Damaged_BlowBack);
	FSMBase::CreateState<WaverState_Damaged_KnockDown>(WaverStateType::Damaged_KnockDown);
	FSMBase::CreateState<WaverState_Damaged_WallHit>(WaverStateType::Damaged_WallHit);
	FSMBase::CreateState<WaverState_Damaged_WallOut>(WaverStateType::Damaged_WallOut);
	FSMBase::CreateState<WaverState_Damaged_Dazed>(WaverStateType::Damaged_Dazed);




	FSMBase::ChangeState(WaverStateType::Idle);
}
