#pragma once
#include "EnemyState_WalkBase.h"

class WaverState_Walk : public EnemyState_WalkBase
{
public:
	WaverState_Walk();
	~WaverState_Walk() override;

	WaverState_Walk(const WaverState_Walk& _Other) = delete;
	WaverState_Walk(WaverState_Walk&& _Other) noexcept = delete;
	WaverState_Walk& operator=(const WaverState_Walk& _Other) = delete;
	WaverState_Walk& operator=(const WaverState_Walk&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	void LoadAnimation();
	void CreateAnimation();
};

