#pragma once
#include "EnemyState_DamagedBase.h"

class NoiseState_Damaged_GroundHit : public EnemyState_DamagedBase
{
public:
	NoiseState_Damaged_GroundHit();
	~NoiseState_Damaged_GroundHit() override;

	NoiseState_Damaged_GroundHit(const NoiseState_Damaged_GroundHit& _Other) = delete;
	NoiseState_Damaged_GroundHit(NoiseState_Damaged_GroundHit&& _Other) noexcept = delete;
	NoiseState_Damaged_GroundHit& operator=(const NoiseState_Damaged_GroundHit& _Other) = delete;
	NoiseState_Damaged_GroundHit& operator=(const NoiseState_Damaged_GroundHit&& _Other) noexcept = delete;

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
	static const float BlowStartAcc;
	static const float BlowDuration;

	void LoadAnimation();
	void CreateAnimation();
};

