#include "PrecompileHeader.h"
#include "HooliganFSM.h"

#include <GameEngineBase/GameEngineRandom.h>

//Movement
#include "HooliganState_Idle.h"
#include "HooliganState_Walk.h"
#include "HooliganState_Ready.h"

//Attack
#include "HooliganState_Attack_AxeKick.h"
#include "HooliganState_Attack_Elbow.h"
#include "HooliganState_Attack_Punch.h"
#include "HooliganState_Attack_SideKick.h"

//Damaged
#include "HooliganState_NormalDamaged_Face.h"
#include "HooliganState_NormalDamaged_Stomach.h"
#include "HooliganState_NormalDamaged_Jaw.h"
#include "HooliganState_Damaged_BlowBack.h"
#include "HooliganState_Damaged_KnockDown.h"
#include "HooliganState_Damaged_WallHit.h"
#include "HooliganState_Damaged_WallOut.h"
#include "HooliganState_Damaged_Dazed.h"


const  std::string_view HooliganFSM::NormalDamaged_FileName = "Hooligan_Get_Hits.png";


const std::vector<HooliganStateType> HooliganFSM::AttackGroup =
{
	HooliganStateType::AxeKick,
	HooliganStateType::Elbow,
	HooliganStateType::Punch,
	HooliganStateType::SideKick
};

size_t HooliganFSM::GetRandomAttack()
{
	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(AttackGroup.size() - 1));
	return static_cast<size_t>(AttackGroup[RandValue]);
}




HooliganFSM::HooliganFSM()
{

}

HooliganFSM::~HooliganFSM()
{

}



void HooliganFSM::Init(FieldEnemyBase* _Enemy)
{
	EnemyFSMBase::Init(_Enemy);
	FSMBase::ResizeStates(HooliganStateType::COUNT);


	//Movement
	FSMBase::CreateState<HooliganState_Idle>(HooliganStateType::Idle);
	FSMBase::CreateState<HooliganState_Walk>(HooliganStateType::Walk);
	FSMBase::CreateState<HooliganState_Ready>(HooliganStateType::Ready);


	//Attack
	FSMBase::CreateState<HooliganState_Attack_AxeKick>(HooliganStateType::AxeKick);
	FSMBase::CreateState<HooliganState_Attack_Elbow>(HooliganStateType::Elbow);
	FSMBase::CreateState<HooliganState_Attack_Punch>(HooliganStateType::Punch);
	FSMBase::CreateState<HooliganState_Attack_SideKick>(HooliganStateType::SideKick);


	//Damaged
	FSMBase::CreateState<HooliganState_NormalDamaged_Face>(HooliganStateType::NormalDamaged_Face);
	FSMBase::CreateState<HooliganState_NormalDamaged_Stomach>(HooliganStateType::NormalDamaged_Stomach);
	FSMBase::CreateState<HooliganState_NormalDamaged_Jaw>(HooliganStateType::NormalDamaged_Jaw);
	FSMBase::CreateState<HooliganState_Damaged_BlowBack>(HooliganStateType::Damaged_BlowBack);
	FSMBase::CreateState<HooliganState_Damaged_KnockDown>(HooliganStateType::Damaged_KnockDown);
	FSMBase::CreateState<HooliganState_Damaged_WallHit>(HooliganStateType::Damaged_WallHit);
	FSMBase::CreateState<HooliganState_Damaged_WallOut>(HooliganStateType::Damaged_WallOut);
	FSMBase::CreateState<HooliganState_Damaged_Dazed>(HooliganStateType::Damaged_Dazed);




	FSMBase::ChangeState(HooliganStateType::Idle);
}
