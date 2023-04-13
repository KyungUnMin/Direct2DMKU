#pragma once
#include "GameEngineResource.h"
#include "GameEngineDirectBuffer.h"

//���ؽ��� �׸��� ������ ���
class GameEngineIndexBuffer : public GameEngineResource<GameEngineIndexBuffer>, public GameEngineDirectBuffer
{
public:
	GameEngineIndexBuffer();
	~GameEngineIndexBuffer() override;

	GameEngineIndexBuffer(const GameEngineIndexBuffer& _Other) = delete;
	GameEngineIndexBuffer(GameEngineIndexBuffer&& _Other) noexcept = delete;
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer& _Other) = delete;
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer&& _Other) noexcept = delete;

	//GameEngineIndexBuffer ���ҽ� ����
	template <typename IndexType>
	static void Create(const std::string_view& _Name, const std::vector<IndexType>& _Vertexs)
	{
		std::shared_ptr<GameEngineIndexBuffer> Res = GameEngineResource::Create(_Name);
		Res->Create(&_Vertexs[0], sizeof(IndexType), static_cast<UINT>(_Vertexs.size()));
	}

	void Setting() override;

protected:

private:
	DXGI_FORMAT Format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;

	UINT Offset = 0;
	UINT IndexSize = 0;
	UINT IndexCount = 0;
	UINT VertexCount = 0;

	//������ ������ �������� ���� �ε��� ���� �����
	void Create(const void* _Data, UINT _IndexSize, UINT _IndexCount);
};

