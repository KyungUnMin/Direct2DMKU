#include "PrecompileHeader.h"
#include "TigerManFSM.h"

#include <GameEngineBase/GameEngineRandom.h>

//Movement
#include "TigerManState_Idle.h"
#include "TigerManState_Walk.h"
#include "TigerManState_Ready.h"

//Attack
#include "TigerManState_Attack_AxeKick.h"
#include "TigerManState_Attack_Elbow.h"
#include "TigerManState_Attack_Punch.h"
#include "TigerManState_Attack_SideKick.h"

//Damaged
#include "TigerManState_NormalDamaged_Face.h"
#include "TigerManState_NormalDamaged_Stomach.h"
#include "TigerManState_NormalDamaged_Jaw.h"
#include "TigerManState_Damaged_BlowBack.h"
#include "TigerManState_Damaged_KnockDown.h"
#include "TigerManState_Damaged_WallHit.h"
#include "TigerManState_Damaged_WallOut.h"
#include "TigerManState_Damaged_Dazed.h"


const  std::string_view TigerManFSM::NormalDamaged_FileName = "TigerMan_Get_Hits.png";


const std::vector<TigerManStateType> TigerManFSM::AttackGroup =
{
	TigerManStateType::AxeKick,
	TigerManStateType::Elbow,
	TigerManStateType::Punch,
	TigerManStateType::SideKick
};

size_t TigerManFSM::GetRandomAttack()
{
	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(AttackGroup.size() - 1));
	return static_cast<size_t>(AttackGroup[RandValue]);
}





TigerManFSM::TigerManFSM()
{

}

TigerManFSM::~TigerManFSM()
{

}



void TigerManFSM::Init(FieldEnemyBase* _Enemy)
{
	EnemyFSMBase::Init(_Enemy);
	FSMBase::ResizeStates(TigerManStateType::COUNT);


	//Movement
	FSMBase::CreateState<TigerManState_Idle>(TigerManStateType::Idle);
	FSMBase::CreateState<TigerManState_Walk>(TigerManStateType::Walk);
	FSMBase::CreateState<TigerManState_Ready>(TigerManStateType::Ready);


	//Attack
	FSMBase::CreateState<TigerManState_Attack_AxeKick>(TigerManStateType::AxeKick);
	FSMBase::CreateState<TigerManState_Attack_Elbow>(TigerManStateType::Elbow);
	FSMBase::CreateState<TigerManState_Attack_Punch>(TigerManStateType::Punch);
	FSMBase::CreateState<TigerManState_Attack_SideKick>(TigerManStateType::SideKick);


	//Damaged
	FSMBase::CreateState<TigerManState_NormalDamaged_Face>(TigerManStateType::NormalDamaged_Face);
	FSMBase::CreateState<TigerManState_NormalDamaged_Stomach>(TigerManStateType::NormalDamaged_Stomach);
	FSMBase::CreateState<TigerManState_NormalDamaged_Jaw>(TigerManStateType::NormalDamaged_Jaw);
	FSMBase::CreateState<TigerManState_Damaged_BlowBack>(TigerManStateType::Damaged_BlowBack);
	FSMBase::CreateState<TigerManState_Damaged_KnockDown>(TigerManStateType::Damaged_KnockDown);
	FSMBase::CreateState<TigerManState_Damaged_WallHit>(TigerManStateType::Damaged_WallHit);
	FSMBase::CreateState<TigerManState_Damaged_WallOut>(TigerManStateType::Damaged_WallOut);
	FSMBase::CreateState<TigerManState_Damaged_Dazed>(TigerManStateType::Damaged_Dazed);




	FSMBase::ChangeState(TigerManStateType::Idle);
}
