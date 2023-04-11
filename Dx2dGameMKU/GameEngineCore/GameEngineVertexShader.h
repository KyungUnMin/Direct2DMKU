#pragma once
#include "GameEngineResource.h"
#include "GameEngineShader.h"

class GameEngineVertexShader : public GameEngineResource<GameEngineVertexShader>, public GameEngineShader
{
public:
	GameEngineVertexShader();
	~GameEngineVertexShader() override;

	GameEngineVertexShader(const GameEngineVertexShader& _Other) = delete;
	GameEngineVertexShader(GameEngineVertexShader&& _Other) noexcept = delete;
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _Other) = delete;
	GameEngineVertexShader& operator=(const GameEngineVertexShader&& _Other) noexcept = delete;

protected:

private:

};

