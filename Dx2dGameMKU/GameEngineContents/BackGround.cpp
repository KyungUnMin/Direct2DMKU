#include "PrecompileHeader.h"
#include "BackGround.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCGDefine.h"

BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}

void BackGround::Start()
{
	GetTransform()->SetLocalPosition(float4{ 0.f, 0.f, 500.f });
}


void BackGround::AddBackImg(const std::string_view& _ResName, const float4& _Scale, const float4& _Offset /*= float4::Zero*/)
{
	std::shared_ptr<GameEngineSpriteRenderer> RendererPtr = CreateComponent<GameEngineSpriteRenderer>();
	RendererPtr->SetTexture(_ResName);
	
	//_Offset TODO

	RendererPtr->GetTransform()->SetLocalScale(_Scale);
}



