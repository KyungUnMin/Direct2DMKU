#include "PrecompileHeader.h"
#include "ShopLevelBase.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "KeyMgr.h"
#include "LevelMgr.h"
#include "SoundMgr.h"

#include "Fader.h"
#include "BackGround.h"

#include "HUD.h"
#include "ShopInfo.h"
#include "ShopItem_CursorBar.h"
#include "ShopSlotController.h"
#include "ShopUI_ResultText.h"

LevelNames ShopLevelBase::PrevLevel = LevelNames::OpeningLevel;
std::string ShopLevelBase::PrevLevelBgmName;
std::shared_ptr<class Fader> ShopLevelBase::LevelExitFade = nullptr;

ShopLevelBase::ShopLevelBase()
{

}

ShopLevelBase::~ShopLevelBase()
{

}

void ShopLevelBase::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);

	ImageResLoad();
	Cursor = CreateActor<ShopItem_CursorBar>(static_cast<int>(UpdateOrder::UI));
	SlotCtrl = CreateActor<ShopSlotController>(static_cast<int>(UpdateOrder::UI));
	Cursor->CreateItemDescRender();

	CreateActor<HUD>(UpdateOrder::UI)->UseShopMode();
	CreateActor<ShopInfo>(UpdateOrder::UI);
	ResultText = CreateActor<ShopUI_ResultText>(UpdateOrder::UI);
}


void ShopLevelBase::ImageResLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	Dir.Move("Shop");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}

	IsLoad = true;
}




void ShopLevelBase::CreateBackImage(const std::string_view& _BackImageName)
{
	std::shared_ptr<BackGround> BGPtr = CreateActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	BGPtr->CreateBackImage(_BackImageName, ScreenSize);
}



void ShopLevelBase::LevelChangeStart()
{
	GameEngineLevel::LevelChangeStart();

	if (nullptr != LevelExitFade)
	{
		LevelExitFade->Death();
		LevelExitFade = nullptr;
	}

	CreateActor<Fader>(static_cast<int>(UpdateOrder::UI))->Init(float4{0.f, 0.f, 0.f, 1.0f});

	PrevLevelBgmName = SoundMgr::GetCurBgmName();
	PrevLevelBgmPos = SoundMgr::GetBgmPos();
	SoundMgr::ChangeBGM("ShopBGM.mp3");
	SoundMgr::SetBgmPos(ThisBgmPos);
}

void ShopLevelBase::LevelChangeEnd()
{
	GameEngineLevel::LevelChangeEnd();

	Cursor->Reset();
	SlotCtrl->Reset();
	LevelTimer = 0.f;

	ThisBgmPos = SoundMgr::GetBgmPos();
	if (false == PrevLevelBgmName.empty())
	{
		SoundMgr::ChangeBGM(PrevLevelBgmName);
		SoundMgr::SetBgmPos(PrevLevelBgmPos);
	}
}


void ShopLevelBase::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);
	LevelTimer += _DeltaTime;

	if (false == KeyMgr::IsDown(KeyNames::Esc) || (LevelTimer < 1.f))
		return;

	if (nullptr != LevelExitFade)
		return;

	static const float FadeTime = 0.5f;

	LevelTimer = 0.f;
	SoundMgr::BgmFadeOut(FadeTime);
	LevelExitFade = CreateActor<Fader>(static_cast<int>(UpdateOrder::UI));
	LevelExitFade->Init(float4{ 0.f, 0.f, 0.f, 0.0f }, FadeTime, []()
	{
		LevelMgr::ChangeLevel(PrevLevel);
	});
	LevelExitFade->DontDestory();
}





