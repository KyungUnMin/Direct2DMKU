#pragma once
#include "StateBase.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "RCGDefine.h"

enum class KeyNames;
class GameEngineSpriteRenderer;
class GameEngineSprite;
class AnimationInfo;

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
	void Start() override;
	void Update(float _DeltaTime) override;

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

	void SettingHeightRender();
	void SettingDirectionRender();
};

