#pragma once
#include "StateBase.h"

enum class KeyNames;

class PlayerStateBase : public StateBase
{
public:
	PlayerStateBase();
	~PlayerStateBase();

	PlayerStateBase(const PlayerStateBase& _Other) = delete;
	PlayerStateBase(PlayerStateBase&& _Other) noexcept = delete;
	PlayerStateBase& operator=(const PlayerStateBase& _Other) = delete;
	PlayerStateBase& operator=(const PlayerStateBase&& _Other) noexcept = delete;

protected:

	//아래 3개 빌드위한 임시
	bool IsOnAir() { return false; }

	void Update_Move(float _DeltaTime){}

	bool Check_Idle() { return false; }

private:
	static const std::vector<KeyNames> IdleCheckKeys;
};

