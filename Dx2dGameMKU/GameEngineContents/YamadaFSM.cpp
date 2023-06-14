#include "PrecompileHeader.h"
#include "YamadaFSM.h"

#include <GameEngineBase/GameEngineRandom.h>

//Movement
#include "YamadaState_Idle.h"
#include "YamadaState_Walk.h"
#include "YamadaState_Defeat.h"
#include "YamadaState_Taunt.h"
#include "YamadaState_TeleportDisappear.h"
#include "YamadaState_TeleportAppear.h"

//Attack
#include "YamadaState_Attack_Blast.h"
#include "YamadaState_Attack_ForceField.h"
//#include "YamadaState_Attack_WUPunch.h"
//#include "YamadaState_Attack_Tackle.h"
//#include "YamadaState_Attack_Slap.h"
//#include "YamadaState_Attack_Meteor.h"
//#include "YamadaState_Attack_Roar.h"

//Damaged
#include "YamadaState_NormalDamaged_Face.h"
#include "YamadaState_NormalDamaged_Stomach.h"
#include "YamadaState_NormalDamaged_Jaw.h"
#include "YamadaState_Damaged_BlowBack.h"
#include "YamadaState_Damaged_KnockDown.h"
//#include "YamadaState_Damaged_Dizzy.h"
//#include "YamadaState_Damaged_GroundHit.h"


const  std::string_view YamadaFSM::NormalDamaged_FileName = "Yamada_GetHit.png";

//근거리
const std::vector<std::vector<YamadaStateType>> YamadaFSM::NearAttackGroup =
{
	//1페이즈
	{
		YamadaStateType::Blast,
	},

	//2페이즈
	{
		YamadaStateType::Blast,
	},

	//3페이즈
	{
		YamadaStateType::Blast,
	},
};

//원거리
const std::vector<std::vector<YamadaStateType>> YamadaFSM::FarAttackGroup =
{
	//1페이즈
	{
		YamadaStateType::ForceField,
	},

	//2페이즈
	{
		YamadaStateType::TeleportDisappear,
	},

	//3페이즈
	{
		YamadaStateType::TeleportDisappear,
	},
};


size_t YamadaFSM::GetRandomAttack()
{
	size_t CurPhase = BossFSMBase::GetCurPhase();
	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(NearAttackGroup[CurPhase].size() - 1));
	return static_cast<size_t>(NearAttackGroup[CurPhase][RandValue]);
}

size_t YamadaFSM::GetRandomFarAttack()
{
	size_t CurPhase = BossFSMBase::GetCurPhase();

	//해당 페이즈에 원거리 공격이 존재하지 않는경우
	if (true == FarAttackGroup[CurPhase].empty())
		return -1;

	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(FarAttackGroup[CurPhase].size() - 1));
	return static_cast<size_t>(FarAttackGroup[CurPhase][RandValue]);
}



YamadaFSM::YamadaFSM()
{

}

YamadaFSM::~YamadaFSM()
{

}



void YamadaFSM::Init(FieldEnemyBase* _Enemy)
{
	EnemyFSMBase::Init(_Enemy);
	FSMBase::ResizeStates(YamadaStateType::COUNT);


	//Movement
	FSMBase::CreateState<YamadaState_Idle>(YamadaStateType::Idle);
	FSMBase::CreateState<YamadaState_Walk>(YamadaStateType::Walk);
	FSMBase::CreateState<YamadaState_Defeat>(YamadaStateType::Defeat);
	FSMBase::CreateState<YamadaState_Taunt>(YamadaStateType::Taunt);
	FSMBase::CreateState<YamadaState_TeleportDisappear>(YamadaStateType::TeleportDisappear);
	FSMBase::CreateState<YamadaState_TeleportAppear>(YamadaStateType::TeleportAppear);


	//Attack
	FSMBase::CreateState<YamadaState_Attack_Blast>(YamadaStateType::Blast);
	FSMBase::CreateState<YamadaState_Attack_ForceField>(YamadaStateType::ForceField);
	//FSMBase::CreateState<YamadaState_Attack_WUPunch>(YamadaStateType::WUPunch);
	//FSMBase::CreateState<YamadaState_Attack_Tackle>(YamadaStateType::Tackle);
	//FSMBase::CreateState<YamadaState_Attack_Slap>(YamadaStateType::Slap);
	//FSMBase::CreateState<YamadaState_Attack_Meteor>(YamadaStateType::Meteor);
	//FSMBase::CreateState<YamadaState_Attack_Roar>(YamadaStateType::Roar);


	//Damaged
	FSMBase::CreateState<YamadaState_NormalDamaged_Face>(YamadaStateType::NormalDamaged_Face);
	FSMBase::CreateState<YamadaState_NormalDamaged_Stomach>(YamadaStateType::NormalDamaged_Stomach);
	FSMBase::CreateState<YamadaState_NormalDamaged_Jaw>(YamadaStateType::NormalDamaged_Jaw);
	FSMBase::CreateState<YamadaState_Damaged_BlowBack>(YamadaStateType::Damaged_BlowBack);
	FSMBase::CreateState<YamadaState_Damaged_KnockDown>(YamadaStateType::Damaged_KnockDown);
	//FSMBase::CreateState<YamadaState_Damaged_Dizzy>(YamadaStateType::Damaged_Dizzy);
	//FSMBase::CreateState<YamadaState_Damaged_GroundHit>(YamadaStateType::Damaged_GroundHit);




	FSMBase::ChangeState(YamadaStateType::Idle);
}


