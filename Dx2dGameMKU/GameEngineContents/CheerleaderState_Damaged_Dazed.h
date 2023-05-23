#pragma once
#include "EnemyState_DamagedBase.h"

class CheerleaderState_Damaged_Dazed : public EnemyState_DamagedBase
{
public:
	CheerleaderState_Damaged_Dazed();
	~CheerleaderState_Damaged_Dazed() override;

	CheerleaderState_Damaged_Dazed(const CheerleaderState_Damaged_Dazed& _Other) = delete;
	CheerleaderState_Damaged_Dazed(CheerleaderState_Damaged_Dazed&& _Other) noexcept = delete;
	CheerleaderState_Damaged_Dazed& operator=(const CheerleaderState_Damaged_Dazed& _Other) = delete;
	CheerleaderState_Damaged_Dazed& operator=(const CheerleaderState_Damaged_Dazed&& _Other) noexcept = delete;

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

	const float Duration = 5.0f;

	void LoadAnimation();
	void CreateAnimation();
};

