#include "PrecompileHeader.h"
#include "SchoolEntryLevel.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"
#include "FieldDoor.h"



//<텍스처 이름, 오프셋>
const std::vector<std::pair<std::string_view, float4>> SchoolEntryLevel::BGInfoes =
{
	{"SchoolEntryBG.png", float4{ 0.f, 0.f, 500.f }},


	{"School_Desks.png", float4{ -598.f, -311.f}},
	{"School_Desks.png", float4{ -387.f, -311.f}},
	{"School_Desks.png", float4{ -170.f, -311.f}},
	{"School_Desks.png", float4{ 45.f, -311.f}},

	{"School_Desks.png", float4{ -470.f, -175.f}},
	{"School_Desks.png", float4{ -258.f, -175.f}},
	{"School_Desks.png", float4{ -37.f, -175.f}},
	{"School_Desks.png", float4{ 177.f, -175.f}},

	/*{"School_TeacherDesk.png", float4{550.f, -236.f}},
	{"School_Chair1.png", float4{ 527.f, -130.f}},
	{"School_Chair2.png", float4{ 667.f, -240.f}},*/
};

const std::string_view SchoolEntryLevel::CollisionImageName = "SchoolEntryColBG.png";

const float4 SchoolEntryLevel::LevelAreaScale = float4{ 672.f, 224.f } *RCGDefine::ResourceScaleConvertor;

//좌측 상단부터
const std::vector<float4> SchoolEntryLevel::DestSitPos =
{
	{-502.f, -156.f, -156.f},
	{-290.f, -156.f, -156.f},
	{-70.f, -156.f, -156.f},
	{147.f, -156.f, -156.f},

	{-632.f, -291.f, -291.f},
	{-420.f, -291.f, -291.f},
	{-205.f, -291.f, -291.f},
	{13.f, -291.f, -291.f}
};

SchoolEntryLevel::SchoolEntryLevel()
{

}

SchoolEntryLevel::~SchoolEntryLevel()
{

}


#include "BossIntroMovie.h"


void SchoolEntryLevel::Start()
{
	FieldLevelBase::Start();
	LoadImgRes();

	CreateBackGrounds();
	//CreateDesks();
	CreateDoors();

	FieldLevelBase::SetPlayerStartPosition(float4{ -200.f, -200.f , 0.f});
	CreateEnemies();

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

void SchoolEntryLevel::CreateDesks()
{
	const std::vector<float4> DeskPoses =
	{
		 float4{ -598.f, -343.f},
		 float4{ -387.f, -343.f},
		float4{ -170.f, -343.f},
		float4{ 45.f, -343.f},

		float4{ -470.f, -207.f},
		float4{ -258.f, -207.f },
		float4{ -37.f, -207.f },
		float4{ 177.f, -207.f }
	};


	std::shared_ptr<BackGround> BGPtr = FieldLevelBase::GetBackGround();
	for (const float4& DeskPos : DeskPoses)
	{
		std::shared_ptr<GameEngineSpriteRenderer> Render = BGPtr->CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
		float4 Pos = DeskPos;
		Pos.z = Pos.y;
		Render->GetTransform()->SetWorldPosition(Pos);

		Render->SetScaleToTexture("School_Desks.png");
	}
}

void SchoolEntryLevel::CreateDoors()
{
	std::shared_ptr<FieldDoor> DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Normal, float4{0.f, 100.f, 100.f});
	DoorPtr->Unlock(LevelNames::SchoolBossLevel);
	DoorPtr->GetTransform()->SetLocalPosition(float4{ 360.f, -25.f, -25.f });
}

#include "FieldEnemy_SchoolBoy.h"
#include "FieldEnemy_SchoolGirl.h"

void SchoolEntryLevel::CreateEnemies()
{
	std::shared_ptr<FieldEnemy_SchoolBoy> SchoolBoyPtr = nullptr;
	std::shared_ptr<FieldEnemy_SchoolGirl> SchoolGirlPtr = nullptr;

	//5번은 Enemy가 아닌 일반 애니메이션으로 할 계획
	const size_t BoySitPosArr[3] = {0, 2, 6};
	for (size_t i = 0; i < 3; ++i)
	{
		SchoolBoyPtr = CreateActor<FieldEnemy_SchoolBoy>(static_cast<int>(UpdateOrder::Enemy));
		size_t SitIndex = BoySitPosArr[i];
		SchoolBoyPtr->GetTransform()->SetWorldPosition(DestSitPos[SitIndex]);
		SchoolBoyPtr->SitDown();
	}
	
	const size_t GirlSitPosArr[3] = { 1, 3, 4 };
	for (size_t i = 0; i < 3; ++i)
	{
		SchoolGirlPtr = CreateActor<FieldEnemy_SchoolGirl>(static_cast<int>(UpdateOrder::Enemy));
		size_t SitIndex = GirlSitPosArr[i];
		SchoolGirlPtr->GetTransform()->SetWorldPosition(DestSitPos[SitIndex]);
		SchoolGirlPtr->SitDown();
	}

}