#include "PrecompileHeader.h"
#include "NoiseFan.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "SoundMgr.h"

const std::string_view NoiseFan::Boy_FileName = "NoiseFanBoy.png";
const std::string_view NoiseFan::Girl_FileName = "NoiseFanGirl.png";
const std::string_view NoiseFan::BoyHurt_FileName = "NoiseFanBoy_Hurt.png";
const std::string_view NoiseFan::GirlHurt_FileName = "NoiseFanGirl_Hurt.png";

const std::vector<std::string_view> NoiseFan::EnumToString =
{
	"Climb",
	"Trace",
	"FlyAway",
	"Fall"
};

size_t NoiseFan::FanCount = 0;

const std::vector<std::string_view> NoiseFan::FemaleFanSfx =
{
	"NoiseFan_Female_Appear0.wav",
	"NoiseFan_Female_Appear1.wav",
	"NoiseFan_Female_Appear2.wav",
};

const std::vector<std::string_view> NoiseFan::MaleFanSfx =
{
	"NoiseFan_Male_Appear0.wav",
	"NoiseFan_Male_Appear1.wav",
	"NoiseFan_Male_Appear2.wav",
};



NoiseFan::NoiseFan()
{
	static bool Girl = true;
	IsZenderGirl = Girl;
	Girl = !Girl;

	++FanCount;
}

NoiseFan::~NoiseFan()
{
	--FanCount;
}



void NoiseFan::Start()
{
	FieldEnemyBase::Start();
	ImageLoad();
	CreateAnimation();
	SetStartHp(1);

	
	std::shared_ptr<GameEngineCollision> MainCollider = GetMainCollider();
	std::shared_ptr<GameEngineCollision> AttackCollider = GetAttackCollider();

	MainCollider->GetTransform()->SetLocalScale(float4::One * 200.f);
	AttackCollider->GetTransform()->SetLocalScale(float4::One * 50.f);
	MainCollider->Off();
	AttackCollider->Off();

	ChangeState(State::Climb);
	PlayAppearSFX();
}

void NoiseFan::ImageLoad() 
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("NoiseFan");

	const std::pair<int, int> CutFrm = { 5, 3 };
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(Boy_FileName).GetFullPath(), CutFrm.first, CutFrm.second);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(Girl_FileName).GetFullPath(), CutFrm.first, CutFrm.second);

	GameEngineTexture::Load(Dir.GetPlusFileName(BoyHurt_FileName).GetFullPath());
	GameEngineTexture::Load(Dir.GetPlusFileName(GirlHurt_FileName).GetFullPath());
}

void NoiseFan::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	const std::string_view& FileName = IsZenderGirl ? Girl_FileName : Boy_FileName;
	const float FrameInter = 0.06f;
	
	Render->CreateAnimation
	({
		.AnimationName = EnumToString[static_cast<size_t>(State::Climb)],
		.SpriteName = FileName,
		.Start = 0,
		.End = 3,
		.FrameInter = FrameInter,
		.Loop = false,
	});

	Render->CreateAnimation
	({
		.AnimationName = EnumToString[static_cast<size_t>(State::Trace)],
		.SpriteName = FileName,
		.Start = 5,
		.End = 10,
		.FrameInter = FrameInter,
		.Loop = true,
	});

}

void NoiseFan::ChangeState(State _Next)
{
	CurState = _Next;
	ResetLiveTime();

	if (State::Fall == CurState)
		return;

	if (State::FlyAway == CurState)
		return;

	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	size_t NextAniIndex = static_cast<size_t>(_Next);
	Render->ChangeAnimation(EnumToString[NextAniIndex]);
}

void NoiseFan::PlayAppearSFX()
{
	size_t RandNum = static_cast<size_t>(GameEngineRandom::MainRandom.RandomInt(0, 2));
	const std::string_view& SfxName = (true == IsZenderGirl) ? FemaleFanSfx[RandNum] : MaleFanSfx[RandNum];
	SoundMgr::PlaySFX(SfxName);
}


void NoiseFan::Update(float _DeltaTime)
{
	FieldEnemyBase::Update(_DeltaTime);

	switch (CurState)
	{
	case NoiseFan::State::Climb:
		Update_Climb(_DeltaTime);
		break;
	case NoiseFan::State::Trace:
		Update_Trace(_DeltaTime);
		break;
	case NoiseFan::State::FlyAway:
		Update_FlyAway(_DeltaTime);
		break;
	case NoiseFan::State::Fall:
		Update_Fall(_DeltaTime);
		break;
	}

	float Height = GetHeight();
	GameEngineTransform* RenderTrans = GetRenderer()->GetTransform();
	RenderTrans->SetLocalPosition(float4::Up * Height);
}


void NoiseFan::ChangeFlyState()
{
	if (State::Trace != CurState)
		return;

	OnDamage(1);

	GetMainCollider()->Off();
	GetAttackCollider()->Off();

	ChangeState(State::FlyAway);

	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	const std::string_view& HurtImgPath = IsZenderGirl ? GirlHurt_FileName : BoyHurt_FileName;
	Render->SetTexture(HurtImgPath);

	SoundMgr::PlaySFX("NoiseFan_GetHit.wav").SetVolume(3.f);
}