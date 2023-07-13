#include "PrecompileHeader.h"
#include "CrossTownLevel3.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "SoundMgr.h"

#include "BackGround.h"
#include "FieldDoor.h"


const std::vector<std::pair<std::string_view, float4>> CrossTownLevel3::BGInfoes =
{
	{"CrossTown3BG.png", float4{0.f, 0.f, 500.f}},
};

const std::string_view CrossTownLevel3::CollisionImageName = "CrossTown3ColBG.png";
const std::vector<float4> CrossTownLevel3::EnemySpawnPoses =
{
	float4{-955.f, -10.f},
	float4{10.f, -10.f}
};



const std::vector<NpcCreateInfo> CrossTownLevel3::NpcInfoes =
{
	{"SchoolBoyC", float4{-1394.f, -156.f, -156.f}, false, true},
	{"WorkingFemaleB", float4{-1224.f, -84.f, -84.f}, true, false},
	{"SchoolBoyB", float4{-241.f, -30.f, -30.f}, false, true},
	{"SchoolGirlE2", float4{451.f, -154.f, -154.f}, true, false},
	{"WorkingMaleA", float4{1203.f, -45.f, -45.f}, false, true},
	{"SchoolGirlD", float4{1350.f, -190.f, -190.f}, true, false},
	{"WorkingMaleC", float4{1605.f, -210.f, -210.f}, true, false},
};


CrossTownLevel3::CrossTownLevel3()
{

}

CrossTownLevel3::~CrossTownLevel3()
{

}

void CrossTownLevel3::Start()
{
	FieldLevelBase::Start();
	LoadImgRes();

	CreateBackGrounds();
	CreateDoors();
	CreateEnemies();
	FieldLevelBase::CreateNpcs(NpcInfoes);

	FieldLevelBase::SetPlayerStartPosition(float4{ -1813.f, -245.f });

	//FieldLevelBase::OnTransView_ForDebug();
}

void CrossTownLevel3::LoadImgRes()
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	Dir.Move("CrossTown3");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}
}

void CrossTownLevel3::CreateBackGrounds()
{
	const float4 LevelArea = ResourceHelper::GetTextureScale("CrossTown3BG.png") * RCGDefine::ResourceScaleConvertor;
	FieldLevelBase::Init(LevelArea, TileInfoData(200, 50));
	FieldLevelBase::CreateBackGrounds(BGInfoes);
	FieldLevelBase::CreateCollisionImage(CollisionImageName);
}

void CrossTownLevel3::CreateDoors()
{
	TownBossDoor = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	TownBossDoor->Init(DoorType::Normal);
	FieldLevelBase::SetDoorOpenFunc([this]()
	{
		TownBossDoor->Unlock(LevelNames::TownBossLevel);
	});
	TownBossDoor->GetTransform()->SetLocalPosition(float4{1900.f, -300.f, -300.f});

	std::shared_ptr<FieldDoor> DoorPtr = nullptr;
	DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Normal);
	DoorPtr->Unlock(LevelNames::CrossTownLevel2);
	DoorPtr->GetTransform()->SetLocalPosition(float4{ -1900.f, -300.f, -300.f });

	DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Shop, float4{0.f, 100.f, 100.f});
	DoorPtr->Unlock(LevelNames::Shop_BurgerLevel);
	DoorPtr->GetTransform()->SetLocalPosition(float4::Right * 980.f);
}


void CrossTownLevel3::CreateEnemies()
{
	EnemySpawner& Spawner = FieldLevelBase::GetEnemySpawner();

	Spawner.SetCycleDuration(1.f, 3.f);
	Spawner.SetCycleMax(8);
	Spawner.OnCycleSpawn({
		EnemyType::Cheerleader,
		EnemyType::Cheerleader,
		EnemyType::Cop,
		EnemyType::TigerMan,
		}, EnemySpawnPoses);
}


void CrossTownLevel3::LevelChangeStart()
{
	FieldLevelBase::LevelChangeStart();

	const std::string_view BgmName = "CrossTownLevel.mp3";
	if (BgmName == SoundMgr::GetCurBgmName())
		return;

	SoundMgr::ChangeBGM(BgmName);
}

void CrossTownLevel3::LevelChangeEnd()
{
	FieldLevelBase::LevelChangeEnd();

	if (LevelNames::TownBossLevel == FieldDoor::GetRegistNextLevel())
	{
		SoundMgr::BgmFadeOut(BgmFadeDuration);
	}
}
