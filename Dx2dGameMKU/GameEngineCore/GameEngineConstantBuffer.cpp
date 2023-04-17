#include "PrecompileHeader.h"
#include "GameEngineConstantBuffer.h"

std::map<int, std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>> GameEngineConstantBuffer::ConstantBufferRes;

GameEngineConstantBuffer::GameEngineConstantBuffer()
{

}

GameEngineConstantBuffer::~GameEngineConstantBuffer()
{

}

void GameEngineConstantBuffer::ResourcesClear()
{
	//�θ����� ���ҽ� ����
	GameEngineResource<GameEngineConstantBuffer>::ResourcesClear();

	//�ڱ� �ڽ����� ���ҽ� ����
	ConstantBufferRes.clear();
}

void GameEngineConstantBuffer::ResCreate(const D3D11_SHADER_BUFFER_DESC& _BufferDesc)
{
	//��� �������� ǥ��
	BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//���� ũ��
	BufferInfo.ByteWidth = _BufferDesc.Size;
	
	//������۴� GPU�� �ִ� ���̴� ���Ͽ� ���� �����ϴ� ���̱� ������ Write�����̴�.
	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	if (0 == BufferInfo.CPUAccessFlags)
	{
		BufferInfo.Usage = D3D11_USAGE_DEFAULT;
	}
	else 
	{
		BufferInfo.Usage = D3D11_USAGE_DYNAMIC;
	}


	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferInfo, nullptr, &Buffer))
	{
		MsgAssert("��� ���� ������ �����߽��ϴ�");
	}
}
