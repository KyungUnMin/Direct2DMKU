#include "PrecompileHeader.h"
#include "CrossTownLevel2.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"
#include "FieldDoor.h"
#include "EnemySpawner.h"

const std::vector<std::pair<std::string_view, float4>> CrossTownLevel2::BGInfoes =
{
	{"CrossTown2BG.png", float4{0.f, 0.f, 500.f}}
};

const std::string_view CrossTownLevel2::CollisionImageName = "CrossTown2ColBG.png";



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

	CreateBackGrounds();
	CreateDoors();
	CreateEnemies();

	FieldLevelBase::SetPlayerStartPosition(float4{ -1300.f, -200.f , -200.f });
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

void CrossTownLevel2::CreateBackGrounds()
{
	const float4 LevelArea = ResourceHelper::GetTextureScale("CrossTown2BG.png") * RCGDefine::ResourceScaleConvertor;
	FieldLevelBase::Init(LevelArea, TileInfoData(200, 100));
	FieldLevelBase::CreateBackGrounds(BGInfoes);
	FieldLevelBase::CreateCollisionImage(CollisionImageName);
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

void CrossTownLevel2::CreateEnemies()
{
	//GetEnemySpawner().CreateEnemy(EnemyType::Hooligan, float4::Down * 100.f);
	GetEnemySpawner().CreateEnemy(EnemyType::TigerMan, float4::Down * 80.f);
}