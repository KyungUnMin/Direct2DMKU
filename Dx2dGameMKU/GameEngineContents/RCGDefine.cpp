#include "PrecompileHeader.h"
#include "RCGDefine.h"

const std::string_view RCGDefine::EnginePipeName = "2DTexture";
const std::string_view RCGDefine::EngineTexName = "DiffuseTex";

const float RCGDefine::ResolutionConvertor = (1080.f / 1920.f);
const float RCGDefine::ResourceScaleConvertor = 2.5f;

void RCGDefine::MoveContentPath(GameEngineDirectory& _Dir, ResType _Type)
{
	_Dir.MoveParentToDirectory("ContentsResource");
	_Dir.Move("ContentsResource");
	
	switch (_Type)
	{
	case ResType::Image:
		_Dir.Move("Image");
		break;
	case ResType::Shader:
		_Dir.Move("Shader");
		break;
	case ResType::Sound:
		_Dir.Move("Sound");
		break;
	case ResType::Video:
		_Dir.Move("Video");
		break;
	}
}

RCGDefine::RCGDefine()
{

}

RCGDefine::~RCGDefine()
{

}
