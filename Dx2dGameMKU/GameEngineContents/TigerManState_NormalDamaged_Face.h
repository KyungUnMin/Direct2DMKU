#pragma once
#include "EnemyState_DamagedBase.h"

class TigerManState_NormalDamaged_Face : public EnemyState_DamagedBase
{
public:
	TigerManState_NormalDamaged_Face();
	~TigerManState_NormalDamaged_Face() override;

	TigerManState_NormalDamaged_Face(const TigerManState_NormalDamaged_Face& _Other) = delete;
	TigerManState_NormalDamaged_Face(TigerManState_NormalDamaged_Face&& _Other) noexcept = delete;
	TigerManState_NormalDamaged_Face& operator=(const TigerManState_NormalDamaged_Face& _Other) = delete;
	TigerManState_NormalDamaged_Face& operator=(const TigerManState_NormalDamaged_Face&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	void LoadAnimation();
	void CreateAnimation();
};

