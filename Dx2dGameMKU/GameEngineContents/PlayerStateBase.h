#pragma once
#include "StateBase.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "RCGDefine.h"

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
	std::shared_ptr<class GameEngineSprite> SpritePtr;
	std::shared_ptr<class AnimationInfo> AniInfoPtr = nullptr;

	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

	//빌드위한 임시
	bool IsOnAir() { return false; }

	void Update_Move(float _DeltaTime, const float4& _Speed = float4{400.f, 200.f});

	bool Check_Idle();

	//애니메이션의 크기를 직접 지정
	inline void SetAniScale(const float4& _Scale)
	{
		AniScale = _Scale;
	}

private:
	static const std::vector<KeyNames> IdleCheckKeys;

	size_t PrevAniFrame = -1;
	std::shared_ptr<class BackGround> BGPtr = nullptr;
	float4 AniScale = float4::Zero;

	void SettingRenderTransForAni();
};

