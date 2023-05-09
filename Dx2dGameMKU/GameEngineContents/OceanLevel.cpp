#include "PrecompileHeader.h"
#include "OceanLevel.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"
#include "FieldDoor.h"

const std::vector<std::pair<std::string_view, float4>> OceanLevel::BGInfoes =
{
	{"OceanBG.png", float4{0.f, 0.f, 500.f}},
};

const std::string_view OceanLevel::CollisionImageName = "OceanColBG.png";



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

	CreateBackGrounds();
	CreateDoors();

	FieldLevelBase::SetPlayerStartPosition(float4::Zero);
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

void OceanLevel::CreateBackGrounds()
{
	const float4 LevelArea = ResourceHelper::GetTextureScale("OceanBG.png") * RCGDefine::ResourceScaleConvertor;
	FieldLevelBase::Init(LevelArea, TileInfoData());
	FieldLevelBase::CreateBackGrounds(BGInfoes);
	FieldLevelBase::CreateCollisionImage(CollisionImageName);
}

void OceanLevel::CreateDoors()
{
	std::shared_ptr<FieldDoor> DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Normal);
	DoorPtr->Unlock(LevelNames::OceanBossLevel);
}
