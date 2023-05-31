#include "PrecompileHeader.h"
#include "FieldNPCBase.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "RCGEnums.h"
#include "RCGDefine.h"
#include "FieldPlayer.h"


const std::string_view FieldNPCBase::IdleAniName = "Idle";
const std::string_view FieldNPCBase::ReactAniName = "React";
const float4 FieldNPCBase::RenderScale = float4{ 32.f, 80.f, 1.f } *RCGDefine::ResourceScaleConvertor;


FieldNPCBase::FieldNPCBase()
{

}

FieldNPCBase::~FieldNPCBase()
{

}


void FieldNPCBase::Start() 
{
	FieldActorBase::Start();

	FieldActorBase::CreateColliders(CollisionOrder::NPC);
	GetRenderer()->GetTransform()->SetLocalScale(RenderScale);
}


void FieldNPCBase::AnimationCreate(const std::string_view& _NpcFolderName)
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("NPC");
	Dir.Move(_NpcFolderName);

	GameEnginePath IdleSheetPath = Dir.GetPlusFileName(IdleAniName);
	GameEnginePath ReactSheetPath = Dir.GetPlusFileName(ReactAniName);

	if (nullptr == GameEngineSprite::Find(IdleAniName))
	{
		GameEngineSprite::LoadFolder(IdleSheetPath.GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find(ReactAniName))
	{
		GameEngineSprite::LoadFolder(ReactSheetPath.GetFullPath());
	}

	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	//Idle애니메이션
	Render->CreateAnimation
	({
		.AnimationName = IdleAniName,
		.SpriteName = IdleAniName,
		.Loop = true,
		});

	Render->CreateAnimation
	({
		.AnimationName = ReactAniName,
		.SpriteName = ReactAniName,
		.Loop = true,
		});

	Render->ChangeAnimation(IdleAniName);
}


void FieldNPCBase::Update(float _DeltaTime)
{
	FieldActorBase::Update(_DeltaTime);

	//렌더러 오프셋 조정
	Update_RenderOffset();
	
	switch (CurState)
	{
	case FieldNPCBase::State::Idle:
		Update_Idle(_DeltaTime);
		break;
	case FieldNPCBase::State::React:
		Update_React(_DeltaTime);
		break;
	}
}



void FieldNPCBase::Update_RenderOffset()
{
	GameEngineTransform* RenderTrans = GetRenderer()->GetTransform();

	float4 RenderScale = RenderTrans->GetLocalScale();
	RenderTrans->SetLocalPosition(float4::Up * RenderScale.hy());
}



void FieldNPCBase::Update_Idle(float _DeltaTime)
{

}



void FieldNPCBase::React()
{
	//이미 React 중일때는 return
	if (State::React == CurState)
		return;

	GameEngineTransform* PlayerTrans = FieldPlayer::GetPtr()->GetTransform();
	GameEngineTransform* ThisTrans = GetTransform();

	float4 PlayerPos = PlayerTrans->GetWorldPosition();
	float4 ThisPos = ThisTrans->GetWorldPosition();

	float4 DirToPlayer = (PlayerPos - ThisPos);

	//플레이어 바라보기
	if (0.f < DirToPlayer.x)
	{
		ThisTrans->SetLocalPositiveScaleX();
	}
	else
	{
		ThisTrans->SetLocalNegativeScaleX();
	}

	CurState = State::React;
	GetRenderer()->ChangeAnimation(ReactAniName);
}



void FieldNPCBase::Update_React(float _DeltaTime) 
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetRenderer()->ChangeAnimation(IdleAniName);
	CurState = State::Idle;
}


