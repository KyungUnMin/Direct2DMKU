#pragma once
#include "BossState_AttackBase.h"

class NoiseState_Attack_Roar : public BossState_AttackBase
{
public:
	NoiseState_Attack_Roar();
	~NoiseState_Attack_Roar() override;

	NoiseState_Attack_Roar(const NoiseState_Attack_Roar& _Other) = delete;
	NoiseState_Attack_Roar(NoiseState_Attack_Roar&& _Other) noexcept = delete;
	NoiseState_Attack_Roar& operator=(const NoiseState_Attack_Roar& _Other) = delete;
	NoiseState_Attack_Roar& operator=(const NoiseState_Attack_Roar&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

	void Attack() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;
	static const int Damage;

	bool IsAttackOk = false;

	void LoadAnimation();
	void CreateAnimation();
};

