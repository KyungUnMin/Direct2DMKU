#pragma once
#include "EnemyState_AttackBase.h"

class CheerleaderState_Attack_SideKick : public EnemyState_AttackBase
{
public:
	CheerleaderState_Attack_SideKick();
	~CheerleaderState_Attack_SideKick() override;

	CheerleaderState_Attack_SideKick(const CheerleaderState_Attack_SideKick& _Other) = delete;
	CheerleaderState_Attack_SideKick(CheerleaderState_Attack_SideKick&& _Other) noexcept = delete;
	CheerleaderState_Attack_SideKick& operator=(const CheerleaderState_Attack_SideKick& _Other) = delete;
	CheerleaderState_Attack_SideKick& operator=(const CheerleaderState_Attack_SideKick&& _Other) noexcept = delete;

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

