#include "PrecompileHeader.h"
#include "OceanBossLevel.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "RCG_GameCore.h"

#include "BackGround.h"
#include "Fader.h"
#include "BossVersus.h"
#include "BossIntroMovie.h"


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
	FieldLevelBase::SetPlayerStartPosition(float4{ -149.f, -223.f });


	CreateActor<GlichSideAttack>()->GetTransform()->SetLocalPosition(float4::Up * 100.f);

	//FieldLevelBase::OnTransView_ForDebug();
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
	FieldLevelBase::Init(LevelArea, TileInfoData(80, 50));
	FieldLevelBase::CreateBackGrounds(BGInfoes);
	FieldLevelBase::CreateCollisionImage(CollisionImageName);
}

void OceanBossLevel::LevelChangeStart()
{
	FieldLevelBase::LevelChangeStart();

	CreateActor<BossIntroMovie>(UpdateOrder::UI)->Init(MovieType::Ocean, [this]()
	{
		RCG_GameCore::SetCurGameState(GameState::OnlyFieldUI);

		//BossIntroMovie ������ ���̵� ������ �´µ�, BossVersus UI ���°� �ӽ�
		this->CreateActor<Fader>(UpdateOrder::UI)->Init(float4::Zero, 0.5f, [this]()
		{
			this->CreateActor<BossVersus>(static_cast<int>(UpdateOrder::UI))->Init(BossType::Noise);
		});
	});
}