#include "PrecompileHeader.h"
#include "FieldNPCBase.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "RCGEnums.h"
#include "RCGDefine.h"
#include "FieldPlayer.h"


const std::string_view FieldNPCBase::IdleAniName = "Idle";
const std::string_view FieldNPCBase::ReactAniName = "React";


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
}


void FieldNPCBase::AnimationCreate(const std::string_view& _NpcFolderName)
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("NPC");
	Dir.Move(_NpcFolderName);

	//TODO
	Dir.GetPlusFileName(IdleAniName);

	if (nullptr == GameEngineSprite::Find(IdleAniName) && nullptr == GameEngineSprite::Find(ReactAniName))
	{
		
		
		//GameEngineSprite::LoadFolder()

	}


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


