#include "PrecompileHeader.h"
#include "ShopLevelBase.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "KeyMgr.h"
#include "BackGround.h"
#include "LevelMgr.h"
#include "Fader.h"
#include "ShopItem_CursorBar.h"
#include "HUD.h"
#include "ShopInfo.h"

LevelNames ShopLevelBase::PrevLevel = LevelNames::OpeningLevel;

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
	CreateActor<ShopItem_CursorBar>(static_cast<int>(UpdateOrder::UI));
	CreateActor<HUD>(static_cast<int>(UpdateOrder::UI));
	CreateActor<ShopInfo>(static_cast<int>(UpdateOrder::UI));
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

	CreateActor<Fader>()->Init(float4{ 0.f, 0.f, 0.f, 1.0f });
}


void ShopLevelBase::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);

	if (false == KeyMgr::IsDown(KeyNames::Esc))
		return;

	LevelMgr::ChangeLevel(PrevLevel);
}





