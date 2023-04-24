#include "PrecompileHeader.h"
#include "SchoolEntryLevel.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"

const std::string_view SchoolEntryLevel::MapImgName = "01_Detention_BG.png";
const float4 SchoolEntryLevel::MapScale = float4{ 672.f, 224.f } *3.f;

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
}

void SchoolEntryLevel::LoadImgRes()
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	Dir.Move("School_Entry");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}
}
