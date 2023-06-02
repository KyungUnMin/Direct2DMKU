#pragma once
#include "EnemyStateBase.h"

class SchoolBoyState_Ready : public EnemyStateBase
{
public:
	SchoolBoyState_Ready();
	~SchoolBoyState_Ready() override;

	SchoolBoyState_Ready(const SchoolBoyState_Ready& _Other) = delete;
	SchoolBoyState_Ready(SchoolBoyState_Ready&& _Other) noexcept = delete;
	SchoolBoyState_Ready& operator=(const SchoolBoyState_Ready& _Other) = delete;
	SchoolBoyState_Ready& operator=(const SchoolBoyState_Ready&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

private:
	static const std::string_view WaitAniName;
	static const std::string_view GetUpAniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	enum class State
	{
		Wait,
		GetUp
	};

	State CurState = State::Wait;

	void LoadAnimation();
	void CreateAnimation();

	void Update_Wait();
	void Update_GetUp();
};

