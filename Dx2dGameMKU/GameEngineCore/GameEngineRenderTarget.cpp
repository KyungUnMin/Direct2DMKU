#include "PrecompileHeader.h"
#include "GameEngineRenderTarget.h"

GameEngineRenderTarget::GameEngineRenderTarget()
{

}

GameEngineRenderTarget::~GameEngineRenderTarget()
{
	DepthTexture = nullptr;
}



void GameEngineRenderTarget::ResCreate(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color)
{
	//텍스처의 경우엔 포인터를 두개로 나눠서
	//GameEngineTexture와 GameEngineRenderTarget이 각각 한개씩 나눠갖는다

	Color = _Color;
	Texture = _Texture;
}





void GameEngineRenderTarget::Clear()
{
	ID3D11RenderTargetView* RTV = Texture->GetRTV();

	if (nullptr == RTV)
	{
		MsgAssert("렌더타겟 뷰가 존재하지 않아서 클리어가 불가능합니다");
		return;
	}

	//그려진 이미지 지우기
	GameEngineDevice::GetContext()->ClearRenderTargetView(RTV, Color.Arr1D);


	ID3D11DepthStencilView* DSV =
		(DepthTexture != nullptr) ? DepthTexture->GetDSV() : nullptr;

	//깊이버퍼 초기화하기
	GameEngineDevice::GetContext()->ClearDepthStencilView(DSV, 
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}


//랜파에서 아웃풋 머저를 위한 렌더타겟뷰를 세팅해주는 단계(Core의 RenderStart에서 호출)
void GameEngineRenderTarget::Setting()
{
	ID3D11RenderTargetView* RTV = Texture->GetRTV();

	if (nullptr == RTV)
	{
		MsgAssert("렌더타겟 뷰가 존재하지 않습니다");
		return;
	}

	//디바이스가 스왑체인을 통해 받거나 만든 텍스처와 깊이 버퍼용 텍스처를 GPU에 세팅
	ID3D11DepthStencilView* DSV =
		(DepthTexture != nullptr) ? DepthTexture->GetDSV() : nullptr;

	//여러 RTV를 세팅할 수 있는데 그중 하나만 세팅
	GameEngineDevice::GetContext()->OMSetRenderTargets(1, &RTV, DSV);
}


void GameEngineRenderTarget::Reset()
{
	ID3D11RenderTargetView* RTV[8] = { nullptr };
	GameEngineDevice::GetContext()->OMSetRenderTargets(8, RTV, nullptr);
}


void GameEngineRenderTarget::CreateDepthTexture()
{
	D3D11_TEXTURE2D_DESC Desc = { 0 };

	Desc.ArraySize = 1;
	Desc.Width = Texture->GetWidth();
	Desc.Height= Texture->GetHeight();

	//깊이버퍼 4바이트중 3바이트는 0~1사이 깊이값
	//나머지 1바이트는 스텐실 값
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;

	Desc.MipLevels = 1;
	Desc.Usage = D3D11_USAGE_DEFAULT;

	Desc.CPUAccessFlags = 0;
	Desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;

	DepthTexture = GameEngineTexture::Create(Desc);
}
