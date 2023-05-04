#include "PrecompileHeader.h"
#include "SchoolBossLevel.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"
#include "FieldDoor.h"

const std::string_view SchoolBossLevel::MapImgName = "SchoolBossBG.png";
const float4 SchoolBossLevel::MapScale = float4{ 923.f, 360.f } *RCGDefine::ResourceScaleConvertor;

SchoolBossLevel::SchoolBossLevel()
{

}

SchoolBossLevel::~SchoolBossLevel()
{

}

void SchoolBossLevel::Start()
{
	FieldLevelBase::Start();

	LoadImgRes();
	FieldLevelBase::InitLevelArea(MapScale, TileInfoData());
	FieldLevelBase::GetBG()->CreateBackImage(MapImgName, MapScale);
	FieldLevelBase::GetBG()->CreateCollisionImage("SchoolBossColBG.png");

	std::shared_ptr<FieldDoor> DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Normal);
	DoorPtr->Unlock(LevelNames::CrossTownLevel1);

	FieldLevelBase::SetPlayerStartPosition(float4{ -700.f, 0.f , 0.f });
}

void SchoolBossLevel::LoadImgRes()
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	Dir.Move("SchoolBoss");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}
}
