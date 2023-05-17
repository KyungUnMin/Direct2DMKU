#pragma once
#include "EnemyStateBase.h"

class SchoolBoyState_Attack_SideKick : public EnemyStateBase
{
public:
	SchoolBoyState_Attack_SideKick();
	~SchoolBoyState_Attack_SideKick() override;

	SchoolBoyState_Attack_SideKick(const SchoolBoyState_Attack_SideKick& _Other) = delete;
	SchoolBoyState_Attack_SideKick(SchoolBoyState_Attack_SideKick&& _Other) noexcept = delete;
	SchoolBoyState_Attack_SideKick& operator=(const SchoolBoyState_Attack_SideKick& _Other) = delete;
	SchoolBoyState_Attack_SideKick& operator=(const SchoolBoyState_Attack_SideKick&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	void LoadAnimation();
	void CreateAnimation();
};

