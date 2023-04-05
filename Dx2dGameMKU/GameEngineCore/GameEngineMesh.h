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

	//Core���� �� �Լ��� ȣ���Ű�Ƿν�
	//������� ���ҽ���
	//static Resources �ڷᱸ���� Mesh���� �����ϰ� ��
	//(�̸��� Ű���� Map or List)
	static void Create(const std::string_view& _Name, const std::vector<float4>& _Vertexs)
	{
		std::shared_ptr<GameEngineMesh> NewMesh = GameEngineResource::Create(_Name);
		//TODO
	}

protected:

private:
	std::vector<float4> Vertexs;
};

