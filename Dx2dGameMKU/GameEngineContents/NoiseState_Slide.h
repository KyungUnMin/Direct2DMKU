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
	void ExitState() override;

private:
	static const std::vector<std::string_view> AniFileNames;
	static const float AniInterTime;

	static const float MoveDuration;

	enum class State
	{
		Start,
		Loop,
		End,
	};

	State CurState = State::Start;

	std::shared_ptr<class BackGround> BGPtr = nullptr;
	float4 StartPos = float4::Zero;
	float4 DestPos = float4::Zero;
	bool IsTargetPlayer = false;

	void LoadAnimation();
	void CreateAnimation();
	void ChangeStateAndAni(State _Next);
	void SettingDir();

	void Update_Start(float _DeltaTime);

	void Update_Loop(float _DeltaTime);
	void Update_LoopMove(float _Ratio);
	void Update_LoopEffect(float _DeltaTime);


	void Update_End(float _DeltaTime);
};

