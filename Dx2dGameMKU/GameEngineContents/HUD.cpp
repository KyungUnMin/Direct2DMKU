#include "PrecompileHeader.h"
#include "HUD.h"

//#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineFont.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "DataMgr.h"

#include "ShaderUIRenderer.h"
#include "UIFontRenderer.h"

HUD::MpDatas HUD::MpData;

HUD::HUD()
{

}

HUD::~HUD()
{

}

void HUD::Start()
{
	UIBase::Start();
	//GetTransform()->AddLocalPosition(float4::Forward);

	LoadImageRes();
	CreateBackGround();
	CreateHpBar();
	CreateMpBar();
	CreateMoneyText();
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
	std::shared_ptr<GameEngineUIRenderer> Sprite = CreateComponent<GameEngineUIRenderer>(FieldUIRenderOrder::HUD);
	Sprite->SetTexture("HUD_BG.png");

	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	Sprite->GetTransform()->SetLocalScale(ScreenSize);
}



void HUD::CreateHpBar()
{
	const float4 Pivot = float4{-338.f, 322.f};
	const float4 BlockSize = float4{ 26.f, 24.f };
	const float OffsetX = 2.f;
	const size_t HealthCount = 25;

	HealthBlocks.resize(HealthCount, nullptr);
	for (size_t i = 0; i < HealthCount; ++i)
	{
		HealthBlocks[i] = CreateComponent<GameEngineUIRenderer>(FieldUIRenderOrder::HUD);
		HealthBlocks[i]->SetTexture("HUD_Health.png");
		HealthBlocks[i]->GetTransform()->SetLocalScale(BlockSize);

		float4 BlockOffset = float4::Right * (BlockSize.hx() + OffsetX) * static_cast<float>(i);
		BlockOffset.z = -1.f;
		HealthBlocks[i]->GetTransform()->SetLocalPosition(Pivot + BlockOffset);
	}
}

void HUD::CreateMpBar()
{
	const float4 BarScale = float4{ 360.f, 18.f };
	const float4 Offset = float4{ -168.f, 294.f , -1.f};

	std::shared_ptr<ShaderUIRenderer> MpBar = CreateComponent<ShaderUIRenderer>(FieldUIRenderOrder::HUD);
	MpBar->SetMesh("Rect");
	MpBar->SetPipeLine(RCGDefine::GetPipeName(PipeType::MpBar));
	MpBar->GetShaderResHelper().SetTexture(RCGDefine::EngineTexName, "HUD_MpBar.png");
	MpBar->GetShaderResHelper().SetConstantBufferLink("MpRatio", HUD::MpData);

	GameEngineTransform* MpTrans = MpBar->GetTransform();
	MpTrans->SetLocalScale(BarScale);
	MpTrans->SetLocalPosition(Offset);
}


void HUD::CreateMoneyText()
{
	const float4 TextPos = float4{ -220.f, 280.f };
	const std::string_view FontName = "휴먼둥근헤드라인";


	if (nullptr == GameEngineFont::Find(FontName))
	{
		GameEngineFont::Load(FontName);
	}

	MoneyText = CreateComponent<UIFontRenderer>(FieldUIRenderOrder::HUD);
	MoneyText->SetFont(FontName);
	MoneyText->SetScale(20.f);
	MoneyText->SetText("0");
	MoneyText->SetColor(float4::White);
	MoneyText->SetFontFlag(FW1_TEXT_FLAG::FW1_RIGHT);

	MoneyText->GetTransform()->SetLocalPosition(TextPos);
}




void HUD::Update(float _DeltaTime)
{
	UIBase::Update(_DeltaTime);

	Update_Hp();
	Update_Mp(_DeltaTime);
	Update_Money();
}

void HUD::Update_Hp()
{
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


//이거 맘에 안들면 속도에 따라 감속하는 방식으로 바꾸자
void HUD::Update_Mp(float _DeltaTime)
{
	const float Duration = 0.25f;

	int NowMp = DataMgr::GetPlayerMP();
	if (NowMp != MpData.DestMp)
	{
		MpData.PrevMpRatio = MpData.NowMpRatio;
		MpData.DestMpRatio = static_cast<float>(NowMp) / DataMgr::PlayerFullPoint;
		MpData.DestMp = NowMp;
		Timer = 0.f;
	}

	Timer += _DeltaTime;
	float TimeRatio = (Timer / Duration);
	TimeRatio = std::clamp(TimeRatio, 0.f, 1.f);

	MpData.NowMpRatio = (MpData.PrevMpRatio * (1.f - TimeRatio)) + (MpData.DestMpRatio * TimeRatio);
}


void HUD::Update_Money()
{
	int Money = DataMgr::GetPlayerMoney();
	MoneyText->SetText(GameEngineString::ToString(Money));
}