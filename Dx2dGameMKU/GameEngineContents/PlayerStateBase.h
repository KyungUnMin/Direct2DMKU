#pragma once
#include "StateBase.h"

enum class KeyNames;

class PlayerStateBase : public StateBase
{
public:
	PlayerStateBase();
	virtual ~PlayerStateBase() = 0;

	PlayerStateBase(const PlayerStateBase& _Other) = delete;
	PlayerStateBase(PlayerStateBase&& _Other) noexcept = delete;
	PlayerStateBase& operator=(const PlayerStateBase& _Other) = delete;
	PlayerStateBase& operator=(const PlayerStateBase&& _Other) noexcept = delete;

protected:

	//�Ʒ� 3�� �������� �ӽ�
	bool IsOnAir() { return false; }

	void Update_Move(float _DeltaTime);

	bool Check_Idle();

private:
	static const std::vector<KeyNames> IdleCheckKeys;
};

