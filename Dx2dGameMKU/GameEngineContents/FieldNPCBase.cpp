#include "PrecompileHeader.h"
#include "FieldNPCBase.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "RCGEnums.h"
#include "RCGDefine.h"
#include "FieldPlayer.h"


const std::string FieldNPCBase::IdleAniName = "_Idle";
const std::string FieldNPCBase::ReactAniName = "_React";
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

	std::string FolderName = _NpcFolderName.data();

	//Sprite이름이자 폴더 이름
	std::string IdleSpriteName = FolderName + IdleAniName;
	std::string ReactSpriteName = FolderName + ReactAniName;
	
	GameEnginePath IdleSheetPath = Dir.GetPlusFileName(IdleSpriteName);
	GameEnginePath ReactSheetPath = Dir.GetPlusFileName(ReactSpriteName);

	if (nullptr == GameEngineSprite::Find(IdleSpriteName))
	{
		GameEngineSprite::LoadFolder(IdleSheetPath.GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find(ReactSpriteName))
	{
		GameEngineSprite::LoadFolder(ReactSheetPath.GetFullPath());
	}

	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	//Idle애니메이션
	Render->CreateAnimation
	({
		.AnimationName = IdleAniName,
		.SpriteName = IdleSpriteName,
		.Loop = true,
		});

	Render->CreateAnimation
	({
		.AnimationName = ReactAniName,
		.SpriteName = ReactSpriteName,
		.Loop = false,
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

	//상태 및 애니메이션 변경
	CurState = State::React;
	GetRenderer()->ChangeAnimation(ReactAniName);

	//플레이어 바라보기 설정된 경우에만
	if (false == IsLookPlayer)
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
}



void FieldNPCBase::Update_React(float _DeltaTime) 
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetRenderer()->ChangeAnimation(IdleAniName);
	CurState = State::Idle;
}


