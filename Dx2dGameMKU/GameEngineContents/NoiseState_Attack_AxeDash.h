#pragma once
#include "BossState_AttackBase.h"

#include <GameEnginePlatform/GameEngineSound.h>

class NoiseState_Attack_AxeDash : public BossState_AttackBase
{
public:
	NoiseState_Attack_AxeDash();
	~NoiseState_Attack_AxeDash() override;

	NoiseState_Attack_AxeDash(const NoiseState_Attack_AxeDash& _Other) = delete;
	NoiseState_Attack_AxeDash(NoiseState_Attack_AxeDash&& _Other) noexcept = delete;
	NoiseState_Attack_AxeDash& operator=(const NoiseState_Attack_AxeDash& _Other) = delete;
	NoiseState_Attack_AxeDash& operator=(const NoiseState_Attack_AxeDash&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

	void Attack() override {}

private:
	static const std::vector<std::string_view> AniFileNames;
	static const float AniInterTime;
	static const float4 ReflectArea;
	static const size_t ReflectMaxCnt;
	static const float StandardFollowRange;
	static const float StandardFollowDuration;
	static const float StartDashRotRange;
	static const float4 FanSpawnPos;

	enum class State
	{
		DashStart,
		DashLoop,
		DashLand,

		WaitIdle,
		WaitCatch
	};

	State CurState = State::DashStart;
	std::shared_ptr<class NoiseAxe> Axe = nullptr;

	const float DashSpeed = 1500.f;
	float4 DashDir = float4::Zero;
	size_t ReflectCount = 1;
	std::vector<float4> ReflectPositions;

	size_t FollowIndex = 1;
	float FollowTimer = 0.f;
	float FollowDuration = 0.f;

	GameEngineSoundPlayer AxeLoopSFX;

	void LoadAnimation();
	void CreateAnimation();
	void ChangeStateAndAni(State _Next);
	void CreateFan();

	void Update_DashStart(float _DeltaTime);
	void Update_DashLoop(float _DeltaTime);
	void Update_DahsLoopEffect(float _DeltaTime);

	enum class ReflectType
	{
		Left,
		Right,
		Up,
		Down,
		None,
	};


	void ReflectDirection(const float4 _PrevPos, ReflectType _Type);
	void SetLookDir(ReflectType _Type);


	void Update_DashLand(float _DeltaTime);
	void Update_WaitIdle(float _DeltaTime);
	void Update_WaitCatch(float _DeltaTime);

	void CalcFollowDuration();
};


