#include "PrecompileHeader.h"
#include "HUD.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "DataMgr.h"

HUD::HUD()
{

}

HUD::~HUD()
{

}

void HUD::Start()
{
	UIBase::Start();
	GetTransform()->AddLocalPosition(float4::Forward);

	LoadImageRes();
	CreateBackGround();
	CreateHealth();
}



void HUD::LoadImageRes()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	RCGDefine::LoadContentPath(ResType::Image, { "UI", "HUD" });
	IsLoad = true;
}



void HUD::CreateBackGround()
{
	std::shared_ptr<GameEngineSpriteRenderer> Sprite = CreateComponent<GameEngineSpriteRenderer>();
	Sprite->SetTexture("HUD_BG.png");

	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	Sprite->GetTransform()->SetLocalScale(ScreenSize);
}



void HUD::CreateHealth()
{
	const float4 Pivot = float4{-338.f, 322.f};
	const float4 BlockSize = float4{ 26.f, 24.f };
	const float OffsetX = 2.f;
	const size_t HealthCount = 25;

	HealthBlocks.resize(HealthCount, nullptr);
	for (size_t i = 0; i < HealthCount; ++i)
	{
		HealthBlocks[i] = CreateComponent<GameEngineSpriteRenderer>();
		HealthBlocks[i]->SetTexture("HUD_Health.png");
		HealthBlocks[i]->GetTransform()->SetLocalScale(BlockSize);

		float4 BlockOffset = float4::Right * (BlockSize.hx() + OffsetX) * static_cast<float>(i);
		HealthBlocks[i]->GetTransform()->SetLocalPosition(Pivot + BlockOffset);
	}
}

//#include "KeyMgr.h"

void HUD::Update(float _DeltaTime)
{
	/*if (true == KeyMgr::IsDown(KeyNames::DebugF2))
	{
		DataMgr::MinusPlayerHP(10);
	}*/

	int PlayerHP = DataMgr::GetPlayerHP();
	size_t RemainHpBlock = static_cast<size_t>((PlayerHP + 3) / 4);

	for (size_t i = 0; i < RemainHpBlock; ++i)
	{
		HealthBlocks[i]->On();
	}

	for (size_t i = RemainHpBlock; i < HealthBlocks.size(); ++i)
	{
		HealthBlocks[i]->Off();
	}
}