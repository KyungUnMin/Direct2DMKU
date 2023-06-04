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

const float BossHUD::SlowTimeRatio = 0.2f;				//5배 느려진다
const float BossHUD::SlowComeBackTime = 0.1f;		//0.5초
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
		MsgAssert("최대 체력이 음수입니다.\n Init함수를 호출시켜주세요");
		return;
	}

	//이전프레임에서 이미 Duratino을 넘겼다면 return
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
	//변경전 Hp비율
	StartRatio = HpRatio.x;

	//변경후 Hp비율
	DestRatio = static_cast<float>(_CurHp) / MaxHp;

	Timer = 0.f;

	//보스의 피가 0이 됐을때만
	if (0 != _CurHp)
		return;

	//이전에 이미 KO연출을 했다면 return
	if (true == IsKo)
		return;

	IsKo = true;
	KoExcute();
}


void BossHUD::KoExcute()
{
	//시간스케일 느리게
	GameEngineTime::GlobalTime.SetGlobalTimeScale(SlowTimeRatio);

	//SlowComeBackTime시간이 흐른후 시간스케일 복귀
	GetLevel()->TimeEvent.AddEvent(SlowComeBackTime, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)
	{
		GameEngineTime::GlobalTime.SetGlobalTimeScale(1.f);
		
		//스케일 복귀할 때 흰색 페이드 아웃
		GetLevel()->CreateActor<Fader>(UpdateOrder::UI)->Init(float4::White, 0.5f, [this]()
		{
			//페이드 아웃이 끝나면 Ko 렌더러 On
			KoRender->On();

			//KoRenderOffTimet시간이 흐른 이후에 Ko렌더러 Off
			GetLevel()->TimeEvent.AddEvent(KoRenderOffTime, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)
			{
				this->KoRender->Off();
			});
		});
	});

	
}
