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

	//아래 3개 빌드위한 임시
	bool IsOnAir() { return false; }

	void Update_Move(float _DeltaTime, const float4& _Speed = float4{400.f, 200.f});

	bool Check_Idle();

private:
	static const std::vector<KeyNames> IdleCheckKeys;
};

