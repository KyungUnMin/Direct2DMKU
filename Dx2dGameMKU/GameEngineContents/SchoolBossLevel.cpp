#include "PrecompileHeader.h"
#include "SchoolBossLevel.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"

#include "BackGround.h"
#include "FieldDoor.h"
#include "BossIntroMovie.h"
#include "BossVersus.h"
#include "Fader.h"



//<텍스처 이름, 오프셋>
const std::vector<std::pair<std::string_view, float4>> SchoolBossLevel::BGInfoes =
{
	{"SchoolBossBG.png", float4{ 0.f, 0.f, 500.f }}
};

const std::string_view SchoolBossLevel::CollisionImageName = "SchoolBossColBG.png";

SchoolBossLevel::SchoolBossLevel()
{

}

SchoolBossLevel::~SchoolBossLevel()
{

}

void SchoolBossLevel::Start()
{
	FieldLevelBase::Start();
	LoadImgRes();

	CreatBackGrounds();
	CreateDoors();

	FieldLevelBase::SetPlayerStartPosition(float4{ -290.f, -205.f });

	//FieldLevelBase::OnTransView_ForDebug();
}



void SchoolBossLevel::LoadImgRes()
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	Dir.Move("SchoolBoss");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}
}

void SchoolBossLevel::CreatBackGrounds()
{
	const float4 LevelArea = ResourceHelper::GetTextureScale("SchoolBossBG.png") * RCGDefine::ResourceScaleConvertor;
	FieldLevelBase::Init(LevelArea, TileInfoData(100, 50));
	FieldLevelBase::CreateBackGrounds(BGInfoes);
	FieldLevelBase::CreateCollisionImage(CollisionImageName);
}

void SchoolBossLevel::CreateDoors()
{
	std::shared_ptr<FieldDoor> DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Normal);
	DoorPtr->Unlock(LevelNames::CrossTownLevel1);
}

void SchoolBossLevel::LevelChangeStart()
{
	FieldLevelBase::LevelChangeStart();

	CreateActor<BossIntroMovie>(UpdateOrder::UI)->Init(MovieType::School, [this]()
	{
		//BossIntroMovie 끝나고 페이드 까지는 맞는데, BossVersus UI 띄우는건 임시
		this->CreateActor<Fader>(UpdateOrder::UI)->Init(float4::Zero, 0.5f, [this]()
		{
			this->CreateActor<BossVersus>(static_cast<int>(UpdateOrder::UI))->Init(BossType::Misuzu);
		});
	});
}


