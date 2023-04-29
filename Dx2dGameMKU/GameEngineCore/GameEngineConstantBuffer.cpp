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

void GameEngineConstantBuffer::ChangeData(const void* _Data, UINT _Size)
{
	if (nullptr == _Data)
	{
		std::string Name = GetName().data();
		MsgAssert(Name + "�� nullptr�� �����͸� �����Ϸ��� �߽��ϴ�");
		return;
	}

	if (BufferInfo.ByteWidth != _Size)
	{
		std::string Name = GetName().data();
		MsgAssert(Name + " : ũ�Ⱑ �ٸ� �����Ͱ� ���Խ��ϴ�");
		return;
	}

	D3D11_MAPPED_SUBRESOURCE SettingResource = { 0, };

	//GPU �� �ִ� ������۸� �����ϱ� ���� ��� GPU�� �ߴܽ�Ű�� �Լ�, �� �������� ���� ������ �� �ִ� �����͸� �ش�
	GameEngineDevice::GetContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SettingResource);

	if (SettingResource.pData == nullptr)
	{
		std::string Name = GetName().data();
		MsgAssert(Name + " �׷���ī�忡�� �޸� ������ �㰡���� ���߽��ϴ�.");
		return;
	}

	//�޸� ī��(A <- B)
	memcpy_s(SettingResource.pData, BufferInfo.ByteWidth, _Data, BufferInfo.ByteWidth);

	//������ �������� �˸�
	GameEngineDevice::GetContext()->Unmap(Buffer, 0);
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


void GameEngineConstantBuffer::VSSetting(UINT _Slot)
{
	//Slot : b0, t0 ���� ����
	GameEngineDevice::GetContext()->VSSetConstantBuffers(_Slot, 1, &Buffer);
}

void GameEngineConstantBuffer::PSSetting(UINT _Slot)
{
	//Slot : b0, t0 ���� ����
	GameEngineDevice::GetContext()->PSSetConstantBuffers(_Slot, 1, &Buffer);
}