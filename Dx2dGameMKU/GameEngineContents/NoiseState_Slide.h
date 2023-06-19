#pragma once
#include "EnemyStateBase.h"

class NoiseState_Slide : public EnemyStateBase
{
public:
	NoiseState_Slide();
	~NoiseState_Slide() override;

	NoiseState_Slide(const NoiseState_Slide& _Other) = delete;
	NoiseState_Slide(NoiseState_Slide&& _Other) noexcept = delete;
	NoiseState_Slide& operator=(const NoiseState_Slide& _Other) = delete;
	NoiseState_Slide& operator=(const NoiseState_Slide&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;
	void Update(float _DeltaTime) override;

private:
	static const std::vector<std::string_view> AniFileNames;
	static const float AniInterTime;

	enum class State
	{
		Start,
		Loop,
		End,
	};

	State CurState = State::Start;

	std::shared_ptr<class BackGround> BGPtr = nullptr;

	const float MoveSpeed = 1500.f;
	float4 MoveDir = float4::Zero;

	void LoadAnimation();
	void CreateAnimation();
	void ChangeStateAndAni(State _Next);

	void Update_Start(float _DeltaTime);
	void Update_Loop(float _DeltaTime);
	void Update_LoopMove(float _DeltaTime);
	void Update_LoopEffect(float _DeltaTime);
	void Update_End(float _DeltaTime);
};

