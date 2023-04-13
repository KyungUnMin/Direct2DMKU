#pragma once
#include "GameEngineResource.h"
#include "GameEngineDirectBuffer.h"

/*
	������ ������������
	Input Assembler1 �ܰ迡 ���Ǵ�
	���ҽ� Ŭ����

	Input Assembler1 �ܰ�� ��(���ؽ�)�� ���� ������ �ʿ��ϴ�
		�̶� �� �ȿ� ��ġ�� ���� ���� �Բ� �� �־�� �Ѵ�
		�װ��� ǥ���ϱ� ���� ���ؽ� ���ۿ�
		�ν��Ͻ� ����(�ε��� ����)�� �ʿ��ϴ�

		���ؽ� ���۴� ���� ���� ������ �ǹ��ϸ�
		�ν��Ͻ� ���۴� ���� �׸��� ������ �ǹ��Ѵ�
		�� Ŭ������ �� �� ���ؽ� ���۸� �ǹ��Ѵ�

		���ؽ� ���۴� CPU�� �ִ� ������
		GPU�� �������ν� ���������.
		������ GPU���� ������ �̵��� �ʿ��ϰ� 
		�̶� ���۵� �ʿ��ϱ� ������ ��� ���ۿ� ���������� ���Ǵ�
		GameEngineResource�� ��ӽ��״�.
*/


class GameEngineVertexBuffer : public GameEngineResource<GameEngineVertexBuffer>, public GameEngineDirectBuffer
{
public:
	GameEngineVertexBuffer();
	~GameEngineVertexBuffer() override;

	GameEngineVertexBuffer(const GameEngineVertexBuffer& _Other) = delete;
	GameEngineVertexBuffer(GameEngineVertexBuffer&& _Other) noexcept = delete;
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer& _Other) = delete;
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer&& _Other) noexcept = delete;

	//�� ���ø����� ������?, ���߿� GameEngineVertex���� �ٸ��͵� ���ؽ� ���۷� ����?
	template <typename VertexType>
	static void Create(const std::string_view& _Name, const std::vector<VertexType>& _Vertexs)
	{
		std::shared_ptr<GameEngineVertexBuffer> Res = GameEngineResource::Create(_Name);
		Res->Create(&_Vertexs[0], sizeof(VertexType), static_cast<UINT>(_Vertexs.size()));
	}

	//����� ����(ID3DBuffer)�� GPU�� �ѱ��(������ ����������_��ǲ�����1 �ܰ�)
	void Setting() override;

protected:

private:
	void Create(const void* _Data, UINT _VertexSize, UINT _VertexCount);

	UINT Offset = 0;
	UINT VertexSize = 0;
	UINT VertexCount= 0;
};

