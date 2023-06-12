#pragma once
#include "BossState_AttackBase.h"

class YamadaState_Attack_Roar : public BossState_AttackBase
{
public:
	YamadaState_Attack_Roar();
	~YamadaState_Attack_Roar() override;

	YamadaState_Attack_Roar(const YamadaState_Attack_Roar& _Other) = delete;
	YamadaState_Attack_Roar(YamadaState_Attack_Roar&& _Other) noexcept = delete;
	YamadaState_Attack_Roar& operator=(const YamadaState_Attack_Roar& _Other) = delete;
	YamadaState_Attack_Roar& operator=(const YamadaState_Attack_Roar&& _Other) noexcept = delete;


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

