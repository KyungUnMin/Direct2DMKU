#pragma once
#include "EnemyState_DamagedBase.h"

class WaverState_Damaged_WallHit : public EnemyState_DamagedBase
{
public:
	WaverState_Damaged_WallHit();
	~WaverState_Damaged_WallHit() override;

	WaverState_Damaged_WallHit(const WaverState_Damaged_WallHit& _Other) = delete;
	WaverState_Damaged_WallHit(WaverState_Damaged_WallHit&& _Other) noexcept = delete;
	WaverState_Damaged_WallHit& operator=(const WaverState_Damaged_WallHit& _Other) = delete;
	WaverState_Damaged_WallHit& operator=(const WaverState_Damaged_WallHit&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const std::pair<size_t, size_t> AniFrameIndex;
	static const float AniInterTime;

	const float Duration = 0.15f;

	void LoadAnimation();
	void CreateAnimation();
};

