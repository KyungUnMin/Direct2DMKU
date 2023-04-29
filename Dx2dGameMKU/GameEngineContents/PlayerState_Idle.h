#pragma once
#include "PlayerStateBase.h"

enum class KeyNames;

class PlayerState_Idle : public PlayerStateBase
{
public:
	PlayerState_Idle();
	~PlayerState_Idle() override;

	PlayerState_Idle(const PlayerState_Idle& _Other) = delete;
	PlayerState_Idle(PlayerState_Idle&& _Other) noexcept = delete;
	PlayerState_Idle& operator=(const PlayerState_Idle& _Other) = delete;
	PlayerState_Idle& operator=(const PlayerState_Idle&& _Other) noexcept = delete;

protected:
	//Start���� �ִϸ��̼� �غ�����
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::vector<KeyNames> ArrowKeyNames;

	void SetArrowKey();
	void LoadAnimation();
	void CreateAnimation();
};
