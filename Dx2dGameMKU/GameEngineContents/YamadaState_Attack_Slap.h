#pragma once
#include "BossState_AttackBase.h"

class YamadaState_Attack_Slap : public BossState_AttackBase
{
public:
	YamadaState_Attack_Slap();
	~YamadaState_Attack_Slap() override;

	YamadaState_Attack_Slap(const YamadaState_Attack_Slap& _Other) = delete;
	YamadaState_Attack_Slap(YamadaState_Attack_Slap&& _Other) noexcept = delete;
	YamadaState_Attack_Slap& operator=(const YamadaState_Attack_Slap& _Other) = delete;
	YamadaState_Attack_Slap& operator=(const YamadaState_Attack_Slap&& _Other) noexcept = delete;

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
	static const int AttackFrm;


	void LoadAnimation();
	void CreateAnimation();
};

