#include "PrecompileHeader.h"
#include "NoiseFSM.h"

#include <GameEngineBase/GameEngineRandom.h>

//Movement
#include "NoiseState_Idle.h"
#include "NoiseState_Slide.h"
#include "NoiseState_Defeat.h"
#include "NoiseState_Taunt.h"

//Attack
#include "NoiseState_Attack_AxeGrind.h"
#include "NoiseState_Attack_GuitarSlash.h"
#include "NoiseState_Attack_GuitarSlashDash.h"
#include "NoiseState_Attack_AxeDash.h"
//#include "NoiseState_Attack_WUPunch.h"
//#include "NoiseState_Attack_Tackle.h"
//#include "NoiseState_Attack_Slap.h"
//#include "NoiseState_Attack_Meteor.h"
//#include "NoiseState_Attack_Roar.h"

//Damaged
#include "NoiseState_NormalDamaged_Face.h"
#include "NoiseState_NormalDamaged_Stomach.h"
#include "NoiseState_NormalDamaged_Jaw.h"
#include "NoiseState_Damaged_BlowBack.h"
#include "NoiseState_Damaged_KnockDown.h"
#include "NoiseState_Damaged_Dizzy.h"
#include "NoiseState_Damaged_GroundHit.h"


const  std::string_view NoiseFSM::NormalDamaged_FileName = "Noise_GetHit.png";

//근거리
const std::vector<std::vector<NoiseStateType>> NoiseFSM::NearAttackGroup =
{
	//1페이즈
	{
		//NoiseStateType::Elbow,
		//NoiseStateType::WUPunch,
		//NoiseStateType::Slap,
	},

	//2페이즈
	{
		//NoiseStateType::WUPunch,
		//NoiseStateType::Slap,
	},

	//3페이즈
	{
		//NoiseStateType::WUPunch,
		//NoiseStateType::Roar,
	},
};

//원거리
const std::vector<std::vector<NoiseStateType>> NoiseFSM::FarAttackGroup =
{
	//1페이즈
	{
		NoiseStateType::GuitarSlashDash
		//NoiseStateType::Tackle,
	},

	//2페이즈
	{
		//NoiseStateType::Tackle,

	},

	//3페이즈
	{
		//NoiseStateType::Tackle,
		//NoiseStateType::Meteor,
	},
};


size_t NoiseFSM::GetRandomAttack()
{
	size_t CurPhase = BossFSMBase::GetCurPhase();
	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(NearAttackGroup[CurPhase].size() - 1));
	return static_cast<size_t>(NearAttackGroup[CurPhase][RandValue]);
}

size_t NoiseFSM::GetRandomFarAttack()
{
	size_t CurPhase = BossFSMBase::GetCurPhase();

	//해당 페이즈에 원거리 공격이 존재하지 않는경우
	if (true == FarAttackGroup[CurPhase].empty())
		return -1;

	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(FarAttackGroup[CurPhase].size() - 1));
	return static_cast<size_t>(FarAttackGroup[CurPhase][RandValue]);
}



NoiseFSM::NoiseFSM()
{

}

NoiseFSM::~NoiseFSM()
{

}



void NoiseFSM::Init(FieldEnemyBase* _Enemy)
{
	EnemyFSMBase::Init(_Enemy);
	FSMBase::ResizeStates(NoiseStateType::COUNT);


	//Movement
	FSMBase::CreateState<NoiseState_Idle>(NoiseStateType::Idle);
	FSMBase::CreateState<NoiseState_Slide>(NoiseStateType::Slide);
	//FSMBase::CreateState<NoiseState_Defeat>(NoiseStateType::Defeat);
	//FSMBase::CreateState<NoiseState_Taunt>(NoiseStateType::Taunt);


	//Attack
	FSMBase::CreateState<NoiseState_Attack_AxeGrind>(NoiseStateType::AxeGrind);
	FSMBase::CreateState<NoiseState_Attack_GuitarSlash>(NoiseStateType::GuitarSlash);
	FSMBase::CreateState<NoiseState_Attack_GuitarSlashDash>(NoiseStateType::GuitarSlashDash);
	FSMBase::CreateState<NoiseState_Attack_AxeDash>(NoiseStateType::AxeDash);
	//FSMBase::CreateState<NoiseState_Attack_Slap>(NoiseStateType::Slap);
	//FSMBase::CreateState<NoiseState_Attack_Meteor>(NoiseStateType::Meteor);
	//FSMBase::CreateState<NoiseState_Attack_Roar>(NoiseStateType::Roar);


	//Damaged
	FSMBase::CreateState<NoiseState_NormalDamaged_Face>(NoiseStateType::NormalDamaged_Face);
	FSMBase::CreateState<NoiseState_NormalDamaged_Stomach>(NoiseStateType::NormalDamaged_Stomach);
	FSMBase::CreateState<NoiseState_NormalDamaged_Jaw>(NoiseStateType::NormalDamaged_Jaw);
	FSMBase::CreateState<NoiseState_Damaged_BlowBack>(NoiseStateType::Damaged_BlowBack);
	FSMBase::CreateState<NoiseState_Damaged_KnockDown>(NoiseStateType::Damaged_KnockDown);
	//FSMBase::CreateState<NoiseState_Damaged_Dizzy>(NoiseStateType::Damaged_Dizzy);
	//FSMBase::CreateState<NoiseState_Damaged_GroundHit>(NoiseStateType::Damaged_GroundHit);




	FSMBase::ChangeState(NoiseStateType::Idle);
}

