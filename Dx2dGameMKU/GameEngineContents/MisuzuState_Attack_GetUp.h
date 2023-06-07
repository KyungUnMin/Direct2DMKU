#pragma once
#include "EnemyState_AttackBase.h"

class MisuzuState_Attack_GetUp : public EnemyState_AttackBase
{
public:
	MisuzuState_Attack_GetUp();
	~MisuzuState_Attack_GetUp() override;

	MisuzuState_Attack_GetUp(const MisuzuState_Attack_GetUp& _Other) = delete;
	MisuzuState_Attack_GetUp(MisuzuState_Attack_GetUp&& _Other) noexcept = delete;
	MisuzuState_Attack_GetUp& operator=(const MisuzuState_Attack_GetUp& _Other) = delete;
	MisuzuState_Attack_GetUp& operator=(const MisuzuState_Attack_GetUp&& _Other) noexcept = delete;

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

