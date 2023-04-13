#include "PrecompileHeader.h"
#include "GameEngineVertex.h"

GameEngineInputLayOut GameEngineVertex::LayOut;

void GameEngineInputLayOut::AddInputLayOut(
	LPCSTR _SemanticName, 
	DXGI_FORMAT _Format, 
	D3D11_INPUT_CLASSIFICATION _InputSlotClass, 
	UINT _InstanceDataStepRate, 
	UINT _AlignedByteOffset, 
	UINT _InputSlot, 
	UINT _SemanticIndex)
{
	D3D11_INPUT_ELEMENT_DESC Data;

	// 시맨틱의 자료형 명시
	Data.SemanticName = _SemanticName;

	//TODO

	Descs.push_back(Data);
}
