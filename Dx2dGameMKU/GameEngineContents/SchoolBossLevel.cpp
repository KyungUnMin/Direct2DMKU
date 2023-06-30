#include "PrecompileHeader.h"
#include "SchoolBossLevel.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "RCG_GameCore.h"
#include "SoundMgr.h"

#include "BackGround.h"
#include "FieldDoor.h"
#include "BossIntroMovie.h"
#include "BossVersus.h"
#include "Fader.h"
#include "EnemySpawner.h"


//<�ؽ�ó �̸�, ������>
const std::vector<std::pair<std::string_view, float4>> SchoolBossLevel::BGInfoes =
{
	{"SchoolBossBG.png", float4{ 0.f, 0.f, 500.f }}
};

const std::string_view SchoolBossLevel::CollisionImageName = "SchoolBossColBG.png";

const float4 SchoolBossLevel::PlayerStartPos = float4{ -290.f, -205.f };

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

	FieldLevelBase::SetPlayerStartPosition(PlayerStartPos);
	float4 EnemyStartPos = { -PlayerStartPos.x,  PlayerStartPos.y, PlayerStartPos.y };
	GetEnemySpawner().CreateEnemy(EnemyType::Misuzu, EnemyStartPos);

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
		RCG_GameCore::SetCurGameState(GameState::OnlyFieldUI);
		SoundMgr::ChangeBGM("SchoolBossLevel.mp3");

		//BossIntroMovie ������ ���̵� ������ �´µ�, BossVersus UI ���°� �ӽ�
		this->CreateActor<Fader>(UpdateOrder::UI)->Init(float4::Zero, 0.5f, [this]()
		{
			this->CreateActor<BossVersus>(static_cast<int>(UpdateOrder::UI))->Init(BossType::Misuzu);
		});
	});

}


