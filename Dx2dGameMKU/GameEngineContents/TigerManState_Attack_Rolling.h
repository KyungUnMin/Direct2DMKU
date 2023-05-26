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

	const float RollingDuration = 5.f;
	const float AttackWaitTime = 0.1f;

	State CurState = State::RollStart;
	float RollInTime = 0.f;
	float LastAttack = 0.f;


	void LoadAnimation();
	void CreateAnimation();

	void Update_RollStart();
	void Update_Rolling(float _DeltaTime);
	void Update_RollEnd();
};

