#include "PrecompileHeader.h"
#include "ContentsSelfRenderer.h"

ContentsSelfRenderer::ContentsSelfRenderer()
{

}

ContentsSelfRenderer::~ContentsSelfRenderer()
{

}

void ContentsSelfRenderer::Init(CamType _CamOrder)
{
	Order = _CamOrder;
	int OrderNum = static_cast<int>(_CamOrder);
	GameEngineRenderer::PushCameraRender(OrderNum);
}

void ContentsSelfRenderer::Update(float _DeltaTime)
{
	GameEngineSpriteRenderer::Update(_DeltaTime);

	if (CamType::UNKNOWN == Order)
	{
		MsgAssert("ī�޶� ���������� �ʾҽ��ϴ�");
		return;
	}

	
}

