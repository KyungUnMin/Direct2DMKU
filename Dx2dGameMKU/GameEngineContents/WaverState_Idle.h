#pragma once
#include "EnemyStateBase.h"

class WaverState_Idle : public EnemyStateBase
{
public:
	WaverState_Idle();
	~WaverState_Idle() override;

	WaverState_Idle(const WaverState_Idle& _Other) = delete;
	WaverState_Idle(WaverState_Idle&& _Other) noexcept = delete;
	WaverState_Idle& operator=(const WaverState_Idle& _Other) = delete;
	WaverState_Idle& operator=(const WaverState_Idle&& _Other) noexcept = delete;

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

