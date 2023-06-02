#include "PrecompileHeader.h"
#include "BossVersus.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>


#include "RCGDefine.h"

//#include "ShaderUIRenderer.h"
#include "SelfRenderer.h"


BossVersus* BossVersus::GPtr = nullptr;

BossVersus* BossVersus::GetPtr()
{
	if (nullptr == GPtr)
	{
		MsgAssert("BossVersusUI를 생성해준 적이 없습니다");
		return nullptr;
	}

	return GPtr;
}

const std::string_view BossVersus::PlayerPortrait_FileName		= "PlayerPortrait.png";
const std::string_view BossVersus::SchoolPortrait_FileName		= "MisuzuPortrait.png";
const std::string_view BossVersus::TownPortrait_FileName		= "YamadaPortrait.png";
const std::string_view BossVersus::OcenePortrait_FileName		= "NoisePortrait.png";

const std::string_view BossVersus::PlayerName_FileName			= "Player_Name.png";
const std::string_view BossVersus::SchoolName_FileName			= "MISUZU_NAME.png";
const std::string_view BossVersus::TownName_FileName			= "YAMADA_NAME.png";
const std::string_view BossVersus::OceneName_FileName			= "NOIZE_NAME.png";

const std::string_view BossVersus::PortraitPipeName = "Burn";
const std::string_view BossVersus::PortraitCBufferName = "NoiseFilter";



//
//const std::string_view BossVersus::NameTag_FileName				= "VersusPortrait_NameTag.png";
//const std::string_view BossVersus::VersusLogo_FileName			= "VS_LOGO.png";






BossVersus::BossVersus()
{
	GPtr = this;
}

BossVersus::~BossVersus()
{
	if (this == GPtr)
	{
		GPtr = nullptr;
	}
}




void BossVersus::Init(BossType _Boss)
{
	//이미지 로드
	LoadImages();
	//렌더 생성
	CreatePortraits(_Boss);

	Fsm.Init(this);
}



void BossVersus::LoadImages()
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


void BossVersus::CreatePortraits(BossType _Boss)
{
	//플레이어 초상화
	PlayerPortrait = CreateComponent<SelfRenderer>(BossVersusUIRenderOrder::Portrait);
	PlayerPortrait->SetCamera(RCG_CamNumType::BossVersusUI);
	PlayerPortrait->SetPipeLine(PortraitPipeName);
	PlayerPortrait->GetShaderResHelper().SetConstantBufferLink(PortraitCBufferName, CBufferData);

	//보스 초상화
	BossPortrait = CreateComponent<SelfRenderer>(BossVersusUIRenderOrder::Portrait);
	BossPortrait->SetCamera(RCG_CamNumType::BossVersusUI);
	BossPortrait->SetPipeLine(PortraitPipeName);
	BossPortrait->GetShaderResHelper().SetConstantBufferLink(PortraitCBufferName, CBufferData);



	std::string_view BossPortName = "";

	switch (_Boss)
	{
	case BossType::Misuzu:
		BossPortName = SchoolPortrait_FileName;
		break;
	case BossType::Yamada:
		BossPortName = TownPortrait_FileName;
		break;
	case BossType::Noise:
		BossPortName = OcenePortrait_FileName;
		break;
	}


	//플레이어 초상화
	PlayerPortrait->GetShaderResHelper().SetTexture(RCGDefine::EngineTexName, PlayerPortrait_FileName);
	const float4& PlayerPortScale = GameEngineTexture::Find(PlayerPortrait_FileName)->GetScale();
	PlayerPortrait->GetTransform()->SetLocalScale(PlayerPortScale);

	//보스 초상화
	BossPortrait->GetShaderResHelper().SetTexture(RCGDefine::EngineTexName, BossPortName);
	const float4& BossPortScale = GameEngineTexture::Find(BossPortName)->GetScale();
	BossPortrait->GetTransform()->SetLocalScale(BossPortScale);
}

void BossVersus::CreateNameRenders(BossType _Boss)
{
	std::string_view BossName = "";

	switch (_Boss)
	{
	case BossType::Misuzu:
		BossName = SchoolName_FileName;
		break;
	case BossType::Yamada:
		BossName = TownName_FileName;
		break;
	case BossType::Noise:
		BossName = OceneName_FileName;
		break;
	}

	std::shared_ptr<SelfRenderer> PlayerNameRender = CreateComponent<SelfRenderer>(BossVersusUIRenderOrder::Name);
	std::shared_ptr<SelfRenderer> BossNameRender = CreateComponent<SelfRenderer>(BossVersusUIRenderOrder::Name);

	PlayerNameRender->SetCamera(RCG_CamNumType::BossVersusUI);
	BossNameRender->SetCamera(RCG_CamNumType::BossVersusUI);

	PlayerNameRender->SetEnginePipe();
	BossNameRender->SetEnginePipe();

	PlayerNameRender->SetScaleToTexture(PlayerName_FileName);
	BossNameRender->SetScaleToTexture(BossName);

	//TODO 자식으로 넣기
}




void BossVersus::Update(float _DeltaTime) 
{
	UIBase::Update(_DeltaTime);

	Update_PortShader(_DeltaTime);
	Fsm.Update(_DeltaTime);
}


void BossVersus::Update_PortShader(float _DeltaTime)
{
	const float Duration = 2.0f;

	float LiveTime = GetLiveTime();
	if (Duration < LiveTime)
	{
		CBufferData.NoiseFilterValue = 1.f;
		return;
	}

	float Ratio = (LiveTime / Duration);
	Ratio = std::clamp(Ratio, 0.0f, 1.f);

	//치역 0 ~ 1
	float SinValue = sinf(GameEngineMath::PIE * Ratio * 0.5f);
	CBufferData.NoiseFilterValue = SinValue;
}