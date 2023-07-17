#include "PrecompileHeader.h"
#include "OceanLevel.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "SoundMgr.h"

#include "BackGround.h"
#include "FieldDoor.h"

const std::vector<std::pair<std::string_view, float4>> OceanLevel::BGInfoes =
{
	{"OceanBG.png", float4{0.f, 0.f, 500.f}},
	{"OceanBoxBack.png", float4{-651.f, -12.f, -41.f}},
	{"OceanBoxFront.png", float4{-651.f, -12.f, -125.f}},
};

const std::string_view OceanLevel::CollisionImageName = "OceanColBG.png";

const std::vector<float4> OceanLevel::EnemySpawnPoses =
{
	float4{-850.f, 280.f},
	float4{290.f, -350.f},
	float4{850.f, -215.f},
	float4{-640.f, -12.f},
};



const std::vector<NpcCreateInfo> OceanLevel::NpcInfoes =
{
	{"WorkingFemaleC", float4{-1080.f, 18.f, 18.f}, true, true},
	{"CasualGirlC", float4{-553.f, 185.f, 185.f}, true, false},
	{"SchoolGirlA2", float4{-152.f, 152.f, 152.f}, false, false},
	{"CasualGirlB", float4{-102.f, 152.f, 152.f}, false, false},
	{"SchoolBoyE", float4{-38.f, 140.f, 140.f}, false, false},
	{"CasualBoyB", float4{0.f, 150.f, 150.f}, false, false},
	{"CasualBoyA", float4{53.f, 163.f, 163.f}, false, false},
	{"CasualBoyD", float4{115.f, 150.f, 150.f}, false, false},
	{"SchoolGirlB2", float4{200.f, 150.f, 150.f}, false, false},
	{"SchoolBoyF", float4{267.f, 150.f, 150.f}, false, false},
	{"CasualGirlD", float4{322.f, 163.f, 163.f}, false, false},
	{"SchoolGirlE", float4{365.f, 174.f, 174.f}, false, false},
};

OceanLevel::OceanLevel()
{

}

OceanLevel::~OceanLevel()
{

}

void OceanLevel::Start()
{
	FieldLevelBase::Start();
	LoadImgRes();

	CreateBackGrounds();
	CreateWaveRender();
	FieldLevelBase::SetDoorOpenFunc(std::bind(&OceanLevel::CreateDoor_ForDebug, this));
	CreateDoor();
	CreateEnemies();
	FieldLevelBase::CreateNpcs(NpcInfoes);

	FieldLevelBase::SetPlayerStartPosition(float4{ -1106.f, -187.f });

	//FieldLevelBase::OnTransView_ForDebug();
}







void OceanLevel::LoadImgRes()
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	Dir.Move("Ocean");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}
}


void OceanLevel::CreateBackGrounds()
{
	const float4 LevelArea = ResourceHelper::GetTextureScale("OceanBG.png") * RCGDefine::ResourceScaleConvertor;
	FieldLevelBase::Init(LevelArea, TileInfoData(100, 50));
	FieldLevelBase::CreateBackGrounds(BGInfoes);
	FieldLevelBase::CreateCollisionImage(CollisionImageName);

	//앞쪽 마켓 렌더
	const std::string_view MarketFileName = "OceanMarket.png";
	const float4 MarketPos = float4{ -79.f, -322.f, -462.f };
	std::shared_ptr<GameEngineSpriteRenderer> MarketRender = nullptr;
	MarketRender = GetBackGround()->CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	MarketRender->SetScaleToTexture(MarketFileName);
	MarketRender->ColorOptionValue.MulColor = float4{ 1.f, 1.f, 1.f, 0.5f };

	GameEngineTransform* MarketRenderTrans = MarketRender->GetTransform();
	float4 MarketScale = MarketRenderTrans->GetLocalScale();
	MarketRenderTrans->SetLocalScale(MarketScale * RCGDefine::ResourceScaleConvertor);
	MarketRenderTrans->SetLocalPosition(MarketPos);

}

void OceanLevel::CreateDoor_ForDebug()
{
	std::shared_ptr<FieldDoor> DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Normal);
	DoorPtr->Unlock(LevelNames::OceanBossLevel);
}

void OceanLevel::CreateDoor()
{
	std::shared_ptr<FieldDoor> DoorPtr = nullptr;
	DoorPtr = CreateActor<FieldDoor>(static_cast<int>(UpdateOrder::FieldDoor));
	DoorPtr->Init(DoorType::Shop, float4{ 0.f, 50.f, 50.f });
	DoorPtr->Unlock(LevelNames::Shop_StoreLevel);
	DoorPtr->GetTransform()->SetLocalPosition(float4{-430.f, 280.f, 280.f});
}


void OceanLevel::CreateEnemies()
{
	EnemySpawner& Spawner = FieldLevelBase::GetEnemySpawner();

	Spawner.SetCycleDuration(1.f, 3.f);
	Spawner.SetCycleMax(4);
	Spawner.OnCycleSpawn({
		EnemyType::Cop,
		EnemyType::Waver
		}, EnemySpawnPoses);
}



void OceanLevel::CreateWaveRender()
{
	const std::string_view FileName = "Ocean_WaveAni";
	const std::string_view AniName = "Wave";
	const float4 TexScale = { 932.f, 450.f, 1.f };


	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName(FileName).GetFullPath());

	std::shared_ptr<GameEngineSpriteRenderer> Render = nullptr;
	Render = GetBackGround()->CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = FileName,
		.Loop = true,
		});
	Render->ChangeAnimation(AniName);

	GameEngineTransform* WaveTrans = Render->GetTransform();
	WaveTrans->SetLocalScale(TexScale * RCGDefine::ResourceScaleConvertor);
	WaveTrans->SetLocalPosition(float4::Forward * 501.f);
}


void OceanLevel::LevelChangeStart()
{
	FieldLevelBase::LevelChangeStart();

	SoundMgr::ChangeBGM("OceanLevel.mp3");
}

void OceanLevel::LevelChangeEnd()
{
	FieldLevelBase::LevelChangeEnd();

	SoundMgr::BgmFadeOut(BgmFadeDuration);
}
