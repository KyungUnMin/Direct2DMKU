#pragma once
#include "GameEngineResource.h"
#include "GameEngineDirectBuffer.h"

//버텍스를 그리는 순서를 담당
class GameEngineIndexBuffer : public GameEngineResource<GameEngineIndexBuffer>, public GameEngineDirectBuffer
{
public:
	GameEngineIndexBuffer();
	~GameEngineIndexBuffer() override;

	GameEngineIndexBuffer(const GameEngineIndexBuffer& _Other) = delete;
	GameEngineIndexBuffer(GameEngineIndexBuffer&& _Other) noexcept = delete;
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer& _Other) = delete;
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer&& _Other) noexcept = delete;

	//GameEngineIndexBuffer 리소스 생성
	template <typename IndexType>
	static void Create(const std::string_view& _Name, const std::vector<IndexType>& _Vertexs)
	{
		std::shared_ptr<GameEngineIndexBuffer> Res = GameEngineResource::Create(_Name);
		Res->ResCreate(&_Vertexs[0], sizeof(IndexType), static_cast<UINT>(_Vertexs.size()));
	}

	//버텍스를 그리는 순서(인덱스 버퍼)를 GPU에 넘긴다(세팅한다)
	void Setting() override;

	inline UINT GetIndexCount()
	{
		return IndexCount;
	}

protected:

private:
	DXGI_FORMAT Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;

	UINT Offset = 0;
	UINT IndexSize = 0;
	UINT IndexCount = 0;
	UINT VertexCount = 0;

	//인자의 정보를 바탕으로 실제 인덱스 버퍼 만들기
	void ResCreate(const void* _Data, UINT _IndexSize, UINT _IndexCount);
};

