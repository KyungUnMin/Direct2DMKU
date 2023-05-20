#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>

class ContentsSelfRenderer : public GameEngineSpriteRenderer
{
public:
	enum class CamType
	{
		MainCamera = 0,


		UI = 100,
		UNKNOWN
	};


	ContentsSelfRenderer();
	~ContentsSelfRenderer() override;

	ContentsSelfRenderer(const ContentsSelfRenderer& _Other) = delete;
	ContentsSelfRenderer(ContentsSelfRenderer&& _Other) noexcept = delete;
	ContentsSelfRenderer& operator=(const ContentsSelfRenderer& _Other) = delete;
	ContentsSelfRenderer& operator=(const ContentsSelfRenderer&& _Other) noexcept = delete;

	void Init(CamType _CamOrder);

	//void SetTexture()

protected:
	void Start() override{}
	void Update(float _DeltaTime) override;

private:
	CamType Order = CamType::UNKNOWN;
};

