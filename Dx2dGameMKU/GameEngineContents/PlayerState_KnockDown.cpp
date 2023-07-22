#include "PrecompileHeader.h"
#include "PlayerState_KnockDown.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCGEnums.h"


#include "FieldPlayer.h"
#include "FieldLevelBase.h"
#include "BackGround.h"
#include "ContinueBox.h"



const std::string_view PlayerState_KnockDown::AniFileName = "Player_Defeated.png";


PlayerState_KnockDown::PlayerState_KnockDown()
{

}

PlayerState_KnockDown::~PlayerState_KnockDown()
{

}

void PlayerState_KnockDown::Start()
{
	PlayerState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();

	std::shared_ptr<FieldPlayer> Player = FieldPlayer::GetPtr();
	PlayerMainCollider = Player->GetMainCollider();
	PlayerTrans = Player->GetTransform();

	BGPtr = FieldLevelBase::GetPtr()->GetBackGround();
}

void PlayerState_KnockDown::LoadAnimation() 
{
	if (nullptr != GameEngineSprite::Find(AniFileName))
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Player");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), 5, 10);
}

void PlayerState_KnockDown::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	Render->CreateAnimation
	({
		.AnimationName = AniFileName,
		.SpriteName = AniFileName,
		.FrameInter = 0.08f,
		.Loop = false,
	});
}




void PlayerState_KnockDown::EnterState()
{
	PlayerState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniFileName);
	PlayerMainCollider->Off();

	//플레이어가 바라보고 있는 방향 반대로 날라감
	bool IsPlayerRightLook = FieldPlayer::GetPtr()->IsRightDir();
	BlowDir = IsPlayerRightLook ? float4::Left : float4::Right;
}

void PlayerState_KnockDown::Update(float _DeltaTime) 
{
	PlayerState_DamagedBase::Update(_DeltaTime);

	if (true == GetRenderer()->IsAnimationEnd())
	{
		CreateContinueUI();
		return;
	}

	float Ratio = GetLiveTime() / BlowDuration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	float NowSpeed = (StartAcc * (1.f - ClampRatio));

	float4 NowPos = PlayerTrans->GetLocalPosition();
	float4 NextPos = NowPos + (BlowDir * NowSpeed * _DeltaTime);
	if (true == BGPtr->IsBlockPos(NextPos))
		return;

	std::pair<int, int> NextGridPos = BGPtr->GetGridFromPos(NextPos);
	if (true == BGPtr->IsBlockGrid(NextGridPos.first, NextGridPos.second))
		return;

	PlayerTrans->SetLocalPosition(NextPos);
}


void PlayerState_KnockDown::CreateContinueUI()
{
	if (nullptr != BoxUI)
		return;

	BoxUI = FieldLevelBase::GetPtr()->CreateActor<ContinueBox>(UpdateOrder::UI);
	BoxUI->Init([this]()
	{
		GetFSM()->ChangeState(PlayerStateType::Movement_BattleStart);
	});
}



void PlayerState_KnockDown::ExitState()
{
	PlayerState_DamagedBase::ExitState();
	PlayerMainCollider->On();
}