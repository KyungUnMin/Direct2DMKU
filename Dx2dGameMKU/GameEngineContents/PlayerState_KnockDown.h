#pragma once
#include "PlayerState_DamagedBase.h"

class PlayerState_KnockDown : public PlayerState_DamagedBase
{
public:
	static const std::string_view AniFileName;

	PlayerState_KnockDown();
	~PlayerState_KnockDown() override;

	PlayerState_KnockDown(const PlayerState_KnockDown& _Other) = delete;
	PlayerState_KnockDown(PlayerState_KnockDown&& _Other) noexcept = delete;
	PlayerState_KnockDown& operator=(const PlayerState_KnockDown& _Other) = delete;
	PlayerState_KnockDown& operator=(const PlayerState_KnockDown&& _Other) noexcept = delete;

protected:
	void Start() override;

	void EnterState() override;
	void Update(float _DeltaTime) override;
	void ExitState() override;

private:
	std::shared_ptr<class GameEngineCollision> PlayerMainCollider = nullptr;

	const float StartAcc = 1500.f;
	const float BlowDuration = 0.5f;

	class GameEngineTransform* PlayerTrans = nullptr;
	float4 BlowDir = float4::Zero;
	std::shared_ptr<class BackGround> BGPtr = nullptr;
	std::shared_ptr<class ContinueBox> BoxUI = nullptr;

	void LoadAnimation();
	void CreateAnimation();

	void CreateContinueUI();
};

