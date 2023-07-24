#include "PrecompileHeader.h"
#include "Shop_GymLevel.h"

#include "RCGEnums.h"

#include "SkillPreviewer.h"
#include "SkillMgr.h"
#include "PlayerFSM.h"
#include "TutorialUI.h"
#include "FieldLevelBase.h"

const std::vector<PlayerStateType> Shop_GymLevel::UnlockSkills =
{
	PlayerStateType::SpecialAttack_DAP,
	PlayerStateType::DashAttack_DropKick,
	PlayerStateType::UniqueAttack_DragonFeet,
	PlayerStateType::UniqueAttack_HyrricaneKick,
};

Shop_GymLevel::Shop_GymLevel()
{

}

Shop_GymLevel::~Shop_GymLevel()
{

}



void Shop_GymLevel::Start()
{
	ShopLevelBase::Start();
	ShopLevelBase::SetBgmName("ShopBGM_Gym.mp3");
	CreateBackImage("GymBG.png");

	GameEngineTransform* Trans = nullptr;
	Trans = CreateActor<SkillPreviewer>(UpdateOrder::UI)->GetTransform();
	Trans->SetLocalPosition({ -184.f, -240.f });
}

void Shop_GymLevel::LevelChangeStart()
{
	ShopLevelBase::LevelChangeStart();

	for (PlayerStateType Skill : UnlockSkills)
	{
		if (false == SkillMgr::HasSkill(Skill))
			continue;

		int BitIndex = static_cast<int>(Skill);
		PrevSkillBit |= (1 << BitIndex);
	}
}


void Shop_GymLevel::LevelChangeEnd()
{
	ShopLevelBase::LevelChangeEnd();

	for (PlayerStateType Skill : UnlockSkills)
	{
		if (false == SkillMgr::HasSkill(Skill))
			continue;

		int BitIndex = static_cast<int>(Skill);
		NowSkillBit |= (1 << BitIndex);
	}

	if (PrevSkillBit != NowSkillBit)
	{
		FieldLevelBase::GetPtr()->TimeEvent.AddEvent(1.f, [](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)
		{
			TutorialUI::BindTurorial("새로운 스킬 획득!", "ESC를 눌러 새 스킬을 확인하자");
		});
	}

	PrevSkillBit = NowSkillBit;
}