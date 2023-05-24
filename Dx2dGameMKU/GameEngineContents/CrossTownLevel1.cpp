#include "PrecompileHeader.h"
#include "CrossTownLevel1.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"
#include "FieldDoor.h"
#include "ResourceHelper.h"

const std::vector<std::pair<std::string_view, float4>> CrossTownLevel1::BGInfoes =
{
	{"CrossTown1LandScape.png", float4{ -323.f, 431.f , 500.f}},
	{"CrossTown1BG.png", float4{0.f, 0.f, 500.f}},

	//{"CrossTown1_Wood2.png", float4{-1984.f, -334.f, -334.f}},
	/*{"CrossTown1_Wood3.png", float4{300.f, 0.f, 0.f}},
	{"CrossTown1_Wood4.png", float4{400.f, 0.f, 0.f}},*/

};

const std::string_view CrossTownLevel1::CollisionImageName = "CrossTown1ColBG.png";

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


#include <GameEngineBase/GameEngineRandom.h>
#include "FieldEnemy_SchoolBoy.h"
#include "FieldEnemy_SchoolGirl.h"


void CrossTownLevel1::CreateEnemies()
{
	std::shared_ptr<FieldEnemy_SchoolBoy> SchoolBoyPtr = nullptr;
	std::shared_ptr<FieldEnemy_SchoolGirl> SchoolGirlPtr = nullptr;

	const float RangeWidth = 1000.f;
	const float RangeHeight = 100.f;

	for (size_t i = 0; i < 5; ++i)
	{
		SchoolBoyPtr = CreateActor<FieldEnemy_SchoolBoy>(static_cast<int>(UpdateOrder::Enemy));
		
		float PosX = GameEngineRandom::MainRandom.RandomFloat(-RangeWidth, RangeWidth);
		float PosY = GameEngineRandom::MainRandom.RandomFloat(-RangeHeight, 0.f);
		SchoolBoyPtr->GetTransform()->SetWorldPosition(float4{PosX, PosY, PosY, 1});
	}
	
	for (size_t i = 0; i < 5; ++i)
	{
		SchoolGirlPtr = CreateActor<FieldEnemy_SchoolGirl>(static_cast<int>(UpdateOrder::Enemy));

		float PosX = GameEngineRandom::MainRandom.RandomFloat(-RangeWidth, RangeWidth);
		float PosY = GameEngineRandom::MainRandom.RandomFloat(-RangeHeight, 0.f);
		SchoolGirlPtr->GetTransform()->SetWorldPosition(float4{ PosX, PosY, PosY, 1 });
	}
}