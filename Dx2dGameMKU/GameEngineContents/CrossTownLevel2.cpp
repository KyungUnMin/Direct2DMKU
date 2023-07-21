#include "PrecompileHeader.h"
#include "CrossTownLevel2.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "SoundMgr.h"

#include "BackGround.h"
#include "FieldDoor.h"
#include "EnemySpawner.h"
#include "EventArea.h"

const std::vector<std::pair<std::string_view, float4>> CrossTownLevel2::BGInfoes =
{
	{"CrossTown2BG.png", float4{0.f, 0.f, 500.f}},
	{"CrossTown2_Build.png", float4{-1166.f, 226.f, -119.f}},
	{"CrossTown2_Grass.png", float4{574.f, -358.f, -433.f}},
	{"CrossTown2_Sky.png", float4{-1304.f, 315.f, 501.f}},
	{"CrossTown2_Wood1.png", float4{715.f, -106.f, -479.f}},
	{"CrossTown2_Wood2.png", float4{172.f, -145.f, -471.f}},
	{"CrossTown2_Build2.png", float4{-552.f, 286.f, -471.f}},
	{"CrossTown2_Dojo.png", float4{1404.f, 322.f, 499.f}},
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
	CreateTutorialArea();

	FieldLevelBase::SetPlayerStartPosition(float4{ -2125.f, -261.f });

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

	DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Gym, float4{ 0.f, 50.f, 50.f });
	DoorPtr->Unlock(LevelNames::Shop_GymLevel);
	DoorPtr->GetTransform()->SetLocalPosition(float4{ 1300.f, 75.f, 75.f });
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

void CrossTownLevel2::CreateTutorialArea()
{
	const float4 ItemTutoPos = float4{ -1300.f, 0.f };
	const float4 ItemTutoScale = float4{ 100.f, -1300.f };

	const float4 SkillTutoPos = float4{ 1200.f, 0.f };
	const float4 SkillTutoScale = float4{ 100.f, 1200.f };

	std::shared_ptr<EventArea> Event = nullptr;
	GameEngineTransform* EventTrans = nullptr;

	Event = CreateActor<EventArea>(UpdateOrder::EventArea);
	Event->Init_Tutorial("아이템을 구매해보자!", "상점에는 다양한 물건들을 살 수 있다");
	EventTrans = Event->GetTransform();
	EventTrans->SetLocalPosition(ItemTutoPos);
	EventTrans->SetLocalScale(ItemTutoScale);

	Event = CreateActor<EventArea>(UpdateOrder::EventArea);
	Event->Init_Tutorial("스킬을 구매해보자!", "체육관에선 돈으로 스킬을 배울수 있다");
	EventTrans = Event->GetTransform();
	EventTrans->SetLocalPosition(SkillTutoPos);
	EventTrans->SetLocalScale(SkillTutoScale);

	//BindTransControllerGUI<CrossTownLevel2>(EventTrans);
}


void CrossTownLevel2::LevelChangeStart()
{
	FieldLevelBase::LevelChangeStart();

	const std::string_view BgmName = "CrossTownLevel.mp3";
	if (BgmName == SoundMgr::GetCurBgmName())
		return;

	SoundMgr::ChangeBGM(BgmName);
}