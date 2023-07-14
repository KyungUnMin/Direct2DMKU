#include "PrecompileHeader.h"
#include "SchoolEntryLevel.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"
#include "FieldDoor.h"
#include "FieldNPCBase.h"
#include "SoundMgr.h"

#include "FieldEnemy_SchoolBoy.h"
#include "FieldEnemy_SchoolGirl.h"

//<텍스처 이름, 오프셋>
const std::vector<std::pair<std::string_view, float4>> SchoolEntryLevel::BGInfoes =
{
	{"SchoolEntryBG.png", float4{ 0.f, 0.f, 500.f }},


	{"School_Desks.png", float4{ -598.f, -310.f, -286.f}},
	{"School_Desks.png", float4{ -387.f, -310.f, -286.f}},
	{"School_Desks.png", float4{ -170.f, -310.f, -286.f}},
	{"School_Desks.png", float4{ 45.f, -310.f, -286.f}},

	{"School_Desks.png", float4{ -470.f, -173.f, -150.f}},
	{"School_Desks.png", float4{ -258.f, -173.f, -150.f}},
	{"School_Desks.png", float4{ -37.f, -173.f, -150.f}},
	{"School_Desks.png", float4{ 177.f, -173.f, -150.f}},

	{"School_DeskHalf2.png", float4{ -598.f, -310.f}},
	{"School_DeskHalf.png", float4{ -387.f, -310.f}},
	{"School_DeskHalf.png", float4{ -170.f, -310.f}},
	{"School_DeskHalf2.png", float4{ 45.f, -310.f}},
						   
	{"School_DeskHalf.png", float4{ -470.f, -173.f}},
	{"School_DeskHalf2.png", float4{ -258.f, -173.f}},
	{"School_DeskHalf2.png", float4{ -37.f, -173.f}},
	{"School_DeskHalf2.png", float4{ 177.f, -173.f}},

	{"School_TeacherDesk.png", float4{550.f, -236.f, -400.f}},
	/*{"School_Chair1.png", float4{ 527.f, -130.f}},
	{"School_Chair2.png", float4{ 667.f, -240.f}},*/
};

const std::string_view SchoolEntryLevel::CollisionImageName = "SchoolEntryColBG.png";

const float4 SchoolEntryLevel::LevelAreaScale = float4{ 672.f, 224.f } *RCGDefine::ResourceScaleConvertor;

//좌측 상단부터
const std::vector<float4> SchoolEntryLevel::DestSitPos =
{
	{-502.f, -156.f, -176.f},
	{-300.f, -156.f, -176.f},
	{-70.f, -156.f, -176.f},
	{137.f, -156.f, -176.f},

	{-642.f, -291.f, -312.f},
	{-420.f, -291.f, -312.f},
	{-205.f, -291.f, -312.f},
	{13.f, -291.f, -312.f}
};

SchoolEntryLevel::SchoolEntryLevel()
{

}

SchoolEntryLevel::~SchoolEntryLevel()
{

}




void SchoolEntryLevel::Start()
{
	FieldLevelBase::Start();
	LoadImgRes();

	CreateBackGrounds();
	CreateDoors();

	FieldLevelBase::SetPlayerStartPosition(float4{ -612.f, -152.f });
	CreateEnemies();

	CreateNPC();

	//디버깅용 DoorOpen함수 등록
	FieldLevelBase::SetDoorOpenFunc(std::bind(&SchoolEntryLevel::DoorOpen, this));


	//FieldLevelBase::OnTransView_ForDebug();
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
	DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Normal, float4{0.f, 100.f, 100.f});
	DoorPtr->GetTransform()->SetLocalPosition(float4{ 360.f, -25.f, -25.f });
	GetEnemySpawner().SetAllKillCallback(std::bind(&SchoolEntryLevel::DoorOpen, this));
}


void SchoolEntryLevel::DoorOpen()
{
	DoorPtr->Unlock(LevelNames::SchoolBossLevel);
}



void SchoolEntryLevel::CreateEnemies()
{
	EnemySpawner& Spawner = GetEnemySpawner();

	//5번은 Enemy가 아닌 일반 애니메이션으로 할 계획
	const size_t BoySitPosArr[3] = {0, 2, 6};
	for (size_t i = 0; i < 3; ++i)
	{
		size_t SitIndex = BoySitPosArr[i];
		std::shared_ptr<FieldEnemyBase> EnemyPtr = Spawner.CreateEnemy(EnemyType::SchoolBoy, DestSitPos[SitIndex]);
		std::dynamic_pointer_cast<FieldEnemy_SchoolBoy>(EnemyPtr)->SitDown();
	}
	
	const size_t GirlSitPosArr[3] = { 1, 3, 4 };
	for (size_t i = 0; i < 3; ++i)
	{
		size_t SitIndex = GirlSitPosArr[i];
		std::shared_ptr<FieldEnemyBase> EnemyPtr = Spawner.CreateEnemy(EnemyType::SchoolGirl, DestSitPos[SitIndex]);
		std::dynamic_pointer_cast<FieldEnemy_SchoolGirl>(EnemyPtr)->SitDown();
	}

}

void SchoolEntryLevel::CreateNPC()
{
	const float4 NpcPos = float4{ 595.f, -175.f ,-175.f };

	std::shared_ptr<FieldNPCBase> Teacher = nullptr;
	Teacher = CreateActor<FieldNPCBase>(UpdateOrder::NPC);
	Teacher->AnimationCreate("Teacher");

	GameEngineTransform* NpcTrans = Teacher->GetTransform();
	NpcTrans->SetLocalPosition(NpcPos);
}

void SchoolEntryLevel::LevelChangeStart()
{
	FieldLevelBase::LevelChangeStart();

	SoundMgr::ChangeBGM("SchoolEntryLevel.mp3");
}

void SchoolEntryLevel::LevelChangeEnd()
{
	FieldLevelBase::LevelChangeEnd();

	SoundMgr::BgmFadeOut(BgmFadeDuration);
}

