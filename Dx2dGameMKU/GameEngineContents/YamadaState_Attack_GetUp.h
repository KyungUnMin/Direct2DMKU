#pragma once
#include "BossState_AttackBase.h"

class YamadaState_Attack_GetUp : public BossState_AttackBase
{
public:
	YamadaState_Attack_GetUp();
	~YamadaState_Attack_GetUp() override;

	YamadaState_Attack_GetUp(const YamadaState_Attack_GetUp& _Other) = delete;
	YamadaState_Attack_GetUp(YamadaState_Attack_GetUp&& _Other) noexcept = delete;
	YamadaState_Attack_GetUp& operator=(const YamadaState_Attack_GetUp& _Other) = delete;
	YamadaState_Attack_GetUp& operator=(const YamadaState_Attack_GetUp&& _Other) noexcept = delete;

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

