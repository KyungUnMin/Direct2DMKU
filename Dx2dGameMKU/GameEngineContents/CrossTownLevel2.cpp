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
	{"SchoolGirlB", float4{-1260.f, -145.f, -145.f}, true, false},
	{"CasualBoyC", float4{-915.f, -155.f, -155.f}, true, true},
	{"CasualGirlC", float4{-830.f, -178.f, -178.f}, false, true},
	{"CasualGirlD", float4{-10.f, 65.f, 65.f}, false, false},
	{"WorkingFemaleD", float4{250.f, 65.f, 65.f}, false, false},
	{"Nick", float4{335.f, 65.f, 65.f}, true, false},
	{"CasualBoyB", float4{-1434.f, -572.f, -572.f}, true, true},
	{"SchoolBoyC", float4{-181.f, -548.f, -548.f}, false, false},
	{"SchoolGirlD", float4{-118.f, -548.f, -548.f}, true, false},

	{"SchoolBoyB2", float4{852.f, 62.f, 62.f}, false, true},
	{"WorkingMaleA", float4{1780.f, -573.f, -573.f}, true, true},
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
	FieldLevelBase::CreateNpcs(NpcInfoes);

	FieldLevelBase::SetPlayerStartPosition(float4{ -1300.f, -200.f , -200.f });

	//FieldLevelBase::OnTransView_ForDebug();
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
	EnemySpawner& Spawner = FieldLevelBase::GetEnemySpawner();

	Spawner.SetCycleDuration(1.f, 5.f);
	Spawner.SetCycleMax(6);
	Spawner.OnCycleSpawn({
		EnemyType::Cheerleader,
		EnemyType::Hooligan, 
		EnemyType::Cop 
		}, EnemySpawnPoses);
}