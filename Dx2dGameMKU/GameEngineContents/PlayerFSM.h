#pragma once
#include "FSMBase.h"

enum class PlayerStateType
{
	Idle,
	Move,
	Jump,
	Fall,
	Dash,

	COUNT
};

class PlayerFSM : public FSMBase
{
public:
	PlayerFSM();
	~PlayerFSM() override;

	PlayerFSM(const PlayerFSM& _Other) = delete;
	PlayerFSM(PlayerFSM&& _Other) noexcept = delete;
	PlayerFSM& operator=(const PlayerFSM& _Other) = delete;
	PlayerFSM& operator=(const PlayerFSM&& _Other) noexcept = delete;

	void Init();

	void ChangeState(size_t _NextIndex) override;
	
	inline PlayerStateType GetLastMovement() const
	{
		return LastMoveState;
	}

protected:


private:
	//Move와 Dash중 어떤게 마지막으로 실행되었는지
	PlayerStateType LastMoveState = PlayerStateType::Idle;
};

