#pragma once
#include <GameEngineBase/GameEngineMath.h>

//쉐이더 파일이 시맨틱 문법을 사용하기 위해 명시해야 하는 정보를 담은 클래스
class GameEngineInputLayOut
{
private:
	std::vector<D3D11_INPUT_ELEMENT_DESC> Descs;

public:
	void AddInputLayOut(
		LPCSTR _SemanticName,					// 시맨틱의 어떤 자료형인지 명시(POSITION or COLOR...)
		DXGI_FORMAT _Format,					// 자료형의 크기
		D3D11_INPUT_CLASSIFICATION _InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA, // 버텍스 데이터가 인스턴싱 데이터임을 의미
		UINT _InstanceDataStepRate = 0, // 인스턴싱이라는 구조를 배울때 쓴다.
		UINT _AlignedByteOffset = -1,		// 0번째 바이트부터 
		UINT _InputSlot = 0,						// n개의 버텍스 버퍼를 세팅할때 n번째 버텍스 버퍼의 인풋 레이아웃임을 표현
		UINT _SemanticIndex = 0
	);
};


class GameEngineVertex
{
public:
	static GameEngineInputLayOut LayOut;

public:
	//위치값
	float4 POSITION;
	//색상 정보
	float4 COLOR;

	//TODO...
};


