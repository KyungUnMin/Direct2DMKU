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
