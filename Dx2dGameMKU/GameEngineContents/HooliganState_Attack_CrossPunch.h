#pragma once
#include "EnemyState_AttackBase.h"

class HooliganState_Attack_CrossPunch : public EnemyState_AttackBase
{
public:
	HooliganState_Attack_CrossPunch();
	~HooliganState_Attack_CrossPunch() override;

	HooliganState_Attack_CrossPunch(const HooliganState_Attack_CrossPunch& _Other) = delete;
	HooliganState_Attack_CrossPunch(HooliganState_Attack_CrossPunch&& _Other) noexcept = delete;
	HooliganState_Attack_CrossPunch& operator=(const HooliganState_Attack_CrossPunch& _Other) = delete;
	HooliganState_Attack_CrossPunch& operator=(const HooliganState_Attack_CrossPunch&& _Other) noexcept = delete;

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

