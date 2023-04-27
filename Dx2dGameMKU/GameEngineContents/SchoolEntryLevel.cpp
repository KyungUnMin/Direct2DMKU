#include "PrecompileHeader.h"
#include "SchoolEntryLevel.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"
#include "FieldDoor.h"

const std::string_view SchoolEntryLevel::MapImgName = "SchoolEntryBG.png";
const float4 SchoolEntryLevel::MapScale = float4{ 672.f, 224.f } *RCGDefine::ResourceScaleConvertor;

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
	FieldLevelBase::SettingBackImg(MapImgName, MapScale);

	CreateActor<FieldDoor>(static_cast<int>(Field_UpdateOrder::FieldDoor))->Unlock(LevelNames::SchoolBossLevel);
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


void SchoolEntryLevel::Update(float _DeltaTime)
{
	FieldLevelBase::Update(_DeltaTime);

}