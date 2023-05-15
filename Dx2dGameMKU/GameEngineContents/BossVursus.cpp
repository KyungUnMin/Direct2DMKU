#include "PrecompileHeader.h"
#include "BossVursus.h"

#include "RCGDefine.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

const std::string_view BossVursus::SchoolName_FileName			= "MISUZU_NAME.png";
const std::string_view BossVursus::SchoolPortrait_FileName		= "MisuzuPortrait.png";
const std::string_view BossVursus::OcenePortrait_FileName		= "NoisePortrait.png";
const std::string_view BossVursus::OceneName_FileName			= "NOIZE_NAME.png";
const std::string_view BossVursus::PlayerName_FileName			= "Player_Name.png";
const std::string_view BossVursus::PlayerPortrait_FileName		= "PlayerPortrait.png";

const std::string_view BossVursus::NameTag_FileName				= "VersusPortrait_NameTag.png";
const std::string_view BossVursus::VersusLogo_FileName			= "VS_LOGO.png";
const std::string_view BossVursus::CornerBlack_FileName			= "VursusPortrait_CornerBlack.png";
const std::string_view BossVursus::CornerPink_FileName			= "VursusPortrait_CornerPink.png";
const std::string_view BossVursus::TownName_FileName			= "YAMADA_NAME.png";
const std::string_view BossVursus::TownPortrait_FileName		= "YamadaPortrait.png";

const std::string_view BossVursus::PortraitPipeName = "Burn";
const std::string_view BossVursus::PortraitCBufferName = "NoiseFilter";


BossVursus::BossVursus()
{

}

BossVursus::~BossVursus()
{

}



void BossVursus::Start()
{
	UIBase::Start();

	LoadImages();
	CreateRenderers();
}


void BossVursus::LoadImages()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("UI");
	Dir.Move("Versus");

	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}

	IsLoad = true;
}



void BossVursus::CreateRenderers()
{
	const float4& ScreenSize = GameEngineWindow::GetScreenSize();

	SpriteRenders.resize(static_cast<size_t>(RenderType::COUNT));
	for (size_t i = 0; i < SpriteRenders.size(); ++i)
	{
		SpriteRenders[i] = CreateComponent<GameEngineSpriteRenderer>();
		//SpriteRenders[i]->Off();
	}

	PlayerPortrait = CreateComponent<GameEngineRenderer>();
	PlayerPortrait->SetPipeLine(PortraitPipeName);
	PlayerPortrait->GetShaderResHelper().SetConstantBufferLink(PortraitCBufferName, CBufferData);
	//PlayerPortrait->Off();

	BossPortrait = CreateComponent<GameEngineRenderer>();
	BossPortrait->SetPipeLine(PortraitPipeName);
	BossPortrait->GetShaderResHelper().SetConstantBufferLink(PortraitCBufferName, CBufferData);
	//BossPortrait->Off();
}




void BossVursus::Init(BossType _Boss)
{
	std::string_view BossName = "";
	std::string_view BossPortName = "";

	switch (_Boss)
	{
	case BossType::Misuzu:
		BossName = SchoolName_FileName;
		BossPortName = SchoolPortrait_FileName;
		break;
	case BossType::Yamada:
		BossName = TownName_FileName;
		BossPortName = TownPortrait_FileName;
		break;
	case BossType::Noise:
		BossName = OceneName_FileName;
		BossPortName = OcenePortrait_FileName;
		break;
	}

	std::shared_ptr<GameEngineSpriteRenderer> RenderPtr = nullptr;

	//코너 블랙
	RenderPtr = SpriteRenders[static_cast<size_t>(RenderType::LeftCornerBlack)];
	RenderPtr->SetScaleToTexture(CornerBlack_FileName);
	RenderPtr = SpriteRenders[static_cast<size_t>(RenderType::RightCornerBlack)];
	RenderPtr->SetScaleToTexture(CornerBlack_FileName);

	//코너 핑크
	RenderPtr = SpriteRenders[static_cast<size_t>(RenderType::LeftCornerPink)];
	RenderPtr->SetScaleToTexture(CornerPink_FileName);
	RenderPtr = SpriteRenders[static_cast<size_t>(RenderType::RightCornerPink)];
	RenderPtr->SetScaleToTexture(CornerPink_FileName);

	//플레이어 네임 태그
	RenderPtr = SpriteRenders[static_cast<size_t>(RenderType::PlayerNameTag)];
	RenderPtr->SetScaleToTexture(NameTag_FileName);

	//보스 네임 태그
	RenderPtr = SpriteRenders[static_cast<size_t>(RenderType::BossNameTag)];
	RenderPtr->SetScaleToTexture(NameTag_FileName);

	//플레이어 이름
	RenderPtr = SpriteRenders[static_cast<size_t>(RenderType::PlayerName)];
	RenderPtr->SetScaleToTexture(PlayerName_FileName);

	//보스 이름
	RenderPtr = SpriteRenders[static_cast<size_t>(RenderType::BossName)];
	RenderPtr->SetScaleToTexture(BossName);

	//VS 로고
	RenderPtr = SpriteRenders[static_cast<size_t>(RenderType::VersusLogo)];
	RenderPtr->SetScaleToTexture(VersusLogo_FileName);

	//플레이어 초상화
	PlayerPortrait->GetShaderResHelper().SetTexture(RCGDefine::EngineTexName, PlayerPortrait_FileName);
	const float4& PlayerPortScale = GameEngineTexture::Find(PlayerPortrait_FileName)->GetScale();
	PlayerPortrait->GetTransform()->SetLocalScale(PlayerPortScale);

	//보스 초상화
	BossPortrait->GetShaderResHelper().SetTexture(RCGDefine::EngineTexName, BossPortName);
	const float4& BossPortScale = GameEngineTexture::Find(BossPortName)->GetScale();
	PlayerPortrait->GetTransform()->SetLocalScale(BossPortScale);

	
	//테스트 코드 : 나중에 리소스에서 직접 스케일을 줄이자
	{
		for (size_t i = 0; i < SpriteRenders.size(); ++i)
		{
			GameEngineTransform* RenderTrans = SpriteRenders[i]->GetTransform();
			float4 RenderScale = RenderTrans->GetLocalScale();
			RenderTrans->SetLocalScale(RenderScale * 0.2f);
		}

		GameEngineTransform* PlayerRenderTrans = PlayerPortrait->GetTransform();
		GameEngineTransform* BossRenderTrans = BossPortrait->GetTransform();

		float4 PlayerRenderScale = PlayerRenderTrans->GetLocalScale();
		float4 BossRenderScale = BossRenderTrans->GetLocalScale();

		PlayerRenderTrans->SetLocalScale(PlayerRenderScale * 0.65f);
		BossRenderTrans->SetLocalScale(BossRenderScale * 0.65f);
	}
}




void BossVursus::Update(float _DeltaTime) 
{
	UIBase::Update(_DeltaTime);

	Timer += _DeltaTime;
	Update_FSM(_DeltaTime);
}

