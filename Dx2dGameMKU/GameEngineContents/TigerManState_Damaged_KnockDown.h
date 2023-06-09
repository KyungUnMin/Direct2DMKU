#pragma once
#include "EnemyState_DamagedBase.h"

class TigerManState_Damaged_KnockDown : public EnemyState_DamagedBase
{
public:
	static const std::string_view AniFileName;


	TigerManState_Damaged_KnockDown();
	~TigerManState_Damaged_KnockDown() override;

	TigerManState_Damaged_KnockDown(const TigerManState_Damaged_KnockDown& _Other) = delete;
	TigerManState_Damaged_KnockDown(TigerManState_Damaged_KnockDown&& _Other) noexcept = delete;
	TigerManState_Damaged_KnockDown& operator=(const TigerManState_Damaged_KnockDown& _Other) = delete;
	TigerManState_Damaged_KnockDown& operator=(const TigerManState_Damaged_KnockDown&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;
	static const float LiveDuration;

	const float StartAcc = 2000.f;

	void LoadAnimation();
	void CreateAnimation();
};

