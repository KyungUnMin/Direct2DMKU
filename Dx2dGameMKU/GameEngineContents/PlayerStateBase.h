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
	void EnterState() override;

	//빌드위한 임시
	bool IsOnAir() { return false; }

	void Update_Move(float _DeltaTime, const float4& _Speed = float4{400.f, 200.f});

	bool Check_Idle();

	inline std::shared_ptr<GameEngineSpriteRenderer> GetRenderer()
	{
		return Renderer;
	}

	void SetAnimationInfo(std::shared_ptr<GameEngineSprite> _SpritePtr, std::shared_ptr<AnimationInfo> _AniInfoPtr);

	void SetAniFrameOffset(size_t _Index, const float4& _Offset);

private:
	static const std::vector<KeyNames> IdleCheckKeys;

	std::shared_ptr<class BackGround> BGPtr = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;

	//현재프레임의 텍스처 정보를 얻기 위해
	std::shared_ptr<GameEngineSprite> SpritePtr = nullptr;
	//애니메이션이 어디 프레임에 위치해있는지 알기 위해
	std::shared_ptr<AnimationInfo> AniInfoPtr = nullptr;
	//애니메이션 프레임 별 오프셋
	std::vector<float4> AniFrameOffset;


	void SettingRenderTransForAni();

private:
	GameEngineTransform DEBUG_ANI_OFFSET;
	std::shared_ptr<class GameEngineActorGUI> TransformViewer = nullptr;

	void UPDATE_DEBUG_ANI_OFFSET();
};

