#pragma once
#include "PlayerStateBase.h"

enum class KeyNames;

class PlayerStateIdle : public PlayerStateBase
{
public:
	PlayerStateIdle();
	~PlayerStateIdle() override;

	PlayerStateIdle(const PlayerStateIdle& _Other) = delete;
	PlayerStateIdle(PlayerStateIdle&& _Other) noexcept = delete;
	PlayerStateIdle& operator=(const PlayerStateIdle& _Other) = delete;
	PlayerStateIdle& operator=(const PlayerStateIdle&& _Other) noexcept = delete;

protected:
	//Start에서 애니메이션 준비하자
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::vector<KeyNames> ArrowKeyNames;
};

