#pragma once
#include "GameEngineResource.h"
#include "GameEngineVertex.h"
#include "GameEngineDirectBuffer.h"

/*
	렌더링 파이프라인의
	Input Assembler1 단계에 사용되는
	리소스 클래스

	Input Assembler1 단계는 점(버텍스)에 대한 정보가 필요하다
		이때 점 안에 위치와 색상 등이 함께 들어가 있어야 한다
		그것을 표현하기 위해 버텍스 버퍼와
		인스턴스 버퍼(인덱스 버퍼)가 필요하다

		버텍스 버퍼는 점에 대한 정보를 의미하며
		인스턴스 버퍼는 점을 그리는 순서를 의미한다
		이 클래스는 그 중 버텍스 버퍼를 의미한다

		버텍스 버퍼는 CPU에 있던 정보를
		GPU에 넣음으로써 만들어진다.
		때문에 GPU와의 데이터 이동이 필요하고 
		이때 버퍼도 필요하기 때문에 모든 버퍼에 범용적으로 사용되는
		GameEngineResource를 상속시켰다.
*/


class GameEngineVertexBuffer : public GameEngineResource<GameEngineVertexBuffer>, public GameEngineDirectBuffer
{
	friend class GameEngineInputLayOut;

public:
	GameEngineVertexBuffer();
	~GameEngineVertexBuffer() override;

	GameEngineVertexBuffer(const GameEngineVertexBuffer& _Other) = delete;
	GameEngineVertexBuffer(GameEngineVertexBuffer&& _Other) noexcept = delete;
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer& _Other) = delete;
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer&& _Other) noexcept = delete;

	template <typename VertexType>
	static void Create(const std::string_view& _Name, const std::vector<VertexType>& _Vertexs)
	{
		std::shared_ptr<GameEngineVertexBuffer> Res = GameEngineResource::Create(_Name);
		
		//버텍스에 있는 버텍스 레이아웃 정보(버텍스 쉐이더에서 시맨틱 문법을 GPU가 이해하기 위한 정보)를 받아온다
		//이것처럼 템플릿도 추상함수처럼 함수를 강제시킬수 있다.
		//모든 버텍스들은 내부에 static으로 GameEngineInputLayOutInfo를 들고 있어야 한다
		Res->LayOutInfo = &VertexType::LayOut;
		Res->ResCreate(&_Vertexs[0], sizeof(VertexType), static_cast<UINT>(_Vertexs.size()));
	}

	//기록한 버퍼(ID3DBuffer)를 GPU에 넘긴다(렌더링 파이프라인_인풋어셈블러1 단계)
	void Setting() override;

protected:

private:
	GameEngineInputLayOutInfo* LayOutInfo = nullptr;

	void ResCreate(const void* _Data, UINT _VertexSize, UINT _VertexCount);

	UINT Offset = 0;
	UINT VertexSize = 0;
	UINT VertexCount= 0;
};

