#pragma once
#include "EnemyState_AttackBase.h"

class CopState_Attack_BatonSmash : public EnemyState_AttackBase
{
public:
	CopState_Attack_BatonSmash();
	~CopState_Attack_BatonSmash() override;

	CopState_Attack_BatonSmash(const CopState_Attack_BatonSmash& _Other) = delete;
	CopState_Attack_BatonSmash(CopState_Attack_BatonSmash&& _Other) noexcept = delete;
	CopState_Attack_BatonSmash& operator=(const CopState_Attack_BatonSmash& _Other) = delete;
	CopState_Attack_BatonSmash& operator=(const CopState_Attack_BatonSmash&& _Other) noexcept = delete;

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

