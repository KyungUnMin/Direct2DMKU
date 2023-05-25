#include "PrecompileHeader.h"
#include "CheerleaderFSM.h"

#include <GameEngineBase/GameEngineRandom.h>

//Movement
#include "CheerleaderState_Idle.h"
#include "CheerleaderState_Walk.h"
//#include "CheerleaderState_Ready.h"
#include "CheerleaderState_CartWheel.h"

//Attack
#include "CheerleaderState_Attack_BackFlip.h"
#include "CheerleaderState_Attack_DoublePom.h"
#include "CheerleaderState_Attack_Jab.h"
#include "CheerleaderState_Attack_SpinPom.h"


//Damaged
#include "CheerleaderState_NormalDamaged_Face.h"
#include "CheerleaderState_NormalDamaged_Stomach.h"
#include "CheerleaderState_NormalDamaged_Jaw.h"
#include "CheerleaderState_Damaged_BlowBack.h"
#include "CheerleaderState_Damaged_KnockDown.h"
#include "CheerleaderState_Damaged_WallHit.h"
#include "CheerleaderState_Damaged_WallOut.h"
#include "CheerleaderState_Damaged_Dazed.h"


const  std::string_view CheerleaderFSM::NormalDamaged_FileName = "Cheerleader_GetHit.png";


const std::vector<CheerleaderStateType> CheerleaderFSM::AttackGroup =
{
	CheerleaderStateType::CartWheel,
	CheerleaderStateType::BackFlip,
	CheerleaderStateType::DoublePom,
	CheerleaderStateType::Jab,
	CheerleaderStateType::SpinPom
};

size_t CheerleaderFSM::GetRandomAttack()
{
	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(AttackGroup.size() - 1));
	return static_cast<size_t>(AttackGroup[RandValue]);
}





CheerleaderFSM::CheerleaderFSM()
{

}

CheerleaderFSM::~CheerleaderFSM()
{

}



void CheerleaderFSM::Init(FieldEnemyBase* _Enemy)
{
	EnemyFSMBase::Init(_Enemy);
	FSMBase::ResizeStates(CheerleaderStateType::COUNT);


	//Movement
	FSMBase::CreateState<CheerleaderState_Idle>(CheerleaderStateType::Idle);
	FSMBase::CreateState<CheerleaderState_Walk>(CheerleaderStateType::Walk);
	//FSMBase::CreateState<CheerleaderState_Ready>(CheerleaderStateType::Ready);
	FSMBase::CreateState<CheerleaderState_CartWheel>(CheerleaderStateType::CartWheel);


	//Attack
	FSMBase::CreateState<CheerleaderState_Attack_BackFlip>(CheerleaderStateType::BackFlip);
	FSMBase::CreateState<CheerleaderState_Attack_DoublePom>(CheerleaderStateType::DoublePom);
	FSMBase::CreateState<CheerleaderState_Attack_Jab>(CheerleaderStateType::Jab);
	FSMBase::CreateState<CheerleaderState_Attack_SpinPom>(CheerleaderStateType::SpinPom);


	//Damaged
	FSMBase::CreateState<CheerleaderState_NormalDamaged_Face>(CheerleaderStateType::NormalDamaged_Face);
	FSMBase::CreateState<CheerleaderState_NormalDamaged_Stomach>(CheerleaderStateType::NormalDamaged_Stomach);
	FSMBase::CreateState<CheerleaderState_NormalDamaged_Jaw>(CheerleaderStateType::NormalDamaged_Jaw);
	FSMBase::CreateState<CheerleaderState_Damaged_BlowBack>(CheerleaderStateType::Damaged_BlowBack);
	FSMBase::CreateState<CheerleaderState_Damaged_KnockDown>(CheerleaderStateType::Damaged_KnockDown);
	FSMBase::CreateState<CheerleaderState_Damaged_WallHit>(CheerleaderStateType::Damaged_WallHit);
	FSMBase::CreateState<CheerleaderState_Damaged_WallOut>(CheerleaderStateType::Damaged_WallOut);
	FSMBase::CreateState<CheerleaderState_Damaged_Dazed>(CheerleaderStateType::Damaged_Dazed);




	FSMBase::ChangeState(CheerleaderStateType::Idle);
}
