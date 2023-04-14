#include "PrecompileHeader.h"
#include "GameEngineInputLayOut.h"
#include "GameEngineVertex.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"

GameEngineInputLayOut::GameEngineInputLayOut()
{

}

GameEngineInputLayOut::~GameEngineInputLayOut()
{
	Release();
}

void GameEngineInputLayOut::Release()
{
	if (nullptr != InputLayOut)
	{
		InputLayOut->Release();
		InputLayOut = nullptr;
	}
}

void GameEngineInputLayOut::ResCreate(std::shared_ptr<class GameEngineVertexBuffer> _Info, std::shared_ptr<class GameEngineVertexShader> _Shader)
{
	//버텍스 쉐이더 파일이 바뀔것을 대비해서
	//이미 만들어졌다면 지우고 다시 만들기
	Release();

	if (nullptr == _Info->LayOutInfo)
	{
		//참고로 모든 버텍스들은 인풋 레이아웃 정보를 가지고 있어야 하며
		//버텍스 버퍼를 생성할 때 해당 버텍스의 인풋레이아웃 정보를 가르키게 된다
		MsgAssert("레이아웃 정보를 만들수 없는 버텍스 버퍼입니다");
		return;
	}

	const std::vector<D3D11_INPUT_ELEMENT_DESC>& LayOutInfoes = _Info->LayOutInfo->GetDescs();

	HRESULT Result = GameEngineDevice::GetDevice()->CreateInputLayout(
		&LayOutInfoes[0],
		static_cast<UINT>(LayOutInfoes.size()),
		_Shader->BinaryCode->GetBufferPointer(),
		_Shader->BinaryCode->GetBufferSize(),
		&InputLayOut);

	if (S_OK != Result)
	{
		MsgAssert("인풋 레이아웃 생성에 실패했습니다");
		return;
	}
}

void GameEngineInputLayOut::Setting()
{
	if (nullptr == InputLayOut)
	{
		MsgAssert("생성되지 않은 인풋레이아웃을 세팅하려고 했습니다.");
	}

	GameEngineDevice::GetContext()->IASetInputLayout(InputLayOut);
}
