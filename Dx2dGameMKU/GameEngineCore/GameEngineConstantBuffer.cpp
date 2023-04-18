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
	//부모쪽의 리소스 정리
	GameEngineResource<GameEngineConstantBuffer>::ResourcesClear();

	//자기 자신쪽의 리소스 정리
	ConstantBufferRes.clear();
}

void GameEngineConstantBuffer::ChangeData(const void* _Data, UINT _Size)
{
	if (nullptr == _Data)
	{
		std::string Name = GetName().data();
		MsgAssert(Name + "에 nullptr인 데이터를 세팅하려고 했습니다");
		return;
	}

	if (BufferInfo.ByteWidth != _Size)
	{
		std::string Name = GetName().data();
		MsgAssert(Name + " : 크기가 다른 데이터가 들어왔습니다");
		return;
	}

	D3D11_MAPPED_SUBRESOURCE SettingResource = { 0, };

	//GPU 에 있는 상수버퍼를 수정하기 위해 잠시 GPU를 중단시키는 함수, 그 과정에서 값을 수정할 수 있는 포인터를 준다
	GameEngineDevice::GetContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SettingResource);

	if (SettingResource.pData == nullptr)
	{
		std::string Name = GetName().data();
		MsgAssert(Name + " 그래픽카드에게 메모리 접근을 허가받지 못했습니다.");
		return;
	}

	//메모리 카피(A <- B)
	memcpy_s(SettingResource.pData, BufferInfo.ByteWidth, _Data, BufferInfo.ByteWidth);

	//수정이 끝났음을 알림
	GameEngineDevice::GetContext()->Unmap(Buffer, 0);
}



void GameEngineConstantBuffer::ResCreate(const D3D11_SHADER_BUFFER_DESC& _BufferDesc)
{
	//상수 버퍼임을 표시
	BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//버퍼 크기
	BufferInfo.ByteWidth = _BufferDesc.Size;
	
	//상수버퍼는 GPU에 있는 쉐이더 파일에 값을 대입하는 것이기 때문에 Write형식이다.
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
		MsgAssert("상수 버퍼 생성에 실패했습니다");
	}
}


void GameEngineConstantBuffer::VSSetting(UINT _Slot)
{
	//Slot : b0, t0 같은 슬롯
	GameEngineDevice::GetContext()->VSSetConstantBuffers(_Slot, 1, &Buffer);
}

void GameEngineConstantBuffer::PSSetting(UINT _Slot)
{
	//Slot : b0, t0 같은 슬롯
	GameEngineDevice::GetContext()->PSSetConstantBuffers(_Slot, 1, &Buffer);
}
