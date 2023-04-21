#pragma once
#include "FSMBase.h"

enum class PlayerStateType
{
	Idle,
	Move,
	Jump,
	Fall,

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

protected:


private:

};

