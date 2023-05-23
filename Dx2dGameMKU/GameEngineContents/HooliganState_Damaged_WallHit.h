#pragma once
#include "EnemyState_DamagedBase.h"

class HooliganState_Damaged_WallHit : public EnemyState_DamagedBase
{
public:
	HooliganState_Damaged_WallHit();
	~HooliganState_Damaged_WallHit() override;

	HooliganState_Damaged_WallHit(const HooliganState_Damaged_WallHit& _Other) = delete;
	HooliganState_Damaged_WallHit(HooliganState_Damaged_WallHit&& _Other) noexcept = delete;
	HooliganState_Damaged_WallHit& operator=(const HooliganState_Damaged_WallHit& _Other) = delete;
	HooliganState_Damaged_WallHit& operator=(const HooliganState_Damaged_WallHit&& _Other) noexcept = delete;

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

