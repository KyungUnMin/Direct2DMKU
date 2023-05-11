#pragma once
#include "StateBase.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "RCGDefine.h"

enum class KeyNames;
class GameEngineSpriteRenderer;

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

	inline std::shared_ptr<GameEngineSpriteRenderer> GetRenderer()
	{
		return Renderer;
	}

private:
	static const std::vector<KeyNames> IdleCheckKeys;

	std::shared_ptr<class BackGround> BGPtr = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;

	//true일때 오른쪽, false면 왼쪽
	bool RenderDir = true;

	void SettingRenderTransForAni();
	void SettingRenderDir();
};

