#include "PrecompileHeader.h"
#include "SkillMgr.h"

#include "DataMgr.h"

#include "PlayerFSM.h"

std::vector<bool>  SkillMgr::SkillSlot;



void SkillMgr::Init()
{
	SkillSlot.resize(static_cast<size_t>(PlayerStateType::COUNT), true);

	SkillSlot[static_cast<size_t>(PlayerStateType::QuickAttack_BackKick)] = false;
	SkillSlot[static_cast<size_t>(PlayerStateType::QuickAttack_CrescentKick)] = false;
	SkillSlot[static_cast<size_t>(PlayerStateType::SpecialAttack_DonkeyKick)] = false;

	SkillSlot[static_cast<size_t>(PlayerStateType::SpecialAttack_DAP)] = false;
	SkillSlot[static_cast<size_t>(PlayerStateType::DashAttack_DropKick)] = false;
	SkillSlot[static_cast<size_t>(PlayerStateType::UniqueAttack_DragonFeet)] = false;
	SkillSlot[static_cast<size_t>(PlayerStateType::UniqueAttack_HyrricaneKick)] = false;
}

bool SkillMgr::HasSkill(PlayerStateType _CheckSkill)
{
	return SkillSlot[static_cast<size_t>(_CheckSkill)];
}

void SkillMgr::AcquireSkill(PlayerStateType _Skill)
{
	size_t Index = static_cast<size_t>(_Skill);
	if (true == SkillSlot[Index])
	{
		MsgAssert("해당 스킬은 이미 얻은 스킬입니다");
		return;
	}

	SkillSlot[Index] = true;
}



SkillMgr::SkillMgr()
{

}

SkillMgr::~SkillMgr()
{

}
