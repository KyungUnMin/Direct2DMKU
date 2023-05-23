#pragma once
#include "EnemyStateBase.h"

class HooliganState_Ready : public EnemyStateBase
{
public:
	HooliganState_Ready();
	~HooliganState_Ready() override;

	HooliganState_Ready(const HooliganState_Ready& _Other) = delete;
	HooliganState_Ready(HooliganState_Ready&& _Other) noexcept = delete;
	HooliganState_Ready& operator=(const HooliganState_Ready& _Other) = delete;
	HooliganState_Ready& operator=(const HooliganState_Ready&& _Other) noexcept = delete;

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

