#pragma once

enum class PlayerStateType;

class SkillMgr
{
public:
	static void Init();

	static bool HasSkill(PlayerStateType _CheckSkill);

	static void AcquireSkill(PlayerStateType _Skill);

	SkillMgr(const SkillMgr& _Other) = delete;
	SkillMgr(SkillMgr&& _Other) noexcept = delete;
	SkillMgr& operator=(const SkillMgr& _Other) = delete;
	SkillMgr& operator=(const SkillMgr&& _Other) noexcept = delete;

protected:

private:
	static std::vector<bool>  SkillSlot;

	//È¹µæ ·¹º§, È¹µæ  ½ºÅ³
	static std::vector<std::pair<int, PlayerStateType>> LevelUpSkills;


	SkillMgr();
	virtual ~SkillMgr() = 0;
};

