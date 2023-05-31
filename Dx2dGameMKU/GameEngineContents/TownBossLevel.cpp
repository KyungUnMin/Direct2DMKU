#include "PrecompileHeader.h"
#include "TownBossLevel.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"

#include "BackGround.h"
#include "FieldDoor.h"
#include "BossIntroMovie.h"
#include "Fader.h"
#include "BossVersus.h"


const std::vector<std::pair<std::string_view, float4>> TownBossLevel::BGInfoes =
{
	{"TownBossBG.png", float4{0.f, 0.f, 500.f}},
};

const std::string_view TownBossLevel::CollisionImageName = "TownBossColBG.png";

TownBossLevel::TownBossLevel()
{

}

TownBossLevel::~TownBossLevel()
{

}

void TownBossLevel::Start()
{
	FieldLevelBase::Start();
	LoadImgRes();

	CreateBackGrounds();
	CreateDoors();

	FieldLevelBase::SetPlayerStartPosition(float4::Zero);
}

void TownBossLevel::LoadImgRes()
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	Dir.Move("TownBoss");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}
}

void TownBossLevel::CreateBackGrounds()
{
	const float4 LevelArea = ResourceHelper::GetTextureScale("TownBossBG.png") * RCGDefine::ResourceScaleConvertor;
	FieldLevelBase::Init(LevelArea, TileInfoData());
	FieldLevelBase::CreateBackGrounds(BGInfoes);
	FieldLevelBase::CreateCollisionImage(CollisionImageName);
}

void TownBossLevel::CreateDoors()
{
	std::shared_ptr<FieldDoor> DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Normal);
	DoorPtr->Unlock(LevelNames::OceanLevel);
}


void TownBossLevel::LevelChangeStart()
{
	FieldLevelBase::LevelChangeStart();

	CreateActor<BossIntroMovie>(UpdateOrder::UI)->Init(MovieType::Town, [this]()
	{
		//BossIntroMovie 끝나고 페이드 까지는 맞는데, BossVersus UI 띄우는건 임시
		this->CreateActor<Fader>(UpdateOrder::UI)->Init(float4::Zero, 0.5f, [this]()
		{
			this->CreateActor<BossVersus>(static_cast<int>(UpdateOrder::UI))->Init(BossType::Yamada);
		});
	});
}