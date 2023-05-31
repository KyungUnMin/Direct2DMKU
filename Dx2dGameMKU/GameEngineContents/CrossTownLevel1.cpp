#include "PrecompileHeader.h"
#include "CrossTownLevel1.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"

#include "BackGround.h"
#include "FieldDoor.h"
#include "ResourceHelper.h"
#include "FieldNPCBase.h"

const std::vector<std::pair<std::string_view, float4>> CrossTownLevel1::BGInfoes =
{
	{"CrossTown1LandScape.png", float4{ -323.f, 431.f , 500.f}},
	{"CrossTown1BG.png", float4{0.f, 0.f, 500.f}},

	//{"CrossTown1_Wood2.png", float4{-1984.f, -334.f, -334.f}},
	/*{"CrossTown1_Wood3.png", float4{300.f, 0.f, 0.f}},
	{"CrossTown1_Wood4.png", float4{400.f, 0.f, 0.f}},*/

};

const std::string_view CrossTownLevel1::CollisionImageName = "CrossTown1ColBG.png";

const std::vector<float4> CrossTownLevel1::EnemySpawnPoses = 
{
	float4{-1920.f, 170.f},
	float4{-2235.f, -605.f},
	float4{830.f, 180.f},
	float4{-1050.f, - 595.f},
	float4{305.f, -595.f},
	float4{855.f, -595.f},
};

const std::vector<std::pair<std::string_view, float4>> CrossTownLevel1::NpcInfoes =
{
	{"CasualBoyD", float4{100.f, 0.f, 0.f}},
	{"CoolArtists", float4{200.f, 0.f, 0.f}},
	{"SchoolBoyB", float4{300.f, 0.f, 0.f}},
};


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

	CreateBackGrounds();
	CreateDoors();
	CreateEnemies();
	CreateNPC();

	FieldLevelBase::SetPlayerStartPosition(float4{ -1000.f, 0.f , 0.f });
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


void CrossTownLevel1::CreateBackGrounds()
{
	const float4 LevelArea = ResourceHelper::GetTextureScale("CrossTown1BG.png") * RCGDefine::ResourceScaleConvertor;
	FieldLevelBase::Init(LevelArea, TileInfoData(200, 100));
	FieldLevelBase::CreateBackGrounds(BGInfoes);
	FieldLevelBase::CreateCollisionImage(CollisionImageName);
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


//#include "DebugActor.h"


void CrossTownLevel1::CreateEnemies()
{
	EnemySpawner& Spawner = FieldLevelBase::GetEnemySpawner();

	Spawner.SetCycleDuration(1.f, 5.f);
	Spawner.SetCycleMax(6);
	Spawner.OnCycleSpawn({
		EnemyType::Cheerleader,
		EnemyType::Hooligan,
		EnemyType::SchoolBoy,
		EnemyType::SchoolGirl,
		EnemyType::SchoolBoy,
		EnemyType::SchoolGirl
		}, EnemySpawnPoses);

	//GetLevel()->CreateActor<DebugActor>(UpdateOrder::FOR_DEBUG)->Init_PositionPointer();
}

void CrossTownLevel1::CreateNPC()
{
	for (const std::pair<std::string_view, float4>& Pair : NpcInfoes)
	{
		const std::string_view& FileName = Pair.first;
		const float4& Pos = Pair.second;

		std::shared_ptr<FieldNPCBase> Npc = nullptr;
		Npc = CreateActor<FieldNPCBase>(UpdateOrder::NPC);
		Npc->AnimationCreate(FileName);
		Npc->GetTransform()->SetLocalPosition(Pos);
	}

}
