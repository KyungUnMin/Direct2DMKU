#pragma once
#include "BossState_AttackBase.h"

class NoiseState_Attack_GetUp : public BossState_AttackBase
{
public:
	NoiseState_Attack_GetUp();
	~NoiseState_Attack_GetUp() override;

	NoiseState_Attack_GetUp(const NoiseState_Attack_GetUp& _Other) = delete;
	NoiseState_Attack_GetUp(NoiseState_Attack_GetUp&& _Other) noexcept = delete;
	NoiseState_Attack_GetUp& operator=(const NoiseState_Attack_GetUp& _Other) = delete;
	NoiseState_Attack_GetUp& operator=(const NoiseState_Attack_GetUp&& _Other) noexcept = delete;

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

