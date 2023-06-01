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

const std::vector<float4> CrossTownLevel2::EnemySpawnPoses =
{
	float4{-1300.f, 120.f},
	float4{50.f, 75.f},
	float4{180.f, -305.f},
	float4{765.f, -170.f}
};

const std::vector<NpcCreateInfo> CrossTownLevel2::NpcInfoes =
{
	{"SchoolGirlB", float4{-875.f, 145.f, 145.f}, true, false},
	{"CoolArtists", float4{-945.f, 130.f, 130.f}, false, false},
	{"SchoolBoyB", float4{-1010.f, -45.f, -45.f}, true, true},
	{"SchoolGirlA", float4{-310.f, -5.f, -5.f}, false, false},
	{"CasualGirlC", float4{-240.f, -20.f, -20.f}, true, false},
	{"SchoolGirlE", float4{1645.f, -480.f, -480.f}, false, false},
	{"SchoolBoyC", float4{1715.f, -465.f, -465.f}, true, false},
};


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



//#include "DebugActor.h"

void CrossTownLevel2::CreateEnemies()
{
	EnemySpawner& Spawner = FieldLevelBase::GetEnemySpawner();

	Spawner.SetCycleDuration(1.f, 5.f);
	Spawner.SetCycleMax(6);
	Spawner.OnCycleSpawn({
		EnemyType::Cheerleader,
		EnemyType::Hooligan, 
		EnemyType::Cop 
		}, EnemySpawnPoses);

	//GetLevel()->CreateActor<DebugActor>(UpdateOrder::FOR_DEBUG)->Init_PositionPointer();
}