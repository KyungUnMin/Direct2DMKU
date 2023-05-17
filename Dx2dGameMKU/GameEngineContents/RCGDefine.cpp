#include "PrecompileHeader.h"
#include "RCGDefine.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEnginePixelShader.h>
#include <GameEngineCore/GameEngineVideo.h>


const std::string_view RCGDefine::EnginePipeName = "2DTexture";
const std::string_view RCGDefine::EngineTexName = "DiffuseTex";

const float RCGDefine::ResolutionConvertor = (1080.f / 1920.f);
const float RCGDefine::ResourceScaleConvertor = 2.5f;

const std::vector<std::string_view> RCGDefine::PipeEnumToString =
{
	"DirectColor",
	"Burn",
	"FieldDoor",
	"GlichStair",
	"MpBar",
	"Tile",
};


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

void RCGDefine::LoadContentPath(ResType _Type, const std::vector<std::string_view>& _Pathes)
{
	if (ResType::Shader == _Type)
	{
		MsgAssert("쉐이더는 다른 함수를 사용해주세요");
		return;
	}

	GameEngineDirectory Dir;
	MoveContentPath(Dir, _Type);
	for (const std::string_view& Path : _Pathes)
	{
		Dir.Move(Path);
	}

	std::vector<std::string_view> Extensions;
	switch (_Type)
	{
	case ResType::Image:
		Extensions.push_back(".png");
		break;
	case ResType::Sound:
		Extensions.push_back(".mp3");
		break;
	case ResType::Video:
		Extensions.push_back(".avi");
		break;
	}

	std::vector<GameEngineFile> Files = Dir.GetAllFile(Extensions);
	for (const GameEngineFile& File : Files)
	{
		switch (_Type)
		{
		case ResType::Image:
			GameEngineTexture::Load(File.GetFullPath());
			break;
		case ResType::Sound:
		{
			MsgAssert("사운드는 아직 준비중...");
			break;
		}
		case ResType::Video:
			GameEngineVideo::Load(File.GetFullPath());
			break;
		}
	}
}


RCGDefine::RCGDefine()
{

}



RCGDefine::~RCGDefine()
{

}
