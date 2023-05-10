#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineSprite.h"


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

	//���� �������� �ؽ�ó�� ��ȯ�Ѵ�
	std::shared_ptr<GameEngineTexture> CurFrameTexture();

public:
	size_t CurFrame = 0;
	size_t StartFrame = -1;
	size_t EndFrame = -1;
	float CurTime = 0.0f;
	float Inter = 0.1f;
	bool Loop = true;

	bool IsEnd();
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

	void SetFlipX();
	void SetFlipY();



	//-----------------�ִϸ��̼�-----------------

	std::shared_ptr<AnimationInfo> FindAnimation(const std::string_view& _Name);

	//�ִϸ��̼� �̸�, ������, etc...
	std::shared_ptr<AnimationInfo> CreateAnimation(
		const std::string_view& _Name,
		const std::string_view& _SpriteName,
		float _FrameInter = 0.1f,
		int _Start = -1,
		int _End = -1,
		bool _Loop = true);


	void ChangeAnimation(const std::string_view& _Name, bool _Force, size_t _Frame = -1)
	{
		ChangeAnimation(_Name, _Frame,_Force);
	}

	void ChangeAnimation(const std::string_view& _Name, size_t _Frame = -1, bool _Force = true);

protected:

private:
	std::map<std::string, std::shared_ptr<AnimationInfo>> Animations;
	std::shared_ptr<AnimationInfo> CurAnimation = nullptr;
	
	void Start() override;
	void Render(float _DeltaTime) override;
};

