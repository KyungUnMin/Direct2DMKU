#pragma once
#include "PlayerStateBase.h"

class GameEngineTransform;
class BackGround;

class PlayerState_MovementBase : public PlayerStateBase
{
public:
	PlayerState_MovementBase();
	~PlayerState_MovementBase() override;

	PlayerState_MovementBase(const PlayerState_MovementBase& _Other) = delete;
	PlayerState_MovementBase(PlayerState_MovementBase&& _Other) noexcept = delete;
	PlayerState_MovementBase& operator=(const PlayerState_MovementBase& _Other) = delete;
	PlayerState_MovementBase& operator=(const PlayerState_MovementBase&& _Other) noexcept = delete;

	void Update_Move(float _DeltaTime, const float4& _Speed = float4{ 400.f, 200.f });

	bool Check_Idle();

protected:
	void Start() override;

	inline std::shared_ptr<BackGround> GetBackGround() const
	{
		return BGPtr;
	}


	inline GameEngineTransform* GetPlayerTransform() const
	{
		return PlayerTrans;
	}


private:
	static const std::vector<KeyNames> IdleCheckKeys;

	std::shared_ptr<BackGround> BGPtr = nullptr;
	GameEngineTransform* PlayerTrans = nullptr;
};

