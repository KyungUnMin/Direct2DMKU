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
		GPU는 어떤 자료형을 수정하는지에 대해서는 관심없다.
		때문에 수정할 위치를 void포인터로 받고, 수정할 크기만 신경쓰면 된다
	*/

	VertexSize = _VertexSize;
	VertexCount = _VertexCount;

	//Direct에서 요구하는 void포인터
	D3D11_SUBRESOURCE_DATA Data;

	//데이터를 전송시킬 시작 위치
	Data.pSysMem = _Data;

	//버퍼의 사용처(버텍스 버퍼용 버퍼)
	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	//전송할 데이터 크기
	BufferInfo.ByteWidth = (VertexSize * VertexCount);

	
	//D3D11_CPU_ACCESS_WRITE
		//	CPU가 GPU에 있는 내용을 변경 가능
	//	D3D11_CPU_ACCESS_READ
		//	CPU가 GPU에 있는 내용을 읽을 수만 있음
		
	//CPU 접근 여부(현재는 수정 불가능)
	BufferInfo.CPUAccessFlags = 0;


	// 데이터를 어디에 두는 지에 대한 정보 
	//	D3D11_USAGE_DEFAULT : GPU, cpu에서 접근못함.
	//	D3D11_USAGE_IMMUTABLE : 	GPU에서만 읽을 수 있음. CPU에서 전혀 액세스할 수 없음.
	//	D3D11_USAGE_DYNAMIC : GPU(읽기 전용)와 CPU(쓰기 전용)에서 모두 액세스 가능
	//	D3D11_USAGE_STAGING : GPU에서 CPU로의 데이터 전송(복사)만 지원하는 (비트코인에 사용)
	if (0 == BufferInfo.CPUAccessFlags)
	{
		BufferInfo.Usage = D3D11_USAGE_DEFAULT;
	}
	else
	{
		BufferInfo.Usage = D3D11_USAGE_DYNAMIC;
	}


	//리소스를 생성하는 것이기 때문에 디바이스를 이용
	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer))
	{
		MsgAssert("버텍스 버퍼 생성에 실패했습니다.");
	}
}
