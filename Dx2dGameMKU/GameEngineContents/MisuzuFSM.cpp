#include "PrecompileHeader.h"
#include "MisuzuFSM.h"

#include <GameEngineBase/GameEngineRandom.h>

//Movement
#include "MisuzuState_Idle.h"
#include "MisuzuState_Walk.h"
#include "MisuzuState_Defeat.h"
#include "MisuzuState_Taunt.h"

//Attack
#include "MisuzuState_Attack_GetUp.h"
#include "MisuzuState_Attack_Elbow.h"
#include "MisuzuState_Attack_WUPunch.h"
#include "MisuzuState_Attack_Tackle.h"
#include "MisuzuState_Attack_Slap.h"
#include "MisuzuState_Attack_Meteor.h"
#include "MisuzuState_Attack_Roar.h"

//Damaged
#include "MisuzuState_NormalDamaged_Face.h"
#include "MisuzuState_NormalDamaged_Stomach.h"
#include "MisuzuState_NormalDamaged_Jaw.h"
#include "MisuzuState_Damaged_BlowBack.h"
#include "MisuzuState_Damaged_KnockDown.h"
#include "MisuzuState_Damaged_Dizzy.h"
#include "MisuzuState_Damaged_GroundHit.h"


const  std::string_view MisuzuFSM::NormalDamaged_FileName = "Misuzu_GetHit.png";

//근거리
const std::vector<std::vector<MisuzuStateType>> MisuzuFSM::NearAttackGroup =
{
	//1페이즈
	{
		MisuzuStateType::Elbow,
		MisuzuStateType::WUPunch,
		MisuzuStateType::Slap,
		MisuzuStateType::Meteor,
	},

	//2페이즈
	{
		MisuzuStateType::WUPunch,
		MisuzuStateType::Slap,
	},

	//3페이즈
	{
		MisuzuStateType::WUPunch,
		MisuzuStateType::Roar,
		MisuzuStateType::Meteor,
	},
};

//원거리
const std::vector<std::vector<MisuzuStateType>> MisuzuFSM::FarAttackGroup =
{
	//1페이즈
	{
		//임시
		//MisuzuStateType::Meteor
		//MisuzuStateType::Tackle,
	},

	//2페이즈
	{
		MisuzuStateType::Tackle,
	},

	//3페이즈
	{
		MisuzuStateType::Tackle,
		MisuzuStateType::Meteor,
	},
};


size_t MisuzuFSM::GetRandomAttack()
{
	size_t CurPhase = BossFSMBase::GetCurPhase();
	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(NearAttackGroup[CurPhase].size() - 1));
	return static_cast<size_t>(NearAttackGroup[CurPhase][RandValue]);
}

size_t MisuzuFSM::GetRandomFarAttack()
{
	size_t CurPhase = BossFSMBase::GetCurPhase();

	//해당 페이즈에 원거리 공격이 존재하지 않는경우
	if (true == FarAttackGroup[CurPhase].empty())
		return -1;

	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(FarAttackGroup[CurPhase].size() - 1));
	return static_cast<size_t>(FarAttackGroup[CurPhase][RandValue]);
}



MisuzuFSM::MisuzuFSM()
{

}

MisuzuFSM::~MisuzuFSM()
{

}



void MisuzuFSM::Init(FieldEnemyBase* _Enemy)
{
	EnemyFSMBase::Init(_Enemy);
	FSMBase::ResizeStates(MisuzuStateType::COUNT);


	//Movement
	FSMBase::CreateState<MisuzuState_Idle>(MisuzuStateType::Idle);
	FSMBase::CreateState<MisuzuState_Walk>(MisuzuStateType::Walk);
	FSMBase::CreateState<MisuzuState_Defeat>(MisuzuStateType::Defeat);
	FSMBase::CreateState<MisuzuState_Taunt>(MisuzuStateType::Taunt);


	//Attack
	FSMBase::CreateState<MisuzuState_Attack_GetUp>(MisuzuStateType::GetUpAttack);
	FSMBase::CreateState<MisuzuState_Attack_Elbow>(MisuzuStateType::Elbow);
	FSMBase::CreateState<MisuzuState_Attack_WUPunch>(MisuzuStateType::WUPunch);
	FSMBase::CreateState<MisuzuState_Attack_Tackle>(MisuzuStateType::Tackle);
	FSMBase::CreateState<MisuzuState_Attack_Slap>(MisuzuStateType::Slap);
	FSMBase::CreateState<MisuzuState_Attack_Meteor>(MisuzuStateType::Meteor);
	FSMBase::CreateState<MisuzuState_Attack_Roar>(MisuzuStateType::Roar);


	//Damaged
	FSMBase::CreateState<MisuzuState_NormalDamaged_Face>(MisuzuStateType::NormalDamaged_Face);
	FSMBase::CreateState<MisuzuState_NormalDamaged_Stomach>(MisuzuStateType::NormalDamaged_Stomach);
	FSMBase::CreateState<MisuzuState_NormalDamaged_Jaw>(MisuzuStateType::NormalDamaged_Jaw);
	FSMBase::CreateState<MisuzuState_Damaged_BlowBack>(MisuzuStateType::Damaged_BlowBack);
	FSMBase::CreateState<MisuzuState_Damaged_KnockDown>(MisuzuStateType::Damaged_KnockDown);
	FSMBase::CreateState<MisuzuState_Damaged_Dizzy>(MisuzuStateType::Damaged_Dizzy);
	FSMBase::CreateState<MisuzuState_Damaged_GroundHit>(MisuzuStateType::Damaged_GroundHit);




	FSMBase::ChangeState(MisuzuStateType::Idle);
}

