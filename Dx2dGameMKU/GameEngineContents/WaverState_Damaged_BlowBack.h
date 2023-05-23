#pragma once
#include "EnemyState_DamagedBase.h"

class WaverState_Damaged_BlowBack : public EnemyState_DamagedBase
{
public:
	WaverState_Damaged_BlowBack();
	~WaverState_Damaged_BlowBack() override;

	WaverState_Damaged_BlowBack(const WaverState_Damaged_BlowBack& _Other) = delete;
	WaverState_Damaged_BlowBack(WaverState_Damaged_BlowBack&& _Other) noexcept = delete;
	WaverState_Damaged_BlowBack& operator=(const WaverState_Damaged_BlowBack& _Other) = delete;
	WaverState_Damaged_BlowBack& operator=(const WaverState_Damaged_BlowBack&& _Other) noexcept = delete;

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

	const float StartAcc = 2500.f;
	const float Duration = 0.5f;

	void LoadAnimation();
	void CreateAnimation();
	
};

