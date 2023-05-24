#pragma once
#include "EnemyState_AttackBase.h"

class CheerleaderState_Attack_BackFlip : public EnemyState_AttackBase
{
public:
	CheerleaderState_Attack_BackFlip();
	~CheerleaderState_Attack_BackFlip() override;

	CheerleaderState_Attack_BackFlip(const CheerleaderState_Attack_BackFlip& _Other) = delete;
	CheerleaderState_Attack_BackFlip(CheerleaderState_Attack_BackFlip&& _Other) noexcept = delete;
	CheerleaderState_Attack_BackFlip& operator=(const CheerleaderState_Attack_BackFlip& _Other) = delete;
	CheerleaderState_Attack_BackFlip& operator=(const CheerleaderState_Attack_BackFlip&& _Other) noexcept = delete;

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

	const float4 ColOffset = float4::Right * 100.f;
	const float4 ColSize = float4::One * 150.f;

	void LoadAnimation();
	void CreateAnimation();
};

