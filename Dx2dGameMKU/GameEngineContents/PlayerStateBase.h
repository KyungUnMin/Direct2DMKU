#pragma once
#include "StateBase.h"

class FieldPlayer;
class PlayerFSM;
class FieldLevelBase;
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
	void Start() override;

	inline FieldPlayer* GetPlayerPtr() const
	{
		return PlayerPtr;
	}

	inline FieldLevelBase* GetLevel() const
	{
		return Level;
	}

	bool IsOnAir();

	void Update_Move(float _DeltaTime);


	inline PlayerFSM* GetPlayerFsm() const
	{
		return FsmPtr;
	}

	bool Check_Idle();


private:
	static const std::vector<KeyNames> IdleCheckKeys;

	FieldPlayer* PlayerPtr = nullptr;
	FieldLevelBase* Level = nullptr;
	PlayerFSM* FsmPtr = nullptr;
};

