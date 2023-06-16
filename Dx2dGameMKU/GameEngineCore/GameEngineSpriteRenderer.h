#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineSprite.h"
#include "EngineContentRenderingStruct.h"


/*
	�ִϸ��̼� 1���� ���� ����
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

	//���� �������� ������ ��ȯ�Ѵ�
	const SpriteInfo& CurSpriteInfo();


	inline void PauseOn()
	{
		IsPauseValue = true;
	}

	inline void PauseOff()
	{
		IsPauseValue = false;
	}

public:
	size_t CurFrame = 0;
	size_t StartFrame = -1;
	size_t EndFrame = -1;
	float CurTime = 0.0f;
	float Inter = 0.1f;
	bool Loop = true;
	bool ScaleToImage = false;
	bool IsPauseValue = false;
	std::vector<size_t> FrameIndex = std::vector<size_t>();
	std::vector<float >FrameTime = std::vector<float>();

	//�ش� �������϶� ó���� �ݹ��̺�Ʈ
	std::map<size_t, std::function<void()>> UpdateEventFunction;
	//�ش� �����ӿ� ������ �� ó���� �ݹ��̺�Ʈ
	std::map<size_t, std::function<void()>> StartEventFunction;

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

	std::vector<size_t> FrameIndex = std::vector<size_t>();
	std::vector<float >FrameTime = std::vector<float>();
};


enum class ClipXDir
{
	Left,
	Right,
};

enum class ClipYDir
{
	Top,
	Bot,
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


	inline bool IsAnimationEnd() const
	{
		return CurAnimation->IsEnd();
	}

	size_t GetCurrentFrame()
	{
		return CurAnimation->FrameIndex[CurAnimation->CurFrame];
	}

	float4 GetAtlasData()
	{
		return AtlasData;
	}

	
	void ImageClippingX(float _Ratio, ClipXDir _Dir);
	void ImageClippingY(float _Ratio, ClipYDir _Dir);


	inline float GetScaleRatio() const
	{
		return ScaleRatio;
	}

	//�ִϸ��̼��� �ƴ� ��������Ʈ�� �߸� �̹����� ������ �� ���(�̸����� ã��)
	void SetSprite(const std::string_view& _SpriteName, size_t _Frame = 0);

	//�ִϸ��̼��� �ƴ� ��������Ʈ�� �߸� �̹����� ������ �� ���(���� Sprite�� Frame���� ã��)
	void SetFrame(size_t _Frame);


	void SetAnimPauseOn()
	{
		CurAnimation->PauseOn();
	}

	void SetAnimPauseOff()
	{
		CurAnimation->PauseOff();
	}

	//���̴����� �ؽ�ó�� ������ ���ϴ� ������ۿ� ����� ��
	ColorOption ColorOptionValue;

	void SetAnimationUpdateEvent(const std::string_view& _AnimationName, size_t _Frame, std::function<void()> _Event);

	void SetAnimationStartEvent(const std::string_view& _AnimationName, size_t _Frame, std::function<void()> _Event);

	std::string GetTexName();

protected:
	void SpriteRenderInit();

	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	float4 AtlasData = { 0.f, 0.f, 1.f, 1.f };
	float4 Clip = float4::One;

private:
	std::map<std::string, std::shared_ptr<AnimationInfo>> Animations;
	std::shared_ptr<AnimationInfo> CurAnimation = nullptr;
	
	std::shared_ptr<GameEngineSprite> Sprite = nullptr;
	size_t Frame = -1;


	
	//std::shared_ptr<GameEngineTexture> CurTexture;

	//�ִϸ��̼��� �׸� UV ����
	float ScaleRatio = 1.0f;
};

