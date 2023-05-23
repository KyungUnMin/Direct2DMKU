#pragma once
#include "EnemyStateBase.h"

class CopState_Ready : public EnemyStateBase
{
public:
	CopState_Ready();
	~CopState_Ready() override;

	CopState_Ready(const CopState_Ready& _Other) = delete;
	CopState_Ready(CopState_Ready&& _Other) noexcept = delete;
	CopState_Ready& operator=(const CopState_Ready& _Other) = delete;
	CopState_Ready& operator=(const CopState_Ready&& _Other) noexcept = delete;

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

