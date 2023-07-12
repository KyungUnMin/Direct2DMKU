#pragma once
#include "EnemyStateBase.h"

class NoiseState_JumpToField : public EnemyStateBase
{
public:
	NoiseState_JumpToField();
	~NoiseState_JumpToField() override;

	NoiseState_JumpToField(const NoiseState_JumpToField& _Other) = delete;
	NoiseState_JumpToField(NoiseState_JumpToField&& _Other) noexcept = delete;
	NoiseState_JumpToField& operator=(const NoiseState_JumpToField& _Other) = delete;
	NoiseState_JumpToField& operator=(const NoiseState_JumpToField&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

private:
	static const std::vector<std::string_view> AniFileNames;
	static const float AniInterTime;
	static const size_t HandsUpLoopCount;

	static const std::vector<std::string_view> CrowdSfx;
	static const std::vector<std::string_view> PhaseBGM;


	enum class State
	{
		Ready,
		Jump,
		Fall,
		Land,
		Struct,
		UnStruct,
	};

	State CurState = State::Ready;
	std::shared_ptr<class GameEngineSpriteRenderer> Shadow = nullptr;
	std::shared_ptr<class GlichSideAttack> AttackEffect = nullptr;
	float4 OriginPlayerColScale = float4::Zero;
	class BossFSMBase* BossFsmPtr = nullptr;
	size_t CurPhase = -1;

	void LoadAnimation();
	void CreateAnimations();
	void CreateAnimation(State _StateaAni, size_t _EndFrm, bool _Loop);
	void CreateAnimation(State _StateaAni, const std::vector<size_t>& _AniFrms, bool _Loop);

	void PlayCrowdSfx();
	void ChangeBGM();


	void Update_Ready(float _DeltaTime);
	void Update_Jump(float _DeltaTime);
	void Update_Fall(float _DeltaTime);
	void Update_Land(float _DeltaTime);
	void Update_Struct(float _DeltaTime);
	void Update_UnStruct(float _DeltaTime);

	void ChangeStateAndAni(State _Next);
};

