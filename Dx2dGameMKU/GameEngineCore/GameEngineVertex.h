#pragma once
#include <GameEngineBase/GameEngineMath.h>

//쉐이더 파일이 시맨틱 문법을 사용하기 위해 명시해야 하는 정보를 담은 클래스
class GameEngineInputLayOutInfo
{
public:
	static UINT FormatSize(DXGI_FORMAT _Format);

	inline const std::vector<D3D11_INPUT_ELEMENT_DESC>& GetDescs()
	{
		return Descs;
	}

private:
	std::vector<D3D11_INPUT_ELEMENT_DESC> Descs;
	int Offset = 0;

public:
	void AddInputLayOut(
		LPCSTR _SemanticName,					// 시맨틱의 어떤 자료형인지 명시(POSITION or COLOR...)
		DXGI_FORMAT _Format,					// 자료형의 크기
		D3D11_INPUT_CLASSIFICATION _InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA, // 버텍스 데이터가 인스턴싱 데이터임을 의미
		UINT _InstanceDataStepRate = 0, // 인스턴싱이라는 구조를 배울때 쓴다.
		UINT _AlignedByteOffset = -1,		// 0번째 바이트부터 
		UINT _InputSlot = 0,						// n개의 버텍스 버퍼를 세팅할때 n번째 버텍스 버퍼의 인풋 레이아웃임을 표현
		UINT _SemanticIndex = 0				//시맨틱 정보를 여러개 넣어줄 수 있는데 이 구조에서는 무조건 하나로 고정
	);
};


class GameEngineVertex
{
public:
	//내가 착각하고 있는데, 레이아웃 정보는 버텍스마다 다 다르다
	//GameEngineInputLayOutInfo를 각각의 버텍스에서 static으로 들고 있을뿐임
	static GameEngineInputLayOutInfo LayOut;

public:
	//이 버텍스의 정보가 쉐이더 파일로 이동하게 될 텐데,
	//그 때 시맨틱 문법(쉐이더 파일 Input구조체)과 순서는 달라도 이름은 똑같아야 한다, 가능하면 순서도 같게 하자
	float4 POSITION;
	float4 UV;

	//TODO...
};

/*
텍스처를 픽셀에 그릴때
	메쉬와 텍스터 모두
	xy모두 왼쪽 상단을 0 좌측 하단을 1로 생각한다

	이를 UV좌표계라고 한다
	예를 들어 (0.75, 0.75)의 해당 메쉬의 픽셀 색상은
	텍스터의 (0.75, 0.75)의 값으로 색칠한다

	이러한 픽셀 쉐이더의 계산방식을 
	도와주는 것을 샘플러라고 한다

	(참고로 픽셀 쉐이더는 자동으로 선형보간 된다)
*/
