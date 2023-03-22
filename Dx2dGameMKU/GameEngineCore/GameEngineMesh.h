#pragma once
#include <vector>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineResource.h"

class GameEngineMesh : public GameEngineResource
{
public:
	GameEngineMesh();
	~GameEngineMesh();

	GameEngineMesh(const GameEngineMesh& _Other) = delete;
	GameEngineMesh(GameEngineMesh&& _Other) noexcept = delete;
	GameEngineMesh& operator=(const GameEngineMesh& _Other) = delete;
	GameEngineMesh& operator=(const GameEngineMesh&& _Other) noexcept = delete;

protected:

private:
	std::vector<float4> Vertexs;
};

