#include "PrecompileHeader.h"
#include "CopFSM.h"

#include <GameEngineBase/GameEngineRandom.h>

//Movement
#include "CopState_Idle.h"
#include "CopState_Walk.h"
#include "CopState_Ready.h"

//Attack
#include "CopState_Attack_AxeKick.h"
#include "CopState_Attack_Elbow.h"
#include "CopState_Attack_Punch.h"
#include "CopState_Attack_SideKick.h"

//Damaged
#include "CopState_NormalDamaged_Face.h"
#include "CopState_NormalDamaged_Stomach.h"
#include "CopState_NormalDamaged_Jaw.h"
#include "CopState_Damaged_BlowBack.h"
#include "CopState_Damaged_KnockDown.h"
#include "CopState_Damaged_WallHit.h"
#include "CopState_Damaged_WallOut.h"
#include "CopState_Damaged_Dazed.h"


const  std::string_view CopFSM::NormalDamaged_FileName = "Cop_Get_Hits.png";


const std::vector<CopStateType> CopFSM::AttackGroup =
{
	CopStateType::AxeKick,
	CopStateType::Elbow,
	CopStateType::Punch,
	CopStateType::SideKick
};

CopStateType CopFSM::GetRandomAttack()
{
	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(AttackGroup.size() - 1));
	return AttackGroup[RandValue];
}




CopFSM::CopFSM()
{

}

CopFSM::~CopFSM()
{

}



void CopFSM::Init(FieldEnemyBase* _Enemy)
{
	EnemyFSMBase::Init(_Enemy);
	FSMBase::ResizeStates(CopStateType::COUNT);


	//Movement
	FSMBase::CreateState<CopState_Idle>(CopStateType::Idle);
	FSMBase::CreateState<CopState_Walk>(CopStateType::Walk);
	FSMBase::CreateState<CopState_Ready>(CopStateType::Ready);


	//Attack
	FSMBase::CreateState<CopState_Attack_AxeKick>(CopStateType::AxeKick);
	FSMBase::CreateState<CopState_Attack_Elbow>(CopStateType::Elbow);
	FSMBase::CreateState<CopState_Attack_Punch>(CopStateType::Punch);
	FSMBase::CreateState<CopState_Attack_SideKick>(CopStateType::SideKick);


	//Damaged
	FSMBase::CreateState<CopState_NormalDamaged_Face>(CopStateType::NormalDamaged_Face);
	FSMBase::CreateState<CopState_NormalDamaged_Stomach>(CopStateType::NormalDamaged_Stomach);
	FSMBase::CreateState<CopState_NormalDamaged_Jaw>(CopStateType::NormalDamaged_Jaw);
	FSMBase::CreateState<CopState_Damaged_BlowBack>(CopStateType::Damaged_BlowBack);
	FSMBase::CreateState<CopState_Damaged_KnockDown>(CopStateType::Damaged_KnockDown);
	FSMBase::CreateState<CopState_Damaged_WallHit>(CopStateType::Damaged_WallHit);
	FSMBase::CreateState<CopState_Damaged_WallOut>(CopStateType::Damaged_WallOut);
	FSMBase::CreateState<CopState_Damaged_Dazed>(CopStateType::Damaged_Dazed);




	FSMBase::ChangeState(CopStateType::Idle);
}
