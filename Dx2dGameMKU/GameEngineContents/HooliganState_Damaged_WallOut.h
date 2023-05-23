#pragma once
#include "EnemyState_DamagedBase.h"

class HooliganState_Damaged_WallOut : public EnemyState_DamagedBase
{
public:
	HooliganState_Damaged_WallOut();
	~HooliganState_Damaged_WallOut() override;

	HooliganState_Damaged_WallOut(const HooliganState_Damaged_WallOut& _Other) = delete;
	HooliganState_Damaged_WallOut(HooliganState_Damaged_WallOut&& _Other) noexcept = delete;
	HooliganState_Damaged_WallOut& operator=(const HooliganState_Damaged_WallOut& _Other) = delete;
	HooliganState_Damaged_WallOut& operator=(const HooliganState_Damaged_WallOut&& _Other) noexcept = delete;

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

