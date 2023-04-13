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

	//인덱스 크기에 따른 버전 관리
	switch (IndexSize)
	{
		//인덱스 하나가 short버전
	case 2:
		Format = DXGI_FORMAT_R16_UINT;
		break;
		//인덱스 하나가 int인 버전
	case 4:
		Format = DXGI_FORMAT_R32_UINT;
		break;
	}

	IndexCount = _IndexCount;

	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	//인덱스버퍼용 버퍼
	BufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//크기 명시
	BufferInfo.ByteWidth = IndexSize * IndexCount;

	//인덱스버퍼가 GPU에 있을때 딱히 수정할 일이 없기 때문에 D3D11_USAGE_DEFAULT로 설정
	BufferInfo.CPUAccessFlags = 0;
	if (0 == BufferInfo.CPUAccessFlags)
	{
		BufferInfo.Usage = D3D11_USAGE_DEFAULT;
	}
	else 
	{
		BufferInfo.Usage = D3D11_USAGE_DYNAMIC;
	}

	//디바이스를 통해 실제 버퍼 만들기
	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer))
	{
		MsgAssert("인덱스 버퍼 생성에 실패했습니다");
	}
}

void GameEngineIndexBuffer::Setting()
{
	if (nullptr == Buffer)
	{
		MsgAssert("ID3DBuffer가 만들어지지 않은 버텍스 버퍼 입니다.");
		return;
	}

	//인덱스 버퍼를 GPU에 보내기
	GameEngineDevice::GetContext()->IASetIndexBuffer(Buffer, Format, Offset);
}
