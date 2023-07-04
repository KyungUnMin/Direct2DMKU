#include "PrecompileHeader.h"
#include "PlayerState_Damaged_BlowBack.h"

#include "SoundMgr.h"

#include "PlayerFSM.h"
#include "FieldPlayer.h"
#include "FieldLevelBase.h"
#include "BackGround.h"

const std::string_view PlayerState_Damaged_BlowBack::AniName = "BlowBack";
const std::string_view PlayerState_Damaged_BlowBack::AniFileName = "Player_KnockDown.png";
const std::pair<int, int> PlayerState_Damaged_BlowBack::AniCutFrame = std::pair<int, int>(5, 9);
const float PlayerState_Damaged_BlowBack::AniInterTime = 0.05f;



PlayerState_Damaged_BlowBack::PlayerState_Damaged_BlowBack()
{

}

PlayerState_Damaged_BlowBack::~PlayerState_Damaged_BlowBack()
{

}



void PlayerState_Damaged_BlowBack::Start()
{
	PlayerState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
	PlayerTrans = FieldPlayer::GetPtr()->GetTransform();
	BGPtr = FieldLevelBase::GetPtr()->GetBackGround();
}

void PlayerState_Damaged_BlowBack::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Player");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void PlayerState_Damaged_BlowBack::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime,
		.Loop = false
	});
}


void PlayerState_Damaged_BlowBack::EnterState()
{
	PlayerState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	FieldPlayer::GetPtr()->SetHeight(0.f);

	SoundMgr::PlaySFX("HitEffective.wav").SetVolume(2.5f);
	SoundMgr::PlaySFX("Player_BlowDamaged_Voice.wav");
}


void PlayerState_Damaged_BlowBack::Update(float _DeltaTime)
{
	PlayerState_DamagedBase::Update(_DeltaTime);

	if (false == Update_BlowBack(_DeltaTime))
	{
		//TODO : 날라가다가 벽에 막혔을때

	}


	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
}




bool PlayerState_Damaged_BlowBack::Update_BlowBack(float _DeltaTime)
{
	float LiveTime = GetLiveTime();
	float Ratio = (LiveTime / Duration);
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);

	bool IsMoveOk = Update_BlowHorizon(ClampRatio, _DeltaTime);

	return IsMoveOk;
}



bool PlayerState_Damaged_BlowBack::Update_BlowHorizon(float _Ratio, float _DeltaTime)
{
	float NowAcc = StartAcc * (1.f - _Ratio);

	float4 NextPos = PlayerTrans->GetLocalPosition();


	//오른쪽을 바라보고 있을때
	if (0.f <  PlayerTrans->GetLocalScale().x)
	{
		//바라보는 방향 반대로 날라간다
		NextPos += (float4::Left * NowAcc * _DeltaTime);
	}
	//왼쪽을 바라보고 있을때
	else
	{
		//바라보는 방향 반대로 날라간다
		NextPos += (float4::Right * NowAcc * _DeltaTime);
	}

	//벽에 막혔을때
	if (true == BGPtr->IsBlockPos(NextPos))
		return false;

	std::pair<int, int> NextGridPos = BGPtr->GetGridFromPos(NextPos);
	if (true == BGPtr->IsBlockGrid(NextGridPos.first, NextGridPos.second))
		return false;

	PlayerTrans->SetLocalPosition(NextPos);
	return true;
}

