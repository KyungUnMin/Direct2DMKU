#include "PrecompileHeader.h"
#include "SchoolBossLevel.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"

const std::string_view SchoolBossLevel::MapImgName = "SchoolBossBG.png";
const float4 SchoolBossLevel::MapScale = float4{ 923.f, 360.f } *RCGDefine::ResourceScaleConvertor;

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
	FieldLevelBase::SettingBackImg(MapImgName, MapScale);
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
