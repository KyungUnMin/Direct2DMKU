#pragma once
#include "EnemyState_DamagedBase.h"

class YamadaState_Damaged_KnockDown : public EnemyState_DamagedBase
{
public:
	static const std::string_view AniFileName;


	YamadaState_Damaged_KnockDown();
	~YamadaState_Damaged_KnockDown() override;

	YamadaState_Damaged_KnockDown(const YamadaState_Damaged_KnockDown& _Other) = delete;
	YamadaState_Damaged_KnockDown(YamadaState_Damaged_KnockDown&& _Other) noexcept = delete;
	YamadaState_Damaged_KnockDown& operator=(const YamadaState_Damaged_KnockDown& _Other) = delete;
	YamadaState_Damaged_KnockDown& operator=(const YamadaState_Damaged_KnockDown&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::pair<int, int> AniCutFrame;
	static const std::pair<size_t, size_t> AniFrameIndex;
	static const float AniInterTime;

	const float StartAcc = 2000.f;

	void LoadAnimation();
	void CreateAnimation();
};

