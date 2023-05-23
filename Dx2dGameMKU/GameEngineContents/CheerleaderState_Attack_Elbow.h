#pragma once
#include "EnemyState_AttackBase.h"

class CheerleaderState_Attack_Elbow : public EnemyState_AttackBase
{
public:
	CheerleaderState_Attack_Elbow();
	~CheerleaderState_Attack_Elbow() override;

	CheerleaderState_Attack_Elbow(const CheerleaderState_Attack_Elbow& _Other) = delete;
	CheerleaderState_Attack_Elbow(CheerleaderState_Attack_Elbow&& _Other) noexcept = delete;
	CheerleaderState_Attack_Elbow& operator=(const CheerleaderState_Attack_Elbow& _Other) = delete;
	CheerleaderState_Attack_Elbow& operator=(const CheerleaderState_Attack_Elbow&& _Other) noexcept = delete;


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

