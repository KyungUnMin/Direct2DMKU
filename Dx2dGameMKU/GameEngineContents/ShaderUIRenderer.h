#pragma once
#include <GameEngineCore/GameEngineUIRenderer.h>

class ShaderUIRenderer : public GameEngineUIRenderer
{
public:
	ShaderUIRenderer();
	~ShaderUIRenderer() override;

	ShaderUIRenderer(const ShaderUIRenderer& _Other) = delete;
	ShaderUIRenderer(ShaderUIRenderer&& _Other) noexcept = delete;
	ShaderUIRenderer& operator=(const ShaderUIRenderer& _Other) = delete;
	ShaderUIRenderer& operator=(const ShaderUIRenderer&& _Other) noexcept = delete;


protected:
	void Start() override;

private:

};

