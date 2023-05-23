#pragma once
#include "EnemyStateBase.h"

class TigerManState_Ready : public EnemyStateBase
{
public:
	TigerManState_Ready();
	~TigerManState_Ready() override;

	TigerManState_Ready(const TigerManState_Ready& _Other) = delete;
	TigerManState_Ready(TigerManState_Ready&& _Other) noexcept = delete;
	TigerManState_Ready& operator=(const TigerManState_Ready& _Other) = delete;
	TigerManState_Ready& operator=(const TigerManState_Ready&& _Other) noexcept = delete;

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

