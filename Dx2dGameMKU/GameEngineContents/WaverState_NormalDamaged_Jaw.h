#pragma once
#include "EnemyState_DamagedBase.h"

class WaverState_NormalDamaged_Jaw : public EnemyState_DamagedBase
{
public:
	WaverState_NormalDamaged_Jaw();
	~WaverState_NormalDamaged_Jaw() override;

	WaverState_NormalDamaged_Jaw(const WaverState_NormalDamaged_Jaw& _Other) = delete;
	WaverState_NormalDamaged_Jaw(WaverState_NormalDamaged_Jaw&& _Other) noexcept = delete;
	WaverState_NormalDamaged_Jaw& operator=(const WaverState_NormalDamaged_Jaw& _Other) = delete;
	WaverState_NormalDamaged_Jaw& operator=(const WaverState_NormalDamaged_Jaw&& _Other) noexcept = delete;

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

