#include "PrecompileHeader.h"
#include "SchoolEntryLevel.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"
#include "FieldDoor.h"

//<텍스처 이름, 오프셋>
const std::vector<std::pair<std::string_view, float4>> SchoolEntryLevel::BGInfoes =
{
	{"SchoolEntryBG.png", float4{ 0.f, 0.f, 500.f }},

	{"School_Desks.png", float4{ -598.f, -242.f}},
	{"School_Desks.png", float4{ -387.f, -242.f}},
	{"School_Desks.png", float4{ -170.f, -242.f}},
	{"School_Desks.png", float4{ 45.f, -242.f}},

	{"School_Desks.png", float4{ -470.f, -108.f}},
	{"School_Desks.png", float4{ -258.f, -108.f}},
	{"School_Desks.png", float4{ -37.f, -108.f}},
	{"School_Desks.png", float4{ 177.f, -108.f}},

	{"School_TeacherDesk.png", float4{ 550.f, -236.f}},
	{"School_Chair1.png", float4{ 527.f, -130.f}},
	{"School_Chair2.png", float4{ 667.f, -240.f}},
};

const std::string_view SchoolEntryLevel::CollisionImageName = "SchoolEntryColBG.png";

const float4 SchoolEntryLevel::LevelAreaScale = float4{ 672.f, 224.f } *RCGDefine::ResourceScaleConvertor;

SchoolEntryLevel::SchoolEntryLevel()
{

}

SchoolEntryLevel::~SchoolEntryLevel()
{

}

#include "FieldEnemy_SchoolBoy.h"
#include "FieldEnemy_SchoolGirl.h"

#include "BossIntroMovie.h"
#include "BurnExample.h"


void SchoolEntryLevel::Start()
{
	FieldLevelBase::Start();
	LoadImgRes();

	CreateBackGrounds();
	CreateDoors();

	FieldLevelBase::SetPlayerStartPosition(float4{ -200.f, -200.f , 0.f});

	CreateActor<FieldEnemy_SchoolBoy>(static_cast<int>(UpdateOrder::Enemy))
		->GetTransform()->SetWorldPosition(float4{ -200.f, -200.f , 0.f });
	CreateActor<FieldEnemy_SchoolGirl>(static_cast<int>(UpdateOrder::Enemy))
		->GetTransform()->SetWorldPosition(float4{ -100.f, -200.f , 0.f });

	/*CreateActor<FieldEnemy_SchoolBoy>(static_cast<int>(UpdateOrder::Enemy))
		->GetTransform()->SetWorldPosition(float4{ 0.f, -200.f , 0.f });
	CreateActor<FieldEnemy_SchoolBoy>(static_cast<int>(UpdateOrder::Enemy))
		->GetTransform()->SetWorldPosition(float4{ 100.f, -200.f , 0.f });
	CreateActor<FieldEnemy_SchoolBoy>(static_cast<int>(UpdateOrder::Enemy))
		->GetTransform()->SetWorldPosition(float4{ 200.f, -200.f , 0.f });*/


	//CreateActor<BossIntroMovie>(static_cast<int>(UpdateOrder::UI))->Init(MovieType::School);


}




void SchoolEntryLevel::LoadImgRes()
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	Dir.Move("SchoolEntry");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}
}


void SchoolEntryLevel::CreateBackGrounds()
{
	FieldLevelBase::Init(LevelAreaScale, TileInfoData(100, 50));
	FieldLevelBase::CreateBackGrounds(BGInfoes);
	FieldLevelBase::CreateCollisionImage(CollisionImageName);
}

void SchoolEntryLevel::CreateDoors()
{
	std::shared_ptr<FieldDoor> DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Normal, float4{0.f, 100.f, 100.f});
	DoorPtr->Unlock(LevelNames::SchoolBossLevel);
	DoorPtr->GetTransform()->SetLocalPosition(float4{ 360.f, -25.f, -25.f });
}

