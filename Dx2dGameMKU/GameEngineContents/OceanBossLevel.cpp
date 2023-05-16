#include "PrecompileHeader.h"
#include "OceanBossLevel.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "BackGround.h"

const std::vector<std::pair<std::string_view, float4>> OceanBossLevel::BGInfoes =
{
	{"OceanBossBG.png", float4{0.f, 0.f, 500.f}},
};

const std::string_view OceanBossLevel::CollisionImageName = "OceanBossColBG.png";


OceanBossLevel::OceanBossLevel()
{

}

OceanBossLevel::~OceanBossLevel()
{

}

#include "GlichSideAttack.h"

void OceanBossLevel::Start()
{
	FieldLevelBase::Start();
	LoadImgRes();


	CreateBackGrounds();


	FieldLevelBase::SetPlayerStartPosition(float4{ 0.f, -200.f, -200.f });

	CreateActor<GlichSideAttack>()->GetTransform()->SetLocalPosition(float4::Up * 100.f);
}

void OceanBossLevel::LoadImgRes()
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	Dir.Move("OceanBoss");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}
}

void OceanBossLevel::CreateBackGrounds()
{
	const float4 LevelArea = ResourceHelper::GetTextureScale("OceanBossBG.png") * RCGDefine::ResourceScaleConvertor;
	FieldLevelBase::Init(LevelArea, TileInfoData());
	FieldLevelBase::CreateBackGrounds(BGInfoes);
	FieldLevelBase::CreateCollisionImage(CollisionImageName);
}
