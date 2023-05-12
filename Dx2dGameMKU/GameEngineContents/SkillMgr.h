#pragma once


class SkillMgr
{
public:
	SkillMgr(const SkillMgr& _Other) = delete;
	SkillMgr(SkillMgr&& _Other) noexcept = delete;
	SkillMgr& operator=(const SkillMgr& _Other) = delete;
	SkillMgr& operator=(const SkillMgr&& _Other) noexcept = delete;

protected:


private:
	static UINT SkillSlot;

	//아직 어떻게 할 지 모르겠다 나중에 필요해질때 다시 보자
	enum
	{
		QuickAttack_Chop = (1 << 0),
		QuickAttack_SnapKick = (1 << 1),
		QuickAttack_HookKick = (1 << 2),
		QuickAttack_BackKick = (1 << 3),


	};


	SkillMgr();
	virtual ~SkillMgr() = 0;
};

