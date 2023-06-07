#pragma once
#include "EnemyState_DamagedBase.h"

class MisuzuState_Damaged_GroundHit : public EnemyState_DamagedBase
{
public:
	MisuzuState_Damaged_GroundHit();
	~MisuzuState_Damaged_GroundHit() override;

	MisuzuState_Damaged_GroundHit(const MisuzuState_Damaged_GroundHit& _Other) = delete;
	MisuzuState_Damaged_GroundHit(MisuzuState_Damaged_GroundHit&& _Other) noexcept = delete;
	MisuzuState_Damaged_GroundHit& operator=(const MisuzuState_Damaged_GroundHit& _Other) = delete;
	MisuzuState_Damaged_GroundHit& operator=(const MisuzuState_Damaged_GroundHit&& _Other) noexcept = delete;

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

