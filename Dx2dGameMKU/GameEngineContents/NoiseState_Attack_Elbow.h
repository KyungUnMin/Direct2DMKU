#pragma once
#include "BossState_AttackBase.h"

class NoiseState_Attack_Elbow : public BossState_AttackBase
{
public:
	NoiseState_Attack_Elbow();
	~NoiseState_Attack_Elbow() override;

	NoiseState_Attack_Elbow(const NoiseState_Attack_Elbow& _Other) = delete;
	NoiseState_Attack_Elbow(NoiseState_Attack_Elbow&& _Other) noexcept = delete;
	NoiseState_Attack_Elbow& operator=(const NoiseState_Attack_Elbow& _Other) = delete;
	NoiseState_Attack_Elbow& operator=(const NoiseState_Attack_Elbow&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

	void Attack() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;
	static const int Damage;

	void LoadAnimation();
	void CreateAnimation();
};

