#pragma once
#include "GameEngineResource.h"

#include "GameEngineVertexBuffer.h"	//인풋 어셈블러1
#include "GameEngineIndexBuffer.h"	//인풋 어셈블러2

class GameEngineMesh : public GameEngineResource<GameEngineMesh>
{
	friend class GameEngineRenderUnit;

public:
	static std::shared_ptr<GameEngineMesh> Create(const std::string_view& _Name)
	{
		return Create(_Name, _Name, _Name);
	}

	//만들 메쉬 이름, 이미 생성된 버텍스버퍼일므, 이미 생성된 인덱스 버퍼 이름
	static std::shared_ptr<GameEngineMesh> Create(const std::string_view& _Name, const std::string_view _VtxName, const std::string_view _IdxName)
	{
		std::shared_ptr<GameEngineMesh> Res = GameEngineResource::Create(_Name);
		Res->VertexBufferPtr = GameEngineVertexBuffer::Find(_VtxName);
		Res->IndexBufferPtr = GameEngineIndexBuffer::Find(_IdxName);

		if ((nullptr == Res->VertexBufferPtr) || (nullptr == Res->IndexBufferPtr))
		{
			MsgAssert("매쉬를 만드는데 실패했습니다.");
		}

		return Res;
	}

	inline std::shared_ptr<GameEngineVertexBuffer> GetVertexBuffer() const
	{
		return VertexBufferPtr;
	}

	inline void SetTopology(D3D11_PRIMITIVE_TOPOLOGY _TOPOLOGY)
	{
		TOPOLOGY = _TOPOLOGY;
	}

	GameEngineMesh();
	~GameEngineMesh() override;

	GameEngineMesh(const GameEngineMesh& _Other) = delete;
	GameEngineMesh(GameEngineMesh&& _Other) noexcept = delete;
	GameEngineMesh& operator=(const GameEngineMesh& _Other) = delete;
	GameEngineMesh& operator=(const GameEngineMesh&& _Other) noexcept = delete;

	

protected:
	//렌더링 파이프라인을 통해 이 Setting함수로 호출되고 Setting은 아래의 인풋 어셈블러 과정을 수행한다
	void Setting() override;

	void InputAssembler1();
	void InputAssembler2();

private:
	D3D11_PRIMITIVE_TOPOLOGY TOPOLOGY = D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	std::shared_ptr<GameEngineVertexBuffer> VertexBufferPtr = nullptr;
	std::shared_ptr<GameEngineIndexBuffer> IndexBufferPtr = nullptr;
};

