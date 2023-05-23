#include "PrecompileHeader.h"
#include "BossVersusState_Fire.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "RCGDefine.h"


#include "BossVersus.h"

const std::string_view BossVersusState_Fire::Light_FileName = "VersusPointLight.png";
const std::string_view BossVersusState_Fire::Fire_FileName = "VersusFire.png";

BossVersusState_Fire::BossVersusState_Fire()
{

}

BossVersusState_Fire::~BossVersusState_Fire()
{

}

void BossVersusState_Fire::Start()
{
	StateBase::Start();

	LoadFireAniSprite();
	CreateRenderers();
}

void BossVersusState_Fire::LoadFireAniSprite()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("UI");
	Dir.Move("Versus");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(Fire_FileName).GetFullPath(), 2, 2);
}

void BossVersusState_Fire::CreateRenderers()
{
	BossVersus* VersusUI = BossVersus::GetPtr();

	Light = VersusUI->CreateComponent<GameEngineUIRenderer>();
	Light->SetTexture(Light_FileName);

	const std::string_view FireAniName = "Fire";
	Fires.resize(20, nullptr);
	for (std::shared_ptr<GameEngineUIRenderer>& Fire : Fires)
	{
		Fire = VersusUI->CreateComponent<GameEngineUIRenderer>();
		Fire->CreateAnimation
		({
			.AnimationName = FireAniName,
			.SpriteName = Fire_FileName,
		});

		GameEngineTransform* FireTrans = Fire->GetTransform();
		float4 Offset = 
		{
			GameEngineRandom::MainRandom.RandomFloat(-FireArea.x, FireArea.x),
			GameEngineRandom::MainRandom.RandomFloat(-FireArea.y, FireArea.y) 
		};

		FireTrans->SetLocalScale(float4::One * 100.f);
		FireTrans->SetLocalPosition(Offset);

		Fire->ChangeAnimation(FireAniName);
		Fire->Off();
	}

}


void BossVersusState_Fire::EnterState()
{
	StateBase::EnterState();

	for (std::shared_ptr<GameEngineUIRenderer>& Fire : Fires)
	{
		Fire->On();
	}

	Light->On();
}


void BossVersusState_Fire::Update(float _DeltaTime)
{
	StateBase::Update(_DeltaTime);

	float Ratio = GetLiveTime() / LightDuration;
	float4 NowLightScale = float4::LerpClamp(float4::Zero, LightMaxScale, Ratio);
	Light->GetTransform()->SetLocalScale(NowLightScale);
}
