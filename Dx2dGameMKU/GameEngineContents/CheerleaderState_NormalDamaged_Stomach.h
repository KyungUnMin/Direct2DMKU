#pragma once
#include "EnemyState_DamagedBase.h"

class CheerleaderState_NormalDamaged_Stomach : public EnemyState_DamagedBase
{
public:
	CheerleaderState_NormalDamaged_Stomach();
	~CheerleaderState_NormalDamaged_Stomach() override;

	CheerleaderState_NormalDamaged_Stomach(const CheerleaderState_NormalDamaged_Stomach& _Other) = delete;
	CheerleaderState_NormalDamaged_Stomach(CheerleaderState_NormalDamaged_Stomach&& _Other) noexcept = delete;
	CheerleaderState_NormalDamaged_Stomach& operator=(const CheerleaderState_NormalDamaged_Stomach& _Other) = delete;
	CheerleaderState_NormalDamaged_Stomach& operator=(const CheerleaderState_NormalDamaged_Stomach&& _Other) noexcept = delete;

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

