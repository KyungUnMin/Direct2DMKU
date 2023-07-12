#pragma once
#include "BossState_AttackBase.h"


class NoiseState_Attack_GuitarSlashDash : public BossState_AttackBase
{
public:
	NoiseState_Attack_GuitarSlashDash();
	~NoiseState_Attack_GuitarSlashDash() override;

	NoiseState_Attack_GuitarSlashDash(const NoiseState_Attack_GuitarSlashDash& _Other) = delete;
	NoiseState_Attack_GuitarSlashDash(NoiseState_Attack_GuitarSlashDash&& _Other) noexcept = delete;
	NoiseState_Attack_GuitarSlashDash& operator=(const NoiseState_Attack_GuitarSlashDash& _Other) = delete;
	NoiseState_Attack_GuitarSlashDash& operator=(const NoiseState_Attack_GuitarSlashDash&& _Other) noexcept = delete;

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
	static const int AttackFrm;

	float4 StartPos = float4::Zero;
	float4 DestPos = float4::Zero;
	bool IsAttack = false;

	void LoadAnimation();
	void CreateAnimation();
};

