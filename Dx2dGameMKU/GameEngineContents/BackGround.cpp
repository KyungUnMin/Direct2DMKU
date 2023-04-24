#include "PrecompileHeader.h"
#include "BackGround.h"

#include <GameEngineCore/GameEngineRenderer.h>

#include "RCGDefine.h"

BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}

void BackGround::SettingBackImg(const std::string_view& _ResName, const float4& _Scale)
{
	std::shared_ptr<GameEngineRenderer> RendererPtr = CreateComponent<GameEngineRenderer>();
	RendererPtr->SetPipeLine(RCGDefine::EnginePipeName);
	RendererPtr->GetShaderResHelper().SetTexture(RCGDefine::EngineTexName, _ResName);

	RendererPtr->GetTransform()->SetLocalScale(_Scale);
}


