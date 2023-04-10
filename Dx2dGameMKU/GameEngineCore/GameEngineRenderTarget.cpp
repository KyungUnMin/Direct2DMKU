#include "PrecompileHeader.h"
#include "GameEngineRenderTarget.h"

GameEngineRenderTarget::GameEngineRenderTarget()
{

}

GameEngineRenderTarget::~GameEngineRenderTarget()
{

}



void GameEngineRenderTarget::Create(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color)
{
	//�ؽ�ó�� ��쿣 �����͸� �ΰ��� ������
	//GameEngineTexture�� GameEngineRenderTarget�� ���� �Ѱ��� �������´�

	Color = _Color;
	Texture = _Texture;
}


void GameEngineRenderTarget::Clear()
{
	ID3D11RenderTargetView* RTV = Texture->GetRTV();

	if (nullptr == RTV)
	{
		MsgAssert("����Ÿ�� �䰡 �������� �ʾƼ� Ŭ��� �Ұ����մϴ�");
		return;
	}

	GameEngineDevice::GetContext()->ClearRenderTargetView(RTV, Color.Arr1D);
}
