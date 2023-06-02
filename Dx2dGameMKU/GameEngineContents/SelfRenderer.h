#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>



/*
	기능은 전부 존재하지만 
	모든걸 외부에서 직접 호출시켜주어야 하는 렌더러
*/

enum class RCG_CamNumType;

class SelfRenderer : public GameEngineSpriteRenderer
{
public:
	SelfRenderer();
	~SelfRenderer() override;

	SelfRenderer(const SelfRenderer& _Other) = delete;
	SelfRenderer(SelfRenderer&& _Other) noexcept = delete;
	SelfRenderer& operator=(const SelfRenderer& _Other) = delete;
	SelfRenderer& operator=(const SelfRenderer&& _Other) noexcept = delete;

	
	void SetCamera(RCG_CamNumType _CamType);

	void SetEnginePipe();

protected:
	void Start() override {}

private:

};

