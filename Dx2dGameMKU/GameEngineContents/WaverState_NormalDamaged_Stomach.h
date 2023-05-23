#pragma once
#include "EnemyState_DamagedBase.h"

class WaverState_NormalDamaged_Stomach : public EnemyState_DamagedBase
{
public:
	WaverState_NormalDamaged_Stomach();
	~WaverState_NormalDamaged_Stomach() override;

	WaverState_NormalDamaged_Stomach(const WaverState_NormalDamaged_Stomach& _Other) = delete;
	WaverState_NormalDamaged_Stomach(WaverState_NormalDamaged_Stomach&& _Other) noexcept = delete;
	WaverState_NormalDamaged_Stomach& operator=(const WaverState_NormalDamaged_Stomach& _Other) = delete;
	WaverState_NormalDamaged_Stomach& operator=(const WaverState_NormalDamaged_Stomach&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::pair<int, int> AniCutFrame;
	static const std::pair<size_t, size_t> AniFrameIndex;
	static const float AniInterTime;

	void LoadAnimation();
	void CreateAnimation();
};

