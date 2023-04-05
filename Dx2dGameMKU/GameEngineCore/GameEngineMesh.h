#pragma once
#include "GameEngineResource.h"
#include <vector>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineMesh : public GameEngineResource<GameEngineMesh>
{
public:
	GameEngineMesh();
	~GameEngineMesh() override;

	GameEngineMesh(const GameEngineMesh& _Other) = delete;
	GameEngineMesh(GameEngineMesh&& _Other) noexcept = delete;
	GameEngineMesh& operator=(const GameEngineMesh& _Other) = delete;
	GameEngineMesh& operator=(const GameEngineMesh&& _Other) noexcept = delete;

	//Core에서 이 함수를 호출시키므로써
	//만들려는 리소스를
	//static Resources 자료구조에 Mesh별로 저장하게 됨
	//(이름이 키값인 Map or List)
	static void Create(const std::string_view& _Name, const std::vector<float4>& _Vertexs)
	{
		std::shared_ptr<GameEngineMesh> NewMesh = GameEngineResource::Create(_Name);
		//TODO
	}

protected:

private:
	std::vector<float4> Vertexs;
};

