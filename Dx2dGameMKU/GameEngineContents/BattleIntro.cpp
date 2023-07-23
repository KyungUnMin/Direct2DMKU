#include "PrecompileHeader.h"
#include "BattleIntro.h"

#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "SoundMgr.h"


const std::string_view BattleIntro::Ani_FileName = "BattleIntro";

BattleIntro::BattleIntro()
{

}

BattleIntro::~BattleIntro()
{

}

void BattleIntro::Start() 
{
	UIBase::Start();

	LoadImgRes();
	CreateAnimation();
}

void BattleIntro::LoadImgRes()
{
	if (nullptr != GameEngineSprite::Find(Ani_FileName))
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("UI");
	GameEnginePath Path = Dir.GetPlusFileName(Ani_FileName);
	GameEngineSprite::LoadFolder(Path.GetFullPath());
}

void BattleIntro::CreateAnimation()
{
	Render = CreateComponent<GameEngineUIRenderer>(FieldUIRenderOrder::BattleIntro);
	Render->CreateAnimation
	({
		.AnimationName = Ani_FileName,
		.SpriteName = Ani_FileName,
		.FrameInter = 0.07f,
		.Loop = false,
	});

	Render->SetAnimationStartEvent(Ani_FileName, 7, []()
	{
		SoundMgr::PlaySFX("BattleIntro.wav");
	});

	Render->GetTransform()->SetLocalScale(GameEngineWindow::GetScreenSize());
	Render->ChangeAnimation(Ani_FileName);
}

void BattleIntro::Update(float _DeltaTime) 
{
	UIBase::Update(_DeltaTime);

	if (false == Render->IsAnimationEnd())
		return;

	Death();
}
