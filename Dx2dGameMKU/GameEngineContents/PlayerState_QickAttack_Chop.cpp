#include "PrecompileHeader.h"
#include "PlayerState_QickAttack_Chop.h"

#include "KeyMgr.h"

#include "PlayerFSM.h"

const std::string_view PlayerState_QickAttack_Chop::AniName = "QuickAttack_Chop";
const std::string_view PlayerState_QickAttack_Chop::AniFolderName = "PQA_Chop_01";
const float PlayerState_QickAttack_Chop::AniInterTime = 0.08f;

PlayerState_QickAttack_Chop::PlayerState_QickAttack_Chop()
{

}

PlayerState_QickAttack_Chop::~PlayerState_QickAttack_Chop()
{

}

void PlayerState_QickAttack_Chop::Start()
{
	PlayerStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_QickAttack_Chop::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Player");
	Dir.Move("Attack");
	Dir.Move("RCG_QuickAttack");
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName(AniFolderName).GetFullPath());
}

void PlayerState_QickAttack_Chop::CreateAnimation() 
{
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = GetRenderer();
	AniInfoPtr = Renderer->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFolderName,
		.FrameInter = AniInterTime,
		.Loop = false
	});

	std::shared_ptr<GameEngineSprite> SpritePtr = GameEngineSprite::Find(AniFolderName);
	PlayerStateBase::SetAnimationInfo(SpritePtr, AniInfoPtr);

	PlayerStateBase::SetAniFrameOffset(2, float4::Right * 29.f);
	PlayerStateBase::SetAniFrameOffset(3, float4::Right * 29.f);
	PlayerStateBase::SetAniFrameOffset(4, float4::Right * 28.f);
}

void PlayerState_QickAttack_Chop::EnterState()
{
	PlayerStateBase::EnterState();

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = GetRenderer();
	Renderer->ChangeAnimation(AniName);
}




void PlayerState_QickAttack_Chop::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);

	if (true == KeyMgr::IsDown(KeyNames::Z))
	{
		IsReserveChainAttack = true;
	}

	if (false == AniInfoPtr->IsEnd())
		return;

	/*if (false == IsReserveChainAttack)
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
		return;
	}*/
	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
	return;

	//TODO
}


void PlayerState_QickAttack_Chop::ExitState()
{
	PlayerStateBase::ExitState();

	IsReserveChainAttack = false;
}
