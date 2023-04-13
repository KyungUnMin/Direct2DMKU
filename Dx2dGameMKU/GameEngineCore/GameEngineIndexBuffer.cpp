#include "PrecompileHeader.h"
#include "GameEngineIndexBuffer.h"

GameEngineIndexBuffer::GameEngineIndexBuffer()
{

}

GameEngineIndexBuffer::~GameEngineIndexBuffer()
{

}


void GameEngineIndexBuffer::Create(const void* _Data, UINT _IndexSize, UINT _IndexCount)
{
	IndexSize = _IndexSize;

	//�ε��� ũ�⿡ ���� ���� ����
	switch (IndexSize)
	{
		//�ε��� �ϳ��� short����
	case 2:
		Format = DXGI_FORMAT_R16_UINT;
		break;
		//�ε��� �ϳ��� int�� ����
	case 4:
		Format = DXGI_FORMAT_R32_UINT;
		break;
	}

	IndexCount = _IndexCount;

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	//�ε������ۿ� ����
	BufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//ũ�� ���
	BufferInfo.ByteWidth = IndexSize * IndexCount;

	//�ε������۰� GPU�� ������ ���� ������ ���� ���� ������ D3D11_USAGE_DEFAULT�� ����
	BufferInfo.CPUAccessFlags = 0;
	if (0 == BufferInfo.CPUAccessFlags)
	{
		BufferInfo.Usage = D3D11_USAGE_DEFAULT;
	}
	else 
	{
		BufferInfo.Usage = D3D11_USAGE_DYNAMIC;
	}

	//����̽��� ���� ���� ���� �����
	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer))
	{
		MsgAssert("�ε��� ���� ������ �����߽��ϴ�");
	}
}

void GameEngineIndexBuffer::Setting()
{
	if (nullptr == Buffer)
	{
		MsgAssert("ID3DBuffer�� ��������� ���� ���ؽ� ���� �Դϴ�.");
		return;
	}

	//�ε��� ���۸� GPU�� ������
	GameEngineDevice::GetContext()->IASetIndexBuffer(Buffer, Format, Offset);
}
