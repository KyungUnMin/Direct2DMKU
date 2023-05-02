#include "PrecompileHeader.h"
#include "SchoolEntryLevel.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"
#include "FieldDoor.h"


const float4 SchoolEntryLevel::LevelAreaScale = float4{ 672.f, 224.f } *RCGDefine::ResourceScaleConvertor;

SchoolEntryLevel::SchoolEntryLevel()
{

}

SchoolEntryLevel::~SchoolEntryLevel()
{

}

#include "GlichSideAttack.h"
#include "BurnExample.h"

void SchoolEntryLevel::Start()
{

	FieldLevelBase::Start();

	LoadImgRes();
	CreateBackGrounds();
	CreateDoors();

	CreateActor<GlichSideAttack>()->GetTransform()->SetLocalPosition(float4::Up * 100.f);
	CreateActor<BurnExample>()->GetTransform()->SetLocalPosition(float4::Up * 100.f);
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
	FieldLevelBase::InitLevelArea(LevelAreaScale, TileInfoData(100, 40));
	FieldLevelBase::GetBG()->CreateBackImage("SchoolEntryBG.png", LevelAreaScale);
}


void SchoolEntryLevel::CreateDoors()
{
	std::shared_ptr<FieldDoor> DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Normal);
	DoorPtr->Unlock(LevelNames::SchoolBossLevel);
	DoorPtr->GetTransform()->SetLocalPosition(float4{ 100.f, 100.f });
}


