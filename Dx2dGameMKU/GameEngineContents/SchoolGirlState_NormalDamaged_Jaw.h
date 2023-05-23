#pragma once
#include "EnemyState_DamagedBase.h"

class SchoolGirlState_NormalDamaged_Jaw : public EnemyState_DamagedBase
{
public:
	SchoolGirlState_NormalDamaged_Jaw();
	~SchoolGirlState_NormalDamaged_Jaw() override;

	SchoolGirlState_NormalDamaged_Jaw(const SchoolGirlState_NormalDamaged_Jaw& _Other) = delete;
	SchoolGirlState_NormalDamaged_Jaw(SchoolGirlState_NormalDamaged_Jaw&& _Other) noexcept = delete;
	SchoolGirlState_NormalDamaged_Jaw& operator=(const SchoolGirlState_NormalDamaged_Jaw& _Other) = delete;
	SchoolGirlState_NormalDamaged_Jaw& operator=(const SchoolGirlState_NormalDamaged_Jaw&& _Other) noexcept = delete;

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

