#include "PrecompileHeader.h"
#include "GameEngineTexture.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\x64\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\x64\\Release\\DirectXTex.lib")
#endif


GameEngineTexture::GameEngineTexture()
{

}

GameEngineTexture::~GameEngineTexture()
{
	if (nullptr != DSV)
	{
		DSV->Release();
		DSV = nullptr;
	}
	
	if (nullptr != SRV)
	{
		SRV->Release();
		SRV = nullptr;
	}

	if (nullptr != RTV)
	{
		RTV->Release();
		RTV = nullptr;
	}

	if (nullptr != Texture2D)
	{
		Texture2D->Release();
		Texture2D = nullptr;
	}
}



void GameEngineTexture::ResCreate(ID3D11Texture2D* _Value)
{
	Texture2D = _Value;

	//만들어낸 메인화면 텍스처의 정보를 받아온다
	Texture2D->GetDesc(&Desc);

	//받은 텍스처를 바탕으로 렌더타겟을 생성
	CreateRenderTargetView();
}


void GameEngineTexture::CreateRenderTargetView()
{
	if (nullptr == Texture2D)
	{
		MsgAssert("텍스처가 존재하지 않는 랜더타겟뷰를 만들 수는 없습니다.");
		return;
	}

	//디바이스를 이용해 텍스처에 따른 실제 렌더타겟을 만든다
	HRESULT Result = GameEngineDevice::GetDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Result)
	{
		MsgAssert("렌더타겟 뷰 생성에 실패하였습니다");
		return;
	}
}



void GameEngineTexture::CreateDepthStencilView()
{
	if (nullptr == Texture2D)
	{
		MsgAssert("텍스처가 존재하지 않는데 뎁스 스텐실 뷰를 만들수는 없습니다");
		return;
	}

	HRESULT Result = GameEngineDevice::GetDevice()->CreateDepthStencilView(Texture2D, nullptr, &DSV);
	if (S_OK != Result)
	{
		MsgAssert("뎁스 스텐실 뷰 생성에 실패했습니다");
		return;
	}
}







void GameEngineTexture::ResLoad(const std::string_view& _Path)
{
	GameEnginePath NewPath(_Path);

	//확장자(대문자)
	std::string Ext = GameEngineString::ToUpper(NewPath.GetExtension());
	
	//유니코드 풀 패스
	std::wstring Path = GameEngineString::AnsiToUniCode(NewPath.GetFullPath());

	if (Ext == ".TGA")
	{
		MsgAssert("아직 로드할 수 없는 포맷입니다." + std::string(_Path.data()));
	}
	else if (Ext == ".DDS")
	{
		MsgAssert("아직 로드할 수 없는 포맷입니다." + std::string(_Path.data()));
	}

	//리소스 로드
	else if (S_OK != DirectX::LoadFromWICFile(Path.c_str(), DirectX::WIC_FLAGS_NONE, &Data, Image))
	{
		MsgAssert("텍스처 로드에 실패했습니다." + std::string(_Path.data()));
	}

	//로드한 리소스를 바탕으로 SRV(쉐이더 리소스 뷰)만들기
	if (S_OK != DirectX::CreateShaderResourceView
	(
		GameEngineDevice::GetDevice(),
		Image.GetImages(),			
		Image.GetImageCount(),	
		Image.GetMetadata(),			//바이너리 코드 같은거
		&SRV
	))
	{
		MsgAssert("쉐이더 리소스 뷰 생성에 실패했습니다." + std::string(_Path.data()));
	}


	Desc.Width = static_cast<UINT>(Data.width);
	Desc.Height= static_cast<UINT>(Data.height);
}




void GameEngineTexture::VSSetting(UINT _Slot)
{
	GameEngineDevice::GetContext()->VSSetShaderResources(_Slot, 1, &SRV);
}

void GameEngineTexture::PSSetting(UINT _Slot)
{
	GameEngineDevice::GetContext()->PSSetShaderResources(_Slot, 1, &SRV);
}




void GameEngineTexture::ResCreate(const D3D11_TEXTURE2D_DESC& _Value)
{
	Desc = _Value;

	GameEngineDevice::GetDevice()->CreateTexture2D(&Desc, nullptr, &Texture2D);

	//깊이 버퍼용으로 만든 텍스처였다면
	if (D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL == Desc.BindFlags)
	{
		CreateDepthStencilView();
	}

	if (nullptr == Texture2D)
	{
		MsgAssert("텍스처 생성에 실패했습니다");
	}
}