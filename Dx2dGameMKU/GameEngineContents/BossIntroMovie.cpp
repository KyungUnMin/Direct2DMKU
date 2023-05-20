#include "PrecompileHeader.h"
#include "BossIntroMovie.h"

#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

#include "RCGDefine.h"

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



void BossIntroMovie::Start()
{
	UIBase::Start();
	LoadSprites();
}


void BossIntroMovie::LoadSprites()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Video);

	for (size_t i = 0; i < MovieNames.size(); ++i)
	{
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName(MovieNames[i]).GetFullPath());
	}

	IsLoad = true;
}


void BossIntroMovie::Init(MovieType _MovieType)
{
	const std::string_view& MovieName = MovieNames[static_cast<size_t>(_MovieType)];
	
	std::shared_ptr<GameEngineUIRenderer> Sprite = CreateComponent<GameEngineUIRenderer>();
	AniCtrl = Sprite->CreateAnimation
	({
		.AnimationName = "Movie",
		.SpriteName = MovieName,
		.Loop = false
	});

	Sprite->ChangeAnimation("Movie");

	const float4& ScreenSize = GameEngineWindow::GetScreenSize();
	Sprite->GetTransform()->SetLocalScale(ScreenSize);
	Sprite->GetTransform()->AddLocalPosition(float4::Back);
}



void BossIntroMovie::Update(float _DelatTime)
{
	UIBase::Update(_DelatTime);

	if (false == AniCtrl->IsEnd())
		return;

	Death();
}