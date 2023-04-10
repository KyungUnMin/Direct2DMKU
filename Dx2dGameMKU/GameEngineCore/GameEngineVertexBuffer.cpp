#include "PrecompileHeader.h"
#include "GameEngineVertexBuffer.h"

GameEngineVertexBuffer::GameEngineVertexBuffer()
{

}

GameEngineVertexBuffer::~GameEngineVertexBuffer()
{

}

void GameEngineVertexBuffer::Create(const void* _Data, UINT _VertexSize, UINT _VertexCount)
{
	/*
		GPU�� � �ڷ����� �����ϴ����� ���ؼ��� ���ɾ���.
		������ ������ ��ġ�� void�����ͷ� �ް�, ������ ũ�⸸ �Ű澲�� �ȴ�
	*/

	VertexSize = _VertexSize;
	VertexCount = _VertexCount;

	//Direct���� �䱸�ϴ� void������
	D3D11_SUBRESOURCE_DATA Data;

	//�����͸� ���۽�ų ���� ��ġ
	Data.pSysMem = _Data;

	//������ ���ó(���ؽ� ���ۿ� ����)
	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	//������ ������ ũ��
	BufferInfo.ByteWidth = (VertexSize * VertexCount);

	
	//D3D11_CPU_ACCESS_WRITE
		//	CPU�� GPU�� �ִ� ������ ���� ����
	//	D3D11_CPU_ACCESS_READ
		//	CPU�� GPU�� �ִ� ������ ���� ���� ����
		
	//CPU ���� ����(����� ���� �Ұ���)
	BufferInfo.CPUAccessFlags = 0;


	// �����͸� ��� �δ� ���� ���� ���� 
	//	D3D11_USAGE_DEFAULT : GPU, cpu���� ���ٸ���.
	//	D3D11_USAGE_IMMUTABLE : 	GPU������ ���� �� ����. CPU���� ���� �׼����� �� ����.
	//	D3D11_USAGE_DYNAMIC : GPU(�б� ����)�� CPU(���� ����)���� ��� �׼��� ����
	//	D3D11_USAGE_STAGING : GPU���� CPU���� ������ ����(����)�� �����ϴ� (��Ʈ���ο� ���)
	if (0 == BufferInfo.CPUAccessFlags)
	{
		BufferInfo.Usage = D3D11_USAGE_DEFAULT;
	}
	else
	{
		BufferInfo.Usage = D3D11_USAGE_DYNAMIC;
	}


	//���ҽ��� �����ϴ� ���̱� ������ ����̽��� �̿�
	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer))
	{
		MsgAssert("���ؽ� ���� ������ �����߽��ϴ�.");
	}
}
