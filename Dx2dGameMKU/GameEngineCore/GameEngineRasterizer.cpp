#include "PrecompileHeader.h"
#include "GameEngineRasterizer.h"

GameEngineRasterizer::GameEngineRasterizer()
{

}

GameEngineRasterizer::~GameEngineRasterizer()
{
	Release();
}

void GameEngineRasterizer::Setting()
{
	if (nullptr == CurState)
	{
		MsgAssert("생성되지 않은 래스터라이저 스테이트 입니다");
		return;
	}

	GameEngineDevice::GetContext()->RSSetState(CurState);
}



void GameEngineRasterizer::Release()
{
	if (nullptr != SolidState)
	{
		SolidState->Release();
		SolidState = nullptr;
	}

	if (nullptr != WireframeState)
	{
		WireframeState->Release();
		WireframeState = nullptr;
	}
}


void GameEngineRasterizer::ResCreate(const D3D11_RASTERIZER_DESC& _Value)
{
	//Fill이나 Cull 변경할때를 위한 이전 State 날리기
	Release();

	//기안서 받기
	Desc = _Value;

	//와이어 프레임 래스터라이저 만들기
	Desc.FillMode = D3D11_FILL_WIREFRAME;
	if (S_OK != GameEngineDevice::GetDevice()->CreateRasterizerState(&Desc, &WireframeState))
	{
		MsgAssert("와이어 프레임 레스터라이저 스테이트 생성에 실패했습니다.");
	}

	//솔리드 프레임 래스터라이저 만들기
	Desc.FillMode = D3D11_FILL_SOLID;
	if (S_OK != GameEngineDevice::GetDevice()->CreateRasterizerState(&Desc, &SolidState))
	{
		MsgAssert("솔리드 레스터라이저 스테이트 생성에 실패했습니다.");
	}

	//기본은 솔리드로 하기
	SetFILL_MODE(D3D11_FILL_SOLID);
}
