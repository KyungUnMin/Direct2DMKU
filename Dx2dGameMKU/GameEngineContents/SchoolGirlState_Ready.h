#pragma once
#include "EnemyStateBase.h"

class SchoolGirlState_Ready : public EnemyStateBase
{
public:
	SchoolGirlState_Ready();
	~SchoolGirlState_Ready() override;

	SchoolGirlState_Ready(const SchoolGirlState_Ready& _Other) = delete;
	SchoolGirlState_Ready(SchoolGirlState_Ready&& _Other) noexcept = delete;
	SchoolGirlState_Ready& operator=(const SchoolGirlState_Ready& _Other) = delete;
	SchoolGirlState_Ready& operator=(const SchoolGirlState_Ready&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

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

