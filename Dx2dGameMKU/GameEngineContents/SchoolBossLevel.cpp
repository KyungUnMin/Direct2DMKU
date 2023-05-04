#include "PrecompileHeader.h"
#include "SchoolBossLevel.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"
#include "FieldDoor.h"

//<�ؽ�ó �̸�, ������>
const std::vector<std::pair<std::string_view, float4>> SchoolBossLevel::BGInfoes =
{
	{"SchoolBossBG.png", float4{ 0.f, 0.f }}
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

	FieldLevelBase::SetPlayerStartPosition(float4{ -700.f, 0.f , 0.f });
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
	FieldLevelBase::InitLevelArea(LevelArea, TileInfoData());
	FieldLevelBase::CreateBackGrounds(BGInfoes);
	FieldLevelBase::CreateCollisionImage(CollisionImageName);
}

void SchoolBossLevel::CreateDoors()
{
	std::shared_ptr<FieldDoor> DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Normal);
	DoorPtr->Unlock(LevelNames::CrossTownLevel1);
}
