#include "PrecompileHeader.h"
#include "OceanBossLevel.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "RCG_GameCore.h"
#include "GUIManager.h"
#include "GameEngineActorGUI.h"
#include "SoundMgr.h"
#include "LevelMgr.h"

#include "BackGround.h"
#include "Fader.h"
#include "BossVersus.h"
#include "BossIntroMovie.h"
#include "FieldEnemy_Noise.h"
#include "LevelChangeHeart.h"


const std::vector<std::pair<std::string_view, float4>> OceanBossLevel::BGInfoes =
{
	{"OceanBossBG.png", float4{0.f, 0.f, 500.f}},
	{"OceanConcert_Sky.png", float4{0.f, 223.f, 500.5f}},
	{"OceanConcert_StageForeground.png", float4{0.f, 223.f, 499.9f}},
	{"OceanConcert_FenceLeft.png", float4{-632.f, -171.f, -171.f}},
	{"OceanConcert_FenceRIght.png", float4{632.f, -171.f, -171.f}},
};

const std::vector<std::string_view> OceanBossLevel::AniPathes =
{
	{"OceanConcert_FanClubLeft.png"},
	{"OceanConcert_FanClubRight.png"},
	{"OceanConcert_Guitar.png"},
	{"OceanConcert_Piano.png"},
	{"OceanConcert_Drum.png"},
};



const std::string_view OceanBossLevel::CollisionImageName = "OceanBossColBG.png";

const float4 OceanBossLevel::PlayerStartPos = float4{ -149.f, -223.f };

OceanBossLevel::OceanBossLevel()
{

}

OceanBossLevel::~OceanBossLevel()
{

}

void OceanBossLevel::Start()
{
	FieldLevelBase::Start();
	LoadImgRes();

	CreateBackGrounds();

	FieldLevelBase::SetPlayerStartPosition(float4{ -149.f, -223.f });
	float4 EnemyStartPos = { -PlayerStartPos.x,  PlayerStartPos.y, PlayerStartPos.y };

	std::shared_ptr<FieldEnemyBase> Boss = nullptr;
	Boss = GetEnemySpawner().CreateEnemy(EnemyType::Noise, EnemyStartPos);
	GetEnemySpawner().SetAllKillCallback([this]()
	{
		CreateActor<LevelChangeHeart>(UpdateOrder::UI)->Init(LevelNames::EndingLevel_Win);
	});

	Boss_Noise = std::dynamic_pointer_cast<FieldEnemy_Noise>(Boss);
	if (nullptr == Boss_Noise)
	{
		MsgAssert("보스Enemy를 Noise로 캐스팅하는데 실패하였습니다");
		return;
	}


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


	//팬클럽
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniPathes[0]).GetFullPath(), 1, 12);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniPathes[1]).GetFullPath(), 1, 12);

	//연주
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniPathes[2]).GetFullPath(), 4, 2);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniPathes[3]).GetFullPath(), 4, 2);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniPathes[4]).GetFullPath(), 4, 1);
}

void OceanBossLevel::CreateBackGrounds()
{
	const float4 LevelArea = ResourceHelper::GetTextureScale("OceanBossBG.png") * RCGDefine::ResourceScaleConvertor;
	FieldLevelBase::Init(LevelArea, TileInfoData(80, 50));
	FieldLevelBase::CreateBackGrounds(BGInfoes/*, BGInfoes.size() -1*/);
	FieldLevelBase::CreateCollisionImage(CollisionImageName);


	//애니메이션 정보<크기, 위치>
	const std::vector<std::pair<float4, float4>> AniTransInfo =
	{
		{float4{830.f, 725.f, 1.f},float4{-520.f, -160.f ,-160.f}},
		{float4{830.f, 725.f, 1.f},float4{520.f, -160.f ,-160.f}},
		{float4{400.f, 400.f, 1.f},float4{-259.f, 140.f, 140.f}},
		{float4{400.f, 400.f, 1.f},float4{259.f, 140.f, 140.f}},
		{float4{400.f, 400.f, 1.f},float4{0.f, 180.f, 180.f}},
	};

	if (AniTransInfo.size() != AniPathes.size())
	{
		MsgAssert("AniTransInfo와 AniPathes의 크기가 맞지 않습니다");
		return;
	}

	for (size_t i = 0; i < AniPathes.size(); ++i)
	{
		bool IsGui = (-1 == i);
		CreateAnimation(AniPathes[i], AniTransInfo[i].first, AniTransInfo[i].second, IsGui);
	}
}

void OceanBossLevel::CreateAnimation(const std::string_view& _AniPath, const float4& _Scale, const float4& _Pos, bool _GuiSelect)
{
	std::shared_ptr<BackGround> BGPtr = GetBackGround();
	std::shared_ptr<GameEngineSpriteRenderer> Render = nullptr;

	Render = BGPtr->CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	Render->CreateAnimation
	({
		.AnimationName = _AniPath,
		.SpriteName= _AniPath ,
		.Loop = true,
	});
	Render->ChangeAnimation(_AniPath);

	GameEngineTransform* RenderTrans = Render->GetTransform();
	RenderTrans->SetLocalScale(_Scale);
	RenderTrans->SetLocalPosition(_Pos);

	std::shared_ptr<GameEngineActorGUI> TransCtrlGUI = nullptr;
	if (false == _GuiSelect)
		return;

	TransCtrlGUI = GUIManager::CreateGui<GameEngineActorGUI>();
	TransCtrlGUI->SetTarget(RenderTrans);
}



void OceanBossLevel::LevelChangeStart()
{
	FieldLevelBase::LevelChangeStart();
	OffPhone();

	//보스 Movie
	CreateActor<BossIntroMovie>(UpdateOrder::UI)->Init(MovieType::Ocean, [this]()
	{
		RCG_GameCore::SetCurGameState(GameState::OnlyFieldUI);
	
		//Fade
		this->CreateActor<Fader>(UpdateOrder::UI)->Init(float4::Zero, 0.5f, [this]()
		{
			//Boss Vs
			SoundMgr::ChangeBGM("SchoolBossLevel.mp3");
	
			std::shared_ptr<BossVersus> VsUI = nullptr;
			VsUI = this->CreateActor<BossVersus>(static_cast<int>(UpdateOrder::UI));
			VsUI->Init(BossType::Noise);
			VsUI->SetCallBack([this]()
			{
				Boss_Noise->JumpForSing();
				OnPhone();
			});
		});
	});

	//임시
	//SoundMgr::ChangeBGM("SchoolBossLevel.mp3");
	//Boss_Noise->JumpForSing();
}