#include "PrecompileHeader.h"
#include "TownBossLevel.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"
#include "FieldDoor.h"

const std::vector<std::pair<std::string_view, float4>> TownBossLevel::BGInfoes =
{
	{"TownBossBG.png", float4{0.f, 0.f}},
};

const std::string_view TownBossLevel::CollisionImageName = "???";

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
	CreateBackGrounds();
	CreateDoors();

	FieldLevelBase::SetPlayerStartPosition(float4::Zero);
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

void TownBossLevel::CreateBackGrounds()
{
	const float4 LevelArea = ResourceHelper::GetTextureScale("TownBossBG.png") * RCGDefine::ResourceScaleConvertor;
	FieldLevelBase::InitLevelArea(LevelArea, TileInfoData());
	FieldLevelBase::CreateBackGrounds(BGInfoes);
	//FieldLevelBase::CreateCollisionImage(CollisionImageName);
}

void TownBossLevel::CreateDoors()
{
	std::shared_ptr<FieldDoor> DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Normal);
	DoorPtr->Unlock(LevelNames::OceanLevel);
}
