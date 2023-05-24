#pragma once
#include "EnemyState_AttackBase.h"

class CheerleaderState_Attack_DoublePom : public EnemyState_AttackBase
{
public:
	CheerleaderState_Attack_DoublePom();
	~CheerleaderState_Attack_DoublePom() override;

	CheerleaderState_Attack_DoublePom(const CheerleaderState_Attack_DoublePom& _Other) = delete;
	CheerleaderState_Attack_DoublePom(CheerleaderState_Attack_DoublePom&& _Other) noexcept = delete;
	CheerleaderState_Attack_DoublePom& operator=(const CheerleaderState_Attack_DoublePom& _Other) = delete;
	CheerleaderState_Attack_DoublePom& operator=(const CheerleaderState_Attack_DoublePom&& _Other) noexcept = delete;

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

	const float4 ColSize = float4::One * 150.f;
	const float JumpDuration = 0.8f;
	const float JumpMaxHeight = 50.f;

	void LoadAnimation();
	void CreateAnimation();
};

