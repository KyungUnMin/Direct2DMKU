#pragma once
#include "EnemyState_DamagedBase.h"

class MisuzuState_Damaged_BlowBack : public EnemyState_DamagedBase
{
public:
	MisuzuState_Damaged_BlowBack();
	~MisuzuState_Damaged_BlowBack() override;

	MisuzuState_Damaged_BlowBack(const MisuzuState_Damaged_BlowBack& _Other) = delete;
	MisuzuState_Damaged_BlowBack(MisuzuState_Damaged_BlowBack&& _Other) noexcept = delete;
	MisuzuState_Damaged_BlowBack& operator=(const MisuzuState_Damaged_BlowBack& _Other) = delete;
	MisuzuState_Damaged_BlowBack& operator=(const MisuzuState_Damaged_BlowBack&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const std::pair<size_t, size_t> AniFrameIndex;
	static const float AniInterTime;

	const float StartAcc = 1500.f;
	const float Duration = 0.5f;

	bool IsWallHit = false;
	float4 WallOutDir = float4::Zero;

	void LoadAnimation();
	void CreateAnimation();
};

