#include "PrecompileHeader.h"
#include "OceanBossLevel.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"

const std::string_view OceanBossLevel::MapImgName = "OceanBossBG.png";
const float4 OceanBossLevel::MapScale = float4{ 640.f, 360.f } *RCGDefine::ResourceScaleConvertor;

OceanBossLevel::OceanBossLevel()
{

}

OceanBossLevel::~OceanBossLevel()
{

}

#include "ColorWave.h"

void OceanBossLevel::Start()
{
	FieldLevelBase::Start();

	LoadImgRes();
	FieldLevelBase::InitLevelArea(MapScale, TileInfoData());
	FieldLevelBase::GetBG()->CreateBackImage(MapImgName, MapScale);

	CreateActor<ColorWave>();
}

void OceanBossLevel::LoadImgRes()
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	Dir.Move("OceanBoss");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}
}
