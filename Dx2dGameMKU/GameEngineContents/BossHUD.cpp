#include "PrecompileHeader.h"
#include "BossHUD.h"

#include <GameEngineBase/GameEngineTimeEvent.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "RCGDefine.h"
#include "RCGEnums.h"

#include "ShaderUIRenderer.h"
#include "Fader.h"

const std::string_view BossHUD::KoFileName = "BossKO";

const std::vector<std::string_view> BossHUD::FileNames =
{
	"RCG_bossmeter_background.png",
	"RCG_bossmeter_Hp.png",
	"RCG_bossmeter_frame.png",
};

const float BossHUD::SlowTimeRatio = 0.2f;				//5�� ��������
const float BossHUD::SlowComeBackTime = 0.1f;		//0.5��
const float BossHUD::KoRenderOffTime = 3.f;		

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



void BossHUD::ImageLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("UI");
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName(KoFileName).GetFullPath());

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


	{
		KoRender = CreateComponent<GameEngineUIRenderer>(FieldUIRenderOrder::BossHUD);
		KoRender->CreateAnimation
		({
			.AnimationName = KoFileName,
			.SpriteName = KoFileName,
			.FrameInter = 0.15f,
			.Loop = false,
		});

		KoRender->ChangeAnimation(KoFileName);
		KoRender->Off();

		GameEngineTransform* KoTrans = KoRender->GetTransform();
		KoTrans->SetWorldPosition(float4::Zero);
		KoTrans->SetLocalScale(GameEngineWindow::GetScreenSize());
	}
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




void BossHUD::SetHp(int _CurHp)
{
	//������ Hp����
	StartRatio = HpRatio.x;

	//������ Hp����
	DestRatio = static_cast<float>(_CurHp) / MaxHp;

	Timer = 0.f;

	//������ �ǰ� 0�� ��������
	if (0 != _CurHp)
		return;

	//������ �̹� KO������ �ߴٸ� return
	if (true == IsKo)
		return;

	IsKo = true;
	KoExcute();
}


void BossHUD::KoExcute()
{
	//�ð������� ������
	GameEngineTime::GlobalTime.SetGlobalTimeScale(SlowTimeRatio);

	//SlowComeBackTime�ð��� �帥�� �ð������� ����
	GetLevel()->TimeEvent.AddEvent(SlowComeBackTime, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)
	{
		GameEngineTime::GlobalTime.SetGlobalTimeScale(1.f);
		
		//������ ������ �� ��� ���̵� �ƿ�
		GetLevel()->CreateActor<Fader>(UpdateOrder::UI)->Init(float4::White, 0.5f, [this]()
		{
			//���̵� �ƿ��� ������ Ko ������ On
			KoRender->On();

			//KoRenderOffTimet�ð��� �帥 ���Ŀ� Ko������ Off
			GetLevel()->TimeEvent.AddEvent(KoRenderOffTime, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)
			{
				this->KoRender->Off();
			});
		});
	});

	
}
