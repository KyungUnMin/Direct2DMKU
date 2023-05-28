#include "PrecompileHeader.h"
#include "CopGrenade.h"

#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "DataMgr.h"

#include "FieldPlayer.h"

const std::string_view CopGrenade::Grenade_FileName = "Cop_Grenade.png";
const std::string_view CopGrenade::Explosion_FileName = "Cop_Grenade_Explosion.png";
const std::pair<int, int> CopGrenade::Grenade_CutFrame = {6, 3};
const std::pair<int, int> CopGrenade::Explosion_CutFrame = {4, 4};

const std::vector<std::string_view> CopGrenade::AniNames =
{
	"Throw",
	"Land",
	"Explosion"
};

CopGrenade::CopGrenade()
{

}

CopGrenade::~CopGrenade()
{

}


void CopGrenade::Start() 
{
	GameEngineActor::Start();

	Render = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	Render->GetTransform()->SetLocalScale(float4::One * 150.f);

	Collider = CreateComponent<GameEngineCollision>(CollisionOrder::EnemyAttack);
	Collider->GetTransform()->SetLocalScale(float4::One * 100.f);

	ImageLoad();
	CreateAnimation();
}

void CopGrenade::ImageLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Effect");
	Dir.Move("EnemyAttack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(Grenade_FileName).GetFullPath(), Grenade_CutFrame.first, Grenade_CutFrame.second);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(Explosion_FileName).GetFullPath(), Explosion_CutFrame.first, Explosion_CutFrame.second);
	IsLoad = true;
}

void CopGrenade::CreateAnimation() 
{
	size_t AniIndex = -1;

	AniIndex = static_cast<size_t>(State::Throw);
	Render->CreateAnimation
	({
		.AnimationName = AniNames[AniIndex],
		.SpriteName = Grenade_FileName,
		.Start = 6,
		.End = 13,
		.FrameInter = 0.05f,
		.Loop = true,
		});

	
	AniIndex = static_cast<size_t>(State::Land);
	Render->CreateAnimation
	({
		.AnimationName = AniNames[AniIndex],
		.SpriteName = Grenade_FileName,
		.Start = 0,
		.End = 5,
		.FrameInter = 0.08f,
		.Loop = false,
	});


	AniIndex = static_cast<size_t>(State::Explosion);
	Render->CreateAnimation
	({
		.AnimationName = AniNames[AniIndex],
		.SpriteName = Explosion_FileName,
		.FrameInter = 0.08f,
		.Loop = false,
	});


	size_t CurIndex = static_cast<size_t>(CurState);
	Render->ChangeAnimation(AniNames[CurIndex]);
}


void CopGrenade::Init(const float4& _ThrowDir)
{
	if ((float4::Right != _ThrowDir) && (float4::Left != _ThrowDir))
	{
		MsgAssert("CopGrenade�� �ʱ�ȭ�Ҷ� float4::Right �Ǵ� float4::Left ������ �ʱ�ȭ �ؾ��մϴ�");
		return;
	}

	const float CreateOffsetX = 80.f;
	GameEngineTransform* ThisTrans = GetTransform();
	ThrowDir = _ThrowDir;
	ThisTrans->AddLocalPosition(ThrowDir * CreateOffsetX);

	StartPos = ThisTrans->GetLocalPosition();
	DestPos = StartPos + (ThrowDir * MaxHorizon);
}


void CopGrenade::Update(float _DeltaTime) 
{
	GameEngineActor::Update(_DeltaTime);

	if (true == ThrowDir.IsZero())
	{
		MsgAssert("Init�Լ��� ȣ����� ���� �ʾҽ��ϴ�");
		return;
	}

	switch (CurState)
	{
	case CopGrenade::State::Throw:
		Update_Throw(_DeltaTime);
		break;
	case CopGrenade::State::Land:
		Update_Land();
		break;
	case CopGrenade::State::Explosion:
		Update_Explosion();
		break;
	}
}


void CopGrenade::Update_Throw(float _DeltaTime)
{
	float Ratio = GetLiveTime() / Duration;
	if (1.f < Ratio)
	{
		ChangeState(State::Land);
		return;
	}

	Update_ThrowHorizon(Ratio);
	Update_ThrowVertical(Ratio);
}

void CopGrenade::Update_ThrowHorizon(float _Ratio)
{
	GameEngineTransform* ThisTrans = GetTransform();
	float4 NextPos = float4::LerpClamp(StartPos, DestPos, _Ratio);
	ThisTrans->SetLocalPosition(NextPos);
}

void CopGrenade::Update_ThrowVertical(float _Ratio)
{
	//y = -6x^2 + 5x = (-6x + 5)x
	//(1, -1), (0, 0), (0.5f, 1)�� ������ ������ 2���� � �׷���
	float VerticalRatio = (-6.f * _Ratio + 5.f) * _Ratio;

	GameEngineTransform* RenderTrans = Render->GetTransform();
	float RenderOffset = PivotVertical + (MaxVertical * VerticalRatio);
	RenderTrans->SetLocalPosition(float4::Up * RenderOffset);
}




void CopGrenade::Update_Land()
{
	if (false == Render->IsAnimationEnd())
		return;

	ChangeState(State::Explosion);
	GameEngineTransform* RenderTrans = Render->GetTransform();
	RenderTrans->SetLocalScale(ExploRenderScale);
	RenderTrans->SetLocalPosition(float4::Up * ExploRenderScale.hy());

	std::shared_ptr<GameEngineCollision> PlayerCol = nullptr;
	PlayerCol = Collider->Collision(CollisionOrder::PlayerMain, ColType::SPHERE3D, ColType::SPHERE3D);
	if (nullptr == PlayerCol)
		return;

	FieldPlayer* PlayerPtr = dynamic_cast<FieldPlayer*>(PlayerCol->GetActor());
	if (nullptr == PlayerPtr)
	{
		MsgAssert("CollisionOrder::PlayerMain �浹 �׷쿡 �÷��̾ �ƴ� �ٸ� Actor�� �� �ֽ��ϴ�");
		return;
	}

	bool Result = PlayerPtr->OnDamage_Jaw();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}

void CopGrenade::Update_Explosion() 
{
	if (false == Render->IsAnimationEnd())
		return;

	Death();
}


void CopGrenade::ChangeState(CopGrenade::State _Next)
{
	CurState = _Next;
	size_t NextIndex = static_cast<size_t>(CurState);
	Render->ChangeAnimation(AniNames[NextIndex]);
}