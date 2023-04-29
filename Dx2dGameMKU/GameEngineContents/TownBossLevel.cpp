#include "PrecompileHeader.h"
#include "TownBossLevel.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"

const std::string_view TownBossLevel::MapImgName = "TownBossBG.png";
const float4 TownBossLevel::MapScale = float4{ 611.f, 419.f } *RCGDefine::ResourceScaleConvertor;

TownBossLevel::TownBossLevel()
{

}

TownBossLevel::~TownBossLevel()
{

}

void TownBossLevel::Start()
{
	FieldLevelBase::Start();

	LoadImgRes();
	FieldLevelBase::InitLevelArea(MapScale, TileInfoData());
	FieldLevelBase::GetBG()->CreateBackImage(MapImgName, MapScale);
}

void TownBossLevel::LoadImgRes()
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	Dir.Move("TownBoss");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}
}
