#include "PrecompileHeader.h"
#include "CrossTownLevel3.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"
#include "FieldDoor.h"

const std::string_view CrossTownLevel3::MapImgName = "CrossTown3BG.png";
const float4 CrossTownLevel3::MapScale = float4{ 1676.f, 360.f} *RCGDefine::ResourceScaleConvertor;

CrossTownLevel3::CrossTownLevel3()
{

}

CrossTownLevel3::~CrossTownLevel3()
{

}

void CrossTownLevel3::Start()
{
	FieldLevelBase::Start();

	LoadImgRes();
	FieldLevelBase::InitLevelArea(MapScale, TileInfoData());
	FieldLevelBase::GetBG()->CreateBackImage(MapImgName, MapScale);

	std::shared_ptr<FieldDoor> DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Normal);
	DoorPtr->Unlock(LevelNames::TownBossLevel);
}

void CrossTownLevel3::LoadImgRes()
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	Dir.Move("CrossTown3");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}
}
