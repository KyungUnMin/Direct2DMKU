#pragma once
#include "EnemyState_AttackBase.h"

class MisuzuState_Attack_Elbow : public EnemyState_AttackBase
{
public:
	MisuzuState_Attack_Elbow();
	~MisuzuState_Attack_Elbow() override;

	MisuzuState_Attack_Elbow(const MisuzuState_Attack_Elbow& _Other) = delete;
	MisuzuState_Attack_Elbow(MisuzuState_Attack_Elbow&& _Other) noexcept = delete;
	MisuzuState_Attack_Elbow& operator=(const MisuzuState_Attack_Elbow& _Other) = delete;
	MisuzuState_Attack_Elbow& operator=(const MisuzuState_Attack_Elbow&& _Other) noexcept = delete;


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

