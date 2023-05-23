#pragma once
#include "EnemyState_DamagedBase.h"

class TigerManState_Damaged_WallOut : public EnemyState_DamagedBase
{
public:
	TigerManState_Damaged_WallOut();
	~TigerManState_Damaged_WallOut() override;

	TigerManState_Damaged_WallOut(const TigerManState_Damaged_WallOut& _Other) = delete;
	TigerManState_Damaged_WallOut(TigerManState_Damaged_WallOut&& _Other) noexcept = delete;
	TigerManState_Damaged_WallOut& operator=(const TigerManState_Damaged_WallOut& _Other) = delete;
	TigerManState_Damaged_WallOut& operator=(const TigerManState_Damaged_WallOut&& _Other) noexcept = delete;

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

