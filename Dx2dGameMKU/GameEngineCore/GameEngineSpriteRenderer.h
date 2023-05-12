#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineSprite.h"


/*
	애니메이션 1개에 대한 정보
*/
class AnimationInfo : public std::enable_shared_from_this<AnimationInfo>
{
	friend class GameEngineSpriteRenderer;

private:
	GameEngineSpriteRenderer* Parent = nullptr;
	std::shared_ptr<GameEngineSprite> Sprite = nullptr;
	bool IsEndValue = false;

	void Reset();
	void Update(float _DeltaTime);

	//현재 프레임의 정보를 반환한다
	const SpriteInfo& CurSpriteInfo();

public:
	size_t CurFrame = 0;
	size_t StartFrame = -1;
	size_t EndFrame = -1;
	float CurTime = 0.0f;
	float Inter = 0.1f;
	bool Loop = true;
	bool ScaleToImage = false;

	bool IsEnd();
};

class AnimationParameter
{
public:
	std::string_view AnimationName = "";
	std::string_view SpriteName = "";

	size_t Start = static_cast<size_t>(-1);
	size_t End = static_cast<size_t>(-1);

	float FrameInter = 0.1f;
	bool Loop = true;
	bool ScaleToImage = false;
};

class GameEngineSpriteRenderer : public GameEngineRenderer
{
public:
	GameEngineSpriteRenderer();
	~GameEngineSpriteRenderer() override;

	GameEngineSpriteRenderer(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer(GameEngineSpriteRenderer&& _Other) noexcept = delete;
	GameEngineSpriteRenderer& operator=(const GameEngineSpriteRenderer& _Other) = delete;
	GameEngineSpriteRenderer& operator=(const GameEngineSpriteRenderer&& _Other) noexcept = delete;

	void SetScaleToTexture(const std::string_view& _Name);

	void SetTexture(const std::string_view& _Name);

	inline void SetScaleRatio(float _Ratio)
	{
		ScaleRatio = _Ratio;
	}


	void SetFlipX();
	void SetFlipY();


	std::shared_ptr<AnimationInfo> FindAnimation(const std::string_view& _Name);

	std::shared_ptr<AnimationInfo> CreateAnimation(const AnimationParameter& _Paramter);


	void ChangeAnimation(const std::string_view& _Name, bool _Force, size_t _Frame = -1)
	{
		ChangeAnimation(_Name, _Frame,_Force);
	}

	void ChangeAnimation(const std::string_view& _Name, size_t _Frame = -1, bool _Force = true);


	//void AllAnimation();

	inline bool IsAnimationEnd() const
	{
		return CurAnimation->IsEnd();
	}

protected:

private:
	std::map<std::string, std::shared_ptr<AnimationInfo>> Animations;
	std::shared_ptr<AnimationInfo> CurAnimation = nullptr;
	
	//애니메이션을 그릴 UV 정보
	float4 AtlasData = {0.f, 0.f, 1.f, 1.f};
	float ScaleRatio = 1.0f;

	void Start() override;
	void Render(float _DeltaTime) override;
};

