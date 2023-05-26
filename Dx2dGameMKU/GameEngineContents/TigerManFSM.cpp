#include "PrecompileHeader.h"
#include "TigerManFSM.h"

#include <GameEngineBase/GameEngineRandom.h>

//Movement
#include "TigerManState_Idle.h"
#include "TigerManState_Walk.h"
//#include "TigerManState_Ready.h"

//Attack
#include "TigerManState_Attack_Boot.h"
#include "TigerManState_Attack_Chop.h"
#include "TigerManState_Attack_Rolling.h"


//Damaged
#include "TigerManState_NormalDamaged_Face.h"
#include "TigerManState_NormalDamaged_Stomach.h"
#include "TigerManState_NormalDamaged_Jaw.h"
#include "TigerManState_Damaged_BlowBack.h"
#include "TigerManState_Damaged_KnockDown.h"
#include "TigerManState_Damaged_WallHit.h"
#include "TigerManState_Damaged_WallOut.h"
#include "TigerManState_Damaged_Dazed.h"


const  std::string_view TigerManFSM::NormalDamaged_FileName = "TigerMan_GetHit.png";


const std::vector<TigerManStateType> TigerManFSM::AttackGroup =
{
	TigerManStateType::Boot,
	TigerManStateType::Chop,
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
	//FSMBase::CreateState<TigerManState_Ready>(TigerManStateType::Ready);


	//Attack
	FSMBase::CreateState<TigerManState_Attack_Boot>(TigerManStateType::Boot);
	FSMBase::CreateState<TigerManState_Attack_Chop>(TigerManStateType::Chop);
	FSMBase::CreateState<TigerManState_Attack_Rolling>(TigerManStateType::Rolling);


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
