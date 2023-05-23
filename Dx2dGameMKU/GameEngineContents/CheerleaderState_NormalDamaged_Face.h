#pragma once
#include "EnemyState_DamagedBase.h"

class CheerleaderState_NormalDamaged_Face : public EnemyState_DamagedBase
{
public:
	CheerleaderState_NormalDamaged_Face();
	~CheerleaderState_NormalDamaged_Face() override;

	CheerleaderState_NormalDamaged_Face(const CheerleaderState_NormalDamaged_Face& _Other) = delete;
	CheerleaderState_NormalDamaged_Face(CheerleaderState_NormalDamaged_Face&& _Other) noexcept = delete;
	CheerleaderState_NormalDamaged_Face& operator=(const CheerleaderState_NormalDamaged_Face& _Other) = delete;
	CheerleaderState_NormalDamaged_Face& operator=(const CheerleaderState_NormalDamaged_Face&& _Other) noexcept = delete;

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

