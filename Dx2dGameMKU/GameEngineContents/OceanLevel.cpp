#include "PrecompileHeader.h"
#include "OceanLevel.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"

const std::string_view OceanLevel::MapImgName = "OceanBG.png";
const float4 OceanLevel::MapScale = float4{ 672.f, 194.f } *RCGDefine::ResourceScaleConvertor;

OceanLevel::OceanLevel()
{

}

OceanLevel::~OceanLevel()
{

}

void OceanLevel::Start()
{
	FieldLevelBase::Start();

	LoadImgRes();
	FieldLevelBase::SettingBackImg(MapImgName, MapScale);
}

void OceanLevel::LoadImgRes()
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	Dir.Move("Ocean");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}
}
