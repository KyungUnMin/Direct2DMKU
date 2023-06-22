#pragma once
#include "EnemyStateBase.h"

class NoiseState_JumpToStage : public EnemyStateBase
{
public:
	NoiseState_JumpToStage();
	~NoiseState_JumpToStage() override;

	NoiseState_JumpToStage(const NoiseState_JumpToStage& _Other) = delete;
	NoiseState_JumpToStage(NoiseState_JumpToStage&& _Other) noexcept = delete;
	NoiseState_JumpToStage& operator=(const NoiseState_JumpToStage& _Other) = delete;
	NoiseState_JumpToStage& operator=(const NoiseState_JumpToStage&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::vector<std::string_view> AniFileNames;
	static const float AniInterTime;
	

	enum class State
	{
		Ready,
		Jump,
		Fall,
		Land
	};

	State CurState = State::Ready;
	std::shared_ptr<class GameEngineSpriteRenderer> Shadow = nullptr;

	void LoadAnimation();
	void CreateAnimation();

	void Update_Ready(float _DeltaTime);
	void Update_Jump(float _DeltaTime);
	void Update_Fall(float _DeltaTime);
	void Update_Land(float _DeltaTime);

	void ChangeStateAndAni(State _Next);
};

