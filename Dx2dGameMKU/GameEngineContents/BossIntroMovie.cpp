#include "PrecompileHeader.h"
#include "BossIntroMovie.h"

#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"

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
	const std::string_view& MovieName = MovieNames[static_cast<size_t>(_MovieType)];
	LoadSprite(MovieName);

	Render = CreateComponent<GameEngineUIRenderer>(FieldUIRenderOrder::BossIntro);
	Render->CreateAnimation
	({
		.AnimationName = MovieName,
		.SpriteName = MovieName,
		.Loop = false
	});

	Render->ChangeAnimation(MovieName);

	const float4& ScreenSize = GameEngineWindow::GetScreenSize();
	Render->GetTransform()->SetLocalScale(ScreenSize);
	Render->GetTransform()->AddLocalPosition(float4::Back);

	EndCallback = _EndCallback;
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


#include <GameEngineCore/GameEngineLevel.h>
#include "Fader.h"

void BossIntroMovie::Update(float _DelatTime)
{
	UIBase::Update(_DelatTime);

	if (false == Render->IsAnimationEnd())
		return;

	Clear();
	GetLevel()->CreateActor<Fader>(UpdateOrder::UI)->Init(float4::Zero);
}

void BossIntroMovie::Clear()
{
	Render->Off();
	Render->Death();
	Render = nullptr;

	for (const std::string& TexName : TexNames)
	{
		GameEngineTexture::UnLoad(TexName);
	}

	TexNames.clear();
	Death();
}