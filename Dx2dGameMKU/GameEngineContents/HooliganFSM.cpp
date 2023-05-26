#include "PrecompileHeader.h"
#include "HooliganFSM.h"

#include <GameEngineBase/GameEngineRandom.h>

//Movement
#include "HooliganState_Idle.h"
#include "HooliganState_Walk.h"
//#include "HooliganState_Ready.h"

//Attack
#include "HooliganState_Attack_CrossPunch.h"
#include "HooliganState_Attack_DodgeKick.h"
#include "HooliganState_Attack_JumpBackKick.h"
#include "HooliganState_Attack_SnapKick.h"

//Damaged
#include "HooliganState_NormalDamaged_Face.h"
#include "HooliganState_NormalDamaged_Stomach.h"
#include "HooliganState_NormalDamaged_Jaw.h"
#include "HooliganState_Damaged_BlowBack.h"
#include "HooliganState_Damaged_KnockDown.h"
#include "HooliganState_Damaged_WallHit.h"
#include "HooliganState_Damaged_WallOut.h"
#include "HooliganState_Damaged_Dazed.h"


const  std::string_view HooliganFSM::NormalDamaged_FileName = "Hooligan_GetHit.png";


const std::vector<HooliganStateType> HooliganFSM::AttackGroup =
{
	HooliganStateType::CrossPunch,
	HooliganStateType::DodgeKick,
	HooliganStateType::JumpBackKick,
	HooliganStateType::SnapKick
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
	//FSMBase::CreateState<HooliganState_Ready>(HooliganStateType::Ready);


	//Attack
	FSMBase::CreateState<HooliganState_Attack_CrossPunch>(HooliganStateType::CrossPunch);
	FSMBase::CreateState<HooliganState_Attack_DodgeKick>(HooliganStateType::DodgeKick);
	FSMBase::CreateState<HooliganState_Attack_JumpBackKick>(HooliganStateType::JumpBackKick);
	FSMBase::CreateState<HooliganState_Attack_SnapKick>(HooliganStateType::SnapKick);


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
