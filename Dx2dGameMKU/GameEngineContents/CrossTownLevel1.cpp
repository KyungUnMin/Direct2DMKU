#include "PrecompileHeader.h"
#include "CrossTownLevel1.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "SoundMgr.h"
#include "InventoryMgr.h"

#include "BackGround.h"
#include "FieldDoor.h"
#include "ResourceHelper.h"
#include "TalkUI.h"
#include "TutorialUI.h"
#include "CrossTownLevel3.h"



const std::vector<std::pair<std::string_view, float4>> CrossTownLevel1::BGInfoes =
{
	{"CrossTown1LandScape.png", float4{ -323.f, 431.f , 500.f}},
	{"CrossTown1BG.png", float4{0.f, 0.f, 500.f}},

	{"CrossTown1_Wood2.png", float4{-1984.f, -334.f, -635.f}},
	{"CrossTown1_Wood3.png", float4{-1139.f, -396.f, -635.f}},
	{"CrossTown1_Wood4.png", float4{296.f, -336.f, -635.f}},

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

const std::vector<NpcCreateInfo> CrossTownLevel1::NpcInfoes =
{
	{"CasualBoyD", float4{-875.f, 145.f, 145.f}, true, false},
	{"CoolArtists", float4{-945.f, 130.f, 130.f}, false, false},
	{"SchoolBoyB", float4{-1010.f, -45.f, -45.f}, true, true},
	{"SchoolGirlA", float4{-310.f, -5.f, -5.f}, false, false},
	{"CasualGirlC", float4{-240.f, -20.f, -20.f}, true, false},
	{"SchoolGirlE", float4{1645.f, -480.f, -480.f}, false, false},
	{"SchoolBoyC", float4{1715.f, -465.f, -465.f}, true, false},
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
	FieldLevelBase::CreateNpcs(NpcInfoes);
	CreateGodaiNPC();
	CreateTalkArea();

	
	FieldLevelBase::SetPlayerStartPosition(float4{ -2214.f, -171.f });

	/*FieldLevelBase::SetDoorOpenFunc([this]()
	{
		CreateActor<ContinueBox>(UpdateOrder::UI)->Init([]()
		{
			int a = 0;
		});
	});*/

	//FieldLevelBase::OnTransView_ForDebug();
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

	//DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	//DoorPtr->Init(DoorType::Gym, float4{0.f, 100.f, 100.f});
	//DoorPtr->Unlock(LevelNames::Shop_GymLevel);
	//DoorPtr->GetTransform()->SetLocalPosition(float4{1250.f, -100.f, -100.f});
}




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

}


void CrossTownLevel1::CreateGodaiNPC()
{ 
	const float4 NpcPos = float4{ -1500.f, -50.f };

	FieldLevelBase::CreateTalkNPC("Godai", NpcPos, [this]() -> bool
	{
		std::shared_ptr<TalkUI> Talk = nullptr;
		Talk = CreateActor<TalkUI>(UpdateOrder::UI);

		if (true == InventoryMgr::IsContain(InvenItemType::DoubleBurger))
		{
			InventoryMgr::Erase(InvenItemType::DoubleBurger);
			Talk->Init(TalkType::Godai2);
			Talk->Excute();

			Talk->SetDestroyCallBack([]()
			{
				TutorialUI::BindTurorial("야마다를 만나자!", "햄버거 집 뒤쪽에 길이 보인다!", []()
				{
					CrossTownLevel3::OpenTownBossDoor();
					return true;
				});
			});
			return true;
		}

		Talk->Init(TalkType::Godai3);
		Talk->Excute();
		return false;
	});
}

void CrossTownLevel1::CreateTalkArea()
{
	std::shared_ptr<TalkUI> TalkPtr = nullptr;
	TalkPtr = CreateActor<TalkUI>(UpdateOrder::UI);
	TalkPtr->Init(TalkType::Godai1, { -1800.f, -200.f });

	TalkPtr->SetDestroyCallBack([this]()
	{
		TutorialUI::BindTurorial("더블 텍 버거를 사오자!", "고다이가 더블 텍 버거를 원한다", []()
		{
			return true;
		});
	});

}


void CrossTownLevel1::LevelChangeStart()
{
	FieldLevelBase::LevelChangeStart();

	const std::string_view BgmName = "CrossTownLevel.mp3";
	if (BgmName == SoundMgr::GetCurBgmName())
		return;

	SoundMgr::ChangeBGM(BgmName);
}