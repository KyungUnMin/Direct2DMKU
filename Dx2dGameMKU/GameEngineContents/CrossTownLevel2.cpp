#include "PrecompileHeader.h"
#include "CrossTownLevel2.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"
#include "FieldDoor.h"

const std::string_view CrossTownLevel2::MapImgName = "CrossTown2BG.png";
const float4 CrossTownLevel2::MapScale = float4{ 1726.f, 462.f } *RCGDefine::ResourceScaleConvertor;

CrossTownLevel2::CrossTownLevel2()
{

}

CrossTownLevel2::~CrossTownLevel2()
{

}

void CrossTownLevel2::Start()
{
	FieldLevelBase::Start();

	LoadImgRes();
	FieldLevelBase::InitLevelArea(MapScale, TileInfoData());
	FieldLevelBase::GetBG()->CreateBackImage(MapImgName, MapScale);

	CreateDoors();

	FieldLevelBase::SetPlayerStartPosition(float4{ -1000.f, 0.f , 0.f });
}

void CrossTownLevel2::LoadImgRes()
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	Dir.Move("CrossTown2");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}
}

void CrossTownLevel2::CreateDoors()
{
	std::shared_ptr<FieldDoor> DoorPtr = nullptr;

	DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Normal);
	DoorPtr->Unlock(LevelNames::CrossTownLevel3);
	DoorPtr->GetTransform()->SetLocalPosition(float4{2100.f, -350.f, -350.f});

	DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Normal);
	DoorPtr->Unlock(LevelNames::CrossTownLevel1);
	DoorPtr->GetTransform()->SetLocalPosition(float4{ -2100.f, -350.f, -350.f });

	DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Shop, float4{ 0.f, 50.f, 50.f });
	DoorPtr->Unlock(LevelNames::Shop_StoreLevel);
	DoorPtr->GetTransform()->SetLocalPosition(float4{-1000.f, -50.f, -50.f});
}
