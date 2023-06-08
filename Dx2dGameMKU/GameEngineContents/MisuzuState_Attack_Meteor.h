#pragma once
#include "BossState_AttackBase.h"

class MisuzuState_Attack_Meteor : public BossState_AttackBase
{
public:
	MisuzuState_Attack_Meteor();
	~MisuzuState_Attack_Meteor() override;

	MisuzuState_Attack_Meteor(const MisuzuState_Attack_Meteor& _Other) = delete;
	MisuzuState_Attack_Meteor(MisuzuState_Attack_Meteor&& _Other) noexcept = delete;
	MisuzuState_Attack_Meteor& operator=(const MisuzuState_Attack_Meteor& _Other) = delete;
	MisuzuState_Attack_Meteor& operator=(const MisuzuState_Attack_Meteor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;


	void Attack() override;

private:
	struct AniInfo
	{
		const std::string_view AniName = "";
		const std::pair<int, int> AniCutFram;
		const std::pair<size_t, size_t> AniFrm;
		bool Loop = false;
	};

	static const std::vector<AniInfo> AniInfoes;

	static const float AniInter;
	static const int Damage;
	static const int AttackFrm;

	enum class State
	{
		JumpUp,
		Jumping,
		Fall,
		Miss,
		Land,
	};

	std::shared_ptr<class GameEngineCollision> MainCollider = nullptr;

	State CurState = State::JumpUp;
	const float MaxHeight = 2000.f;
	const float Duration = 1.0f;
	const float LandDuration = 0.1f;
	const float LandHeight= 50.f;

	float Timer = 0.f;

	
	float4 MoveStartPos = float4::Zero;
	float4 MoveHalfPos = float4::Zero;
	float4 MoveDestPos = float4::Zero;
	


	void LoadAnimation();
	void CreateAnimation();
	void ChangeStateWithAni(State _NextState);

	void Update_JumpUp(float _DeltaTime);
	void Update_Jumping(float _DeltaTime);
	void Update_Fall(float _DeltaTime);

	void Update_JumpingMove(float _DeltaTime);
	void Update_FallMove(float _DeltaTime);

	void Update_Land(float _DeltaTime);
};

