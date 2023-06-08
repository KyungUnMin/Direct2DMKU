#pragma once
#include "BossState_AttackBase.h"

class MisuzuState_Attack_Roar : public BossState_AttackBase
{
public:
	MisuzuState_Attack_Roar();
	~MisuzuState_Attack_Roar() override;

	MisuzuState_Attack_Roar(const MisuzuState_Attack_Roar& _Other) = delete;
	MisuzuState_Attack_Roar(MisuzuState_Attack_Roar&& _Other) noexcept = delete;
	MisuzuState_Attack_Roar& operator=(const MisuzuState_Attack_Roar& _Other) = delete;
	MisuzuState_Attack_Roar& operator=(const MisuzuState_Attack_Roar&& _Other) noexcept = delete;


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

