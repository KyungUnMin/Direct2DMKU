#pragma once
#include "EnemyState_AttackBase.h"

class CopState_Attack_TossNades : public EnemyState_AttackBase
{
public:
	CopState_Attack_TossNades();
	~CopState_Attack_TossNades() override;

	CopState_Attack_TossNades(const CopState_Attack_TossNades& _Other) = delete;
	CopState_Attack_TossNades(CopState_Attack_TossNades&& _Other) noexcept = delete;
	CopState_Attack_TossNades& operator=(const CopState_Attack_TossNades& _Other) = delete;
	CopState_Attack_TossNades& operator=(const CopState_Attack_TossNades&& _Other) noexcept = delete;

	void WeaponInit(std::shared_ptr<class CopGrenade> _Grenade);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

	void Attack() override{}

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	void LoadAnimation();
	void CreateAnimation();
};

