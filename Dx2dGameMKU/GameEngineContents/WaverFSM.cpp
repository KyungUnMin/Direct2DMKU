#include "PrecompileHeader.h"
#include "WaverFSM.h"

#include <GameEngineBase/GameEngineRandom.h>

//Movement
#include "WaverState_Idle.h"
#include "WaverState_Walk.h"
//#include "WaverState_Ready.h"

//Attack
#include "WaverState_Attack_DiceSpike.h"
#include "WaverState_Attack_DoubleSlash.h"
#include "WaverState_Attack_Frog.h"
#include "WaverState_Attack_Kick.h"
#include "WaverState_Attack_Slash.h"
#include "WaverState_Attack_WindSlash.h"

//Damaged
#include "WaverState_NormalDamaged_Face.h"
#include "WaverState_NormalDamaged_Stomach.h"
#include "WaverState_NormalDamaged_Jaw.h"
#include "WaverState_Damaged_BlowBack.h"
#include "WaverState_Damaged_KnockDown.h"
#include "WaverState_Damaged_WallHit.h"
#include "WaverState_Damaged_WallOut.h"
#include "WaverState_Damaged_Dazed.h"


const  std::string_view WaverFSM::NormalDamaged_FileName = "Waver_GetHit.png";


const std::vector<WaverStateType> WaverFSM::AttackGroup =
{
	WaverStateType::DiceSpike,
	WaverStateType::DoubleSlash,
	WaverStateType::Frog,
	WaverStateType::Kick,
	WaverStateType::Slash,
	WaverStateType::WindSlash
};

size_t WaverFSM::GetRandomAttack()
{
	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(AttackGroup.size() - 1));
	return static_cast<size_t>(AttackGroup[RandValue]);
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
	//FSMBase::CreateState<WaverState_Ready>(WaverStateType::Ready);


	//Attack
	FSMBase::CreateState<WaverState_Attack_DiceSpike>(WaverStateType::DiceSpike);
	FSMBase::CreateState<WaverState_Attack_DoubleSlash>(WaverStateType::DoubleSlash);
	FSMBase::CreateState<WaverState_Attack_Frog>(WaverStateType::Frog);
	FSMBase::CreateState<WaverState_Attack_Kick>(WaverStateType::Kick);
	FSMBase::CreateState<WaverState_Attack_Slash>(WaverStateType::Slash);
	FSMBase::CreateState<WaverState_Attack_WindSlash>(WaverStateType::WindSlash);


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
