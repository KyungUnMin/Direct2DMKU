#pragma once
#include "EnemyState_DamagedBase.h"

class WaverState_Damaged_WallOut : public EnemyState_DamagedBase
{
public:
	WaverState_Damaged_WallOut();
	~WaverState_Damaged_WallOut() override;

	WaverState_Damaged_WallOut(const WaverState_Damaged_WallOut& _Other) = delete;
	WaverState_Damaged_WallOut(WaverState_Damaged_WallOut&& _Other) noexcept = delete;
	WaverState_Damaged_WallOut& operator=(const WaverState_Damaged_WallOut& _Other) = delete;
	WaverState_Damaged_WallOut& operator=(const WaverState_Damaged_WallOut&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	const float Duration = 0.3f;
	const float StartReflectSize = 700.f;

	void LoadAnimation();
	void CreateAnimation();
	void SetReflectDirection();
};

