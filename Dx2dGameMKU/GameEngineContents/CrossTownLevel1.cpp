#include "PrecompileHeader.h"
#include "CrossTownLevel1.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"
#include "FieldDoor.h"

const std::string_view CrossTownLevel1::MapImgName = "CrossTown1BG.png";
const float4 CrossTownLevel1::MapScale = float4{ 1818.f, 500.f } *RCGDefine::ResourceScaleConvertor;

CrossTownLevel1::CrossTownLevel1()
{

}

CrossTownLevel1::~CrossTownLevel1()
{

}

void CrossTownLevel1::Start()
{
	FieldLevelBase::Start();

	LoadImgRes();
	FieldLevelBase::InitLevelArea(MapScale, TileInfoData());
	FieldLevelBase::GetBG()->CreateBackImage(MapImgName, MapScale);

	CreateDoors();
}


void CrossTownLevel1::LoadImgRes()
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	Dir.Move("CrossTown1");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}
}

void CrossTownLevel1::CreateDoors()
{
	std::shared_ptr<FieldDoor> DoorPtr = nullptr;

	DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Normal);
	DoorPtr->Unlock(LevelNames::CrossTownLevel2);
	DoorPtr->GetTransform()->SetLocalPosition(float4{ 2200.f, -475.f, -475.f});

	DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Gym, float4{0.f, 100.f, 100.f});
	DoorPtr->Unlock(LevelNames::Shop_GymLevel);
	DoorPtr->GetTransform()->SetLocalPosition(float4{1250.f, -100.f, -100.f});
}
