#pragma once
#include "EnemyState_IdleBase.h"

class SchoolBoyState_Idle : public EnemyState_IdleBase
{
public:
	SchoolBoyState_Idle();
	~SchoolBoyState_Idle() override;

	SchoolBoyState_Idle(const SchoolBoyState_Idle& _Other) = delete;
	SchoolBoyState_Idle(SchoolBoyState_Idle&& _Other) noexcept = delete;
	SchoolBoyState_Idle& operator=(const SchoolBoyState_Idle& _Other) = delete;
	SchoolBoyState_Idle& operator=(const SchoolBoyState_Idle&& _Other) noexcept = delete;

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

