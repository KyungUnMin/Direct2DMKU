#pragma once
#include "EnemyState_AttackBase.h"

class MisuzuState_Attack_Slap : public EnemyState_AttackBase
{
public:
	MisuzuState_Attack_Slap();
	~MisuzuState_Attack_Slap() override;

	MisuzuState_Attack_Slap(const MisuzuState_Attack_Slap& _Other) = delete;
	MisuzuState_Attack_Slap(MisuzuState_Attack_Slap&& _Other) noexcept = delete;
	MisuzuState_Attack_Slap& operator=(const MisuzuState_Attack_Slap& _Other) = delete;
	MisuzuState_Attack_Slap& operator=(const MisuzuState_Attack_Slap&& _Other) noexcept = delete;

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


	void LoadAnimation();
	void CreateAnimation();
};

