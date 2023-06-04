#include "PrecompileHeader.h"
#include "BossHUD.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

#include "RCGDefine.h"
#include "RCGEnums.h"

#include "ShaderUIRenderer.h"



const std::vector<std::string_view> BossHUD::FileNames =
{
	"RCG_bossmeter_background.png",
	"RCG_bossmeter_Hp.png",
	"RCG_bossmeter_frame.png",
};

BossHUD::BossHUD()
{

}

BossHUD::~BossHUD()
{

}


void BossHUD::Start()
{
	UIBase::Start();

	ImageLoad();
	CreateRenders();
}


void BossHUD::SetHp(int _CurHp)
{
	//������ Hp����
	StartRatio = HpRatio.x;

	//������ Hp����
	DestRatio = static_cast<float>(_CurHp) / MaxHp;

	Timer = 0.f;
}



void BossHUD::Update(float _DeltaTime)
{
	UIBase::Update(_DeltaTime);

	if (MaxHp <= 0.f)
	{
		MsgAssert("�ִ� ü���� �����Դϴ�.\n Init�Լ��� ȣ������ּ���");
		return;
	}

	//���������ӿ��� �̹� Duratino�� �Ѱ�ٸ� return
	if (Duration < Timer)
		return;

	Timer += _DeltaTime;
	float TimeRatio = (Timer / Duration);
	TimeRatio = std::clamp(TimeRatio, 0.f, 1.f);
	float SinValue = sinf(GameEngineMath::PIE * 0.5f * TimeRatio);

	float NowRatio = (StartRatio * (1.f - SinValue)) + (DestRatio * SinValue);
	HpRatio.x = NowRatio;
}


void BossHUD::ImageLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("UI");
	Dir.Move("BossHUD");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}
}

enum class RenderName
{
	Background = 0,
	Hp,
	Frame
};


void BossHUD::CreateRenders()
{
	{
		std::shared_ptr<GameEngineUIRenderer> Render = nullptr;
		Render = CreateComponent<GameEngineUIRenderer>(FieldUIRenderOrder::BossHUD);
		const std::string_view& TexName = FileNames[static_cast<size_t>(RenderName::Background)];
		Render->SetScaleToTexture(TexName);
	}


	{
		std::shared_ptr<ShaderUIRenderer> Render = nullptr;
		Render = CreateComponent<ShaderUIRenderer>(FieldUIRenderOrder::BossHUD);
		Render->SetMesh("Rect");
		Render->SetPipeLine(RCGDefine::GetPipeName(PipeType::MpBar));
		Render->GetShaderResHelper().SetConstantBufferLink("MpRatio", HpRatio);

		const std::string_view& TexName = FileNames[static_cast<size_t>(RenderName::Hp)];
		Render->SetScaleToTexture(TexName);
		Render->GetTransform()->AddLocalPosition(float4::Left * 70.f);
	}


	{
		std::shared_ptr<GameEngineUIRenderer> Render = nullptr;
		Render = CreateComponent<GameEngineUIRenderer>(FieldUIRenderOrder::BossHUD);
		const std::string_view& TexName = FileNames[static_cast<size_t>(RenderName::Frame)];
		Render->SetScaleToTexture(TexName);
	}
}


