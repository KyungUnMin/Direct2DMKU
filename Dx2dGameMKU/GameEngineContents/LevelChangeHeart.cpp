#include "PrecompileHeader.h"
#include "LevelChangeHeart.h"

#include <GameEngineBase/GameEngineTimeEvent.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "RCG_GameCore.h"
#include "SoundMgr.h"
#include "LevelMgr.h"


#include "ShaderUIRenderer.h"
#include "FieldLevelBase.h"
#include "FieldPlayer.h"


const std::string_view LevelChangeHeart::TexName = "LevelChangeHeart.png";

LevelChangeHeart::LevelChangeHeart()
{

}

LevelChangeHeart::~LevelChangeHeart()
{

}


void LevelChangeHeart::Start() 
{
	UIBase::Start();

	LoadImageRes();
	CreateRender();

	PlayerMainCollider = FieldPlayer::GetPtr()->GetMainCollider();
	Off();
}


void LevelChangeHeart::LoadImageRes()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("UI");
	GameEngineTexture::Load(Dir.GetPlusFileName(TexName).GetFullPath());

	IsLoad = true;
}

void LevelChangeHeart::CreateRender()
{
	std::shared_ptr<ShaderUIRenderer> Render = CreateComponent<ShaderUIRenderer>(FieldUIRenderOrder::LevelChangeHeart);
	Render->SetMesh("Rect");
	Render->SetPipeLine(RCGDefine::GetPipeName(PipeType::LevelChangeHeart));
	Render->GetShaderResHelper().SetTexture(RCGDefine::EngineTexName, TexName);
	Render->GetShaderResHelper().SetConstantBufferLink("TextureUV", TextureUV);

	Render->GetTransform()->SetLocalScale(GameEngineWindow::GetScreenSize());
}


void LevelChangeHeart::Init(LevelNames _NextLevel, float _WaitTime /*= 6.f*/)
{
	std::shared_ptr<FieldLevelBase> Level = FieldLevelBase::GetPtr();

	Level->TimeEvent.AddEvent(_WaitTime, [this, Level](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)
	{
		On();
		ResetLiveTime();
		SoundMgr::BgmFadeOut(Duration);
		Level->OffPhone();
		PlayerMainCollider->Off();
	});

	Level->TimeEvent.AddEvent(_WaitTime + Duration - 1.f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)
	{
		SoundMgr::PlaySFX("LevelChangeHeart.wav");
	});

	NextLevel = static_cast<size_t>(_NextLevel);
}



void LevelChangeHeart::Update(float _DeltaTime)
{
	UIBase::Update(_DeltaTime);

	if (-1 == NextLevel)
	{
		MsgAssert("Init함수를 호출시켜주지 않았습니다");
		return;
	}

	

	float Ratio = GetLiveTime() / Duration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	float CosValue = cosf(ClampRatio * GameEngineMath::PIE * 0.5f);
	float NowScale = (CosValue * MaxScaleRatio);

	TextureUV.SizeX = NowScale;
	TextureUV.SizeY = NowScale;

	if (Ratio < 1.f)
		return;

	FieldLevelBase::GetPtr()->OnPhone(0.f);
	PlayerMainCollider->On();

	SoundMgr::BgmStop();
	LevelMgr::ChangeLevel(static_cast<LevelNames>(NextLevel));
}