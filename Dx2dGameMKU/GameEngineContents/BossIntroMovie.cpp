#include "PrecompileHeader.h"
#include "BossIntroMovie.h"

#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "RCG_GameCore.h"
#include "RCGDefine.h"
#include "RCGEnums.h"
#include "KeyMgr.h"
#include "SoundMgr.h"

#include "SelfRenderer.h"


const std::vector<std::string_view> BossIntroMovie::MovieNames =
{
	"SchoolBossIntro",
	"CrossTownBossIntro",
	"OceanBossIntro"
};

BossIntroMovie::BossIntroMovie()
{

}

BossIntroMovie::~BossIntroMovie()
{

}


void BossIntroMovie::Init(MovieType _MovieType, std::function<void()> _EndCallback /*= nullptr*/)
{
	IsInit = true;

	const std::string_view& MovieName = MovieNames[static_cast<size_t>(_MovieType)];
	LoadSprite(MovieName);
	CreateAnimation(MovieName);

	EndCallback = _EndCallback;
	RCG_GameCore::SetCurGameState(GameState::IntroMovie);
	GameEngineLevel* Level = GetLevel();
	Level->GetCamera(static_cast<int>(RCG_CamNumType::Main))->Off();
	Level->GetCamera(static_cast<int>(RCG_CamNumType::UI))->Off();

	std::string_view SfxName = "";

	switch (_MovieType)
	{
	case MovieType::School:
		SfxName = "Bossintros_Misuzu.mp3";
		break;
	case MovieType::Town:
		SfxName = "Bossintros_Yamada.mp3";
		break;
	case MovieType::Ocean:
		SfxName = "Bossintros_Noize.mp3";
		break;
	}

	SoundMgr::BgmStop();
	Sfx = SoundMgr::PlaySFX(SfxName);
	Sfx.SetPause(false);
}


void BossIntroMovie::LoadSprite(const std::string_view& _MovieName)
{
	//스프라이트로 텍스처 로드
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Video);
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName(_MovieName).GetFullPath());

	//텍스처 이름 저장
	Dir.Move(_MovieName);
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	TexNames.resize(Files.size());

	for (size_t i = 0; i < Files.size(); ++i)
	{
		GameEnginePath Path(Files[i].GetFullPath());
		TexNames[i] = Path.GetFileName();
	}
}


void BossIntroMovie::CreateAnimation(const std::string_view& _MovieName)
{
	Render = CreateComponent<SelfRenderer>(FieldUIRenderOrder::BossIntro);
	Render->SetCamera(RCG_CamNumType::BossUI);
	Render->SetEnginePipe();

	Render->CreateAnimation
	({
		.AnimationName = _MovieName,
		.SpriteName = _MovieName,
		.Loop = false
	});

	Render->ChangeAnimation(_MovieName);

	const float4& ScreenSize = GameEngineWindow::GetScreenSize();
	Render->GetTransform()->SetLocalScale(ScreenSize);
	Render->GetTransform()->AddLocalPosition(float4::Back);
}



void BossIntroMovie::Update(float _DelatTime)
{
	UIBase::Update(_DelatTime);
	

	if (false == IsInit)
	{
		MsgAssert("초기화 함수(Init)를 호출시키지 않았습니다");
		return;
	}

	if (true == KeyMgr::IsDown(KeyNames::Esc) && 1.f < GetLiveTime())
	{
		DeleteThis();
		return;
	}

	bool IsPlaySFX = false;
	Sfx.isPlaying(&IsPlaySFX);
	if (false == IsPlaySFX)
	{
		Sfx.SetPause(true);
	}

	if (false == Render->IsAnimationEnd())
		return;

	DeleteThis();
}

void BossIntroMovie::DeleteThis()
{
	SoundMgr::PlaySFX("Bossintros_End.mp3").SetVolume(0.5f);

	RCG_GameCore::SetCurGameState(GameState::OnField);
	GameEngineLevel* Level = GetLevel();
	Level->GetCamera(static_cast<int>(RCG_CamNumType::Main))->On();
	Level->GetCamera(static_cast<int>(RCG_CamNumType::UI))->On();

	//페이드인 생성
	//GetLevel()->CreateActor<Fader>(UpdateOrder::UI)->Init(float4::Zero);

	if (nullptr != EndCallback)
	{
		EndCallback();
		EndCallback = nullptr;
	}

	Render->Off();
	Render->Death();
	Render = nullptr;

	for (const std::string& TexName : TexNames)
	{
		GameEngineTexture::UnLoad(TexName);
	}

	Sfx.Stop();
	TexNames.clear();
	this->Death();
}