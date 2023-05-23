#pragma once
#include "EnemyState_DamagedBase.h"

class TigerManState_Damaged_WallHit : public EnemyState_DamagedBase
{
public:
	TigerManState_Damaged_WallHit();
	~TigerManState_Damaged_WallHit() override;

	TigerManState_Damaged_WallHit(const TigerManState_Damaged_WallHit& _Other) = delete;
	TigerManState_Damaged_WallHit(TigerManState_Damaged_WallHit&& _Other) noexcept = delete;
	TigerManState_Damaged_WallHit& operator=(const TigerManState_Damaged_WallHit& _Other) = delete;
	TigerManState_Damaged_WallHit& operator=(const TigerManState_Damaged_WallHit&& _Other) noexcept = delete;

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

