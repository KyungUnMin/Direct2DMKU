#include "PrecompileHeader.h"
#include "ResourceHelper.h"

#include <GameEngineCore/GameEngineTexture.h>

ResourceHelper::ResourceHelper()
{

}

ResourceHelper::~ResourceHelper()
{

}

float4 ResourceHelper::GetTextureScale(const std::string_view& _ResName)
{
	std::shared_ptr<GameEngineTexture> TexPtr = GameEngineTexture::Find(_ResName);
	if (nullptr == TexPtr)
	{
		std::string Name = _ResName.data();
		MsgAssert("이런 이름을 가진 텍스처를 로드해준적이 없습니다 : " + Name);
	}

	float Width = static_cast<float>(TexPtr->GetWidth());
	float Height = static_cast<float>(TexPtr->GetHeight());
	return float4{ Width, Height };
}
