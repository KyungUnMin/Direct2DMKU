#include "PrecompileHeader.h"
#include "CrossTownLevel3.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"
#include "FieldDoor.h"


const std::vector<std::pair<std::string_view, float4>> CrossTownLevel3::BGInfoes =
{
	{"CrossTown3BG.png", float4{0.f, 0.f, 500.f}},
};

const std::string_view CrossTownLevel3::CollisionImageName = "CrossTown3ColBG.png";


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

	FieldLevelBase::SetPlayerStartPosition(float4{ -1000.f, 0.f , 0.f });
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
	std::shared_ptr<FieldDoor> DoorPtr = nullptr;

	DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Normal);
	DoorPtr->Unlock(LevelNames::TownBossLevel);
	DoorPtr->GetTransform()->SetLocalPosition(float4{1900.f, -300.f, -300.f});

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
	GetEnemySpawner().CreateEnemy(EnemyType::Cop, float4::Down * 50.f);
}