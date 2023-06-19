#pragma once
#include "BossState_AttackBase.h"

class NoiseState_Attack_AxeGrind : public BossState_AttackBase
{
public:
	NoiseState_Attack_AxeGrind();
	~NoiseState_Attack_AxeGrind() override;

	NoiseState_Attack_AxeGrind(const NoiseState_Attack_AxeGrind& _Other) = delete;
	NoiseState_Attack_AxeGrind(NoiseState_Attack_AxeGrind&& _Other) noexcept = delete;
	NoiseState_Attack_AxeGrind& operator=(const NoiseState_Attack_AxeGrind& _Other) = delete;
	NoiseState_Attack_AxeGrind& operator=(const NoiseState_Attack_AxeGrind&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

	void Attack() override{}

private:
	static const std::string_view Idle_AniFileName;
	static const std::string_view Catch_AniFileName;
	static const float AniInterTime;

	static const float AxeMoveDuration;
	static const float AxeStayDuration;

	enum class State
	{
		Idle,
		Catch,
	};

	State CurState = State::Idle;
	const float TotalDuration = (AxeMoveDuration * 2.f) + AxeStayDuration;

	void LoadAnimation();
	void CreateAnimation();
	void CreateAxe();

	void Update_Idle();
	void Update_Catch();
};

