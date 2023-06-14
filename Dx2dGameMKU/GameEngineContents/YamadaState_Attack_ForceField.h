#pragma once
#include "BossState_AttackBase.h"

class YamadaState_Attack_ForceField : public BossState_AttackBase
{
public:
	YamadaState_Attack_ForceField();
	~YamadaState_Attack_ForceField() override;

	YamadaState_Attack_ForceField(const YamadaState_Attack_ForceField& _Other) = delete;
	YamadaState_Attack_ForceField(YamadaState_Attack_ForceField&& _Other) noexcept = delete;
	YamadaState_Attack_ForceField& operator=(const YamadaState_Attack_ForceField& _Other) = delete;
	YamadaState_Attack_ForceField& operator=(const YamadaState_Attack_ForceField&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

	void Attack() override{}

private:
	static const std::vector<std::string_view> AniNames;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	enum class State
	{
		Ready,
		Rise,
		Hang,
		Land,
		Spread,
	};

	State CurState = State::Ready;
	const float MaxHeight = 15.f;
	float LandStartHeight = 0.f;

	//공중부양 시간
	const float EtyrtTime = 5.f;
	const float RiseTime = 1.f;
	std::shared_ptr<class YamadaEnergyBallCtrl> EnergyBallCtrl = nullptr;

	void LoadAnimation();
	void CreateAnimation();
	void ChangeStateAndAni(State _NextState);

	void Update_Ready(float _DeltaTime);
	void Update_Rise(float _DeltaTime);
	void Update_Hang(float _DeltaTime);
	void Update_Land(float _DeltaTime);
	void Update_Spread(float _DeltaTime);
};

