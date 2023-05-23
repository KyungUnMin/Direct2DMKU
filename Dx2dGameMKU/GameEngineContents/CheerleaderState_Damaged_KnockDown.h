#pragma once
#include "EnemyState_DamagedBase.h"

class CheerleaderState_Damaged_KnockDown : public EnemyState_DamagedBase
{
public:
	static const std::string_view AniFileName;


	CheerleaderState_Damaged_KnockDown();
	~CheerleaderState_Damaged_KnockDown() override;

	CheerleaderState_Damaged_KnockDown(const CheerleaderState_Damaged_KnockDown& _Other) = delete;
	CheerleaderState_Damaged_KnockDown(CheerleaderState_Damaged_KnockDown&& _Other) noexcept = delete;
	CheerleaderState_Damaged_KnockDown& operator=(const CheerleaderState_Damaged_KnockDown& _Other) = delete;
	CheerleaderState_Damaged_KnockDown& operator=(const CheerleaderState_Damaged_KnockDown&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::pair<int, int> AniCutFrame;
	static const std::pair<size_t, size_t> AniFrameIndex;
	static const float AniInterTime;
	static const float LiveDuration;

	const float StartAcc = 2000.f;

	void LoadAnimation();
	void CreateAnimation();
};

