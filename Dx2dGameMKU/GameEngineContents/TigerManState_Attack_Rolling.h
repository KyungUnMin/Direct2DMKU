#pragma once
#include "EnemyState_AttackBase.h"

class TigerManState_Attack_Rolling : public EnemyState_AttackBase
{
public:
	TigerManState_Attack_Rolling();
	~TigerManState_Attack_Rolling() override;

	TigerManState_Attack_Rolling(const TigerManState_Attack_Rolling& _Other) = delete;
	TigerManState_Attack_Rolling(TigerManState_Attack_Rolling&& _Other) noexcept = delete;
	TigerManState_Attack_Rolling& operator=(const TigerManState_Attack_Rolling& _Other) = delete;
	TigerManState_Attack_Rolling& operator=(const TigerManState_Attack_Rolling&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

	void Attack() override;

	void OnAttackSound() override{}

private:
	static const std::vector<std::string_view> AniNames;
	static const std::vector<std::string_view> AniFileNames;
	static const std::vector <std::pair<int, int>> AniCutFrames;
	static const std::vector <std::pair<size_t, size_t>> AniIndexes;
	static const float AniInterTime;
	static const int Damage;

	enum class State
	{
		RollStart,
		Rolling,
		RoolEnd,

		COUNT
	};


	const float Duration = 5.f;
	const float AttackWaitTime = 0.1f;

	const float TraceAcc = 1000.f;
	const float MaxSpeed = 2000.f;
	
	State CurState = State::RollStart;
	float RollInTime = 0.f;
	float LastAttack = 0.f;
	float4 TraceVec = float4::Zero;
	

	void LoadAnimation();
	void CreateAnimation();

	void Update_RollStart();
	void Update_Rolling(float _DeltaTime);
	void TracePlayer(float _DeltaTime);

	//일단 여기에 만들고 나중에 부모쪽으로 이동할꺼면 그때 하자
	void TeamKill();

	void Update_RollEnd();

	void Update_Sfx(float _DeltaTime);
};

