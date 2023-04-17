#pragma once
#include "GameEngineComponent.h"
#include "GameEngineShader.h"

class GameEngineRenderer : public GameEngineComponent
{
public:
	GameEngineRenderer();
	~GameEngineRenderer() override;

	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer&& _Other) noexcept = delete;

	//(드로우(그리기) 하기 직전에 쉐이더 파일에 값을 넣어주는 것 같다)
	//파이프라인을 세팅하면서, 쉐이더 과정들의 헬터들을 한곳에 모은다
	void SetPipeLine(const std::string_view& _Name);

protected:
	void Render(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineRenderingPipeLine> Pipe;

	//쉐이더들의 상수버퍼, 텍스처 등의 정보를 집약시킨 값
	GameEngineShaderResHelper ShaderResHelper;
};

