#pragma once
#include "BossState_AttackBase.h"

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

	void Attack() override {}

private:
	//static const std::vector<std::string_view> AniFileNames;
	//static const float AniInterTime;

	enum class State
	{
		Start,
		Loop,
		End,
	};

	State CurState = State::Start;
	std::shared_ptr<class BackGround> BGPtr = nullptr;

	void LoadAnimation();
	void CreateAnimation();
	void CreateAxe();

};

