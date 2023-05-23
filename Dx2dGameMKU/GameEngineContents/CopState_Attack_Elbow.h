#pragma once
#include "EnemyState_AttackBase.h"

class CopState_Attack_Elbow : public EnemyState_AttackBase
{
public:
	CopState_Attack_Elbow();
	~CopState_Attack_Elbow() override;

	CopState_Attack_Elbow(const CopState_Attack_Elbow& _Other) = delete;
	CopState_Attack_Elbow(CopState_Attack_Elbow&& _Other) noexcept = delete;
	CopState_Attack_Elbow& operator=(const CopState_Attack_Elbow& _Other) = delete;
	CopState_Attack_Elbow& operator=(const CopState_Attack_Elbow&& _Other) noexcept = delete;


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

