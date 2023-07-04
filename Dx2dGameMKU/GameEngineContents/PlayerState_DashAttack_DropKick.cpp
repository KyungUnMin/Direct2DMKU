#include "PrecompileHeader.h"
#include "PlayerState_DashAttack_DropKick.h"

#include "SoundMgr.h"

#include "FieldPlayer.h"
#include "PlayerFSM.h"
#include "FieldEnemyBase.h"


const std::string_view PlayerState_DashAttack_DropKick::AniName = "DashAttack_DropKick";
const std::string_view PlayerState_DashAttack_DropKick::AniFileName = "Player_DashAttack_DropKick.png";
const std::pair<int, int> PlayerState_DashAttack_DropKick::AniCutFrame = std::pair<int, int>(5, 3);
const float PlayerState_DashAttack_DropKick::AniInterTime = 0.06f;
const int PlayerState_DashAttack_DropKick::Damage = 10;
const float PlayerState_DashAttack_DropKick::IneriaDuration = 0.7f;

PlayerState_DashAttack_DropKick::PlayerState_DashAttack_DropKick()
{

}

PlayerState_DashAttack_DropKick::~PlayerState_DashAttack_DropKick()
{

}

void PlayerState_DashAttack_DropKick::Start()
{
	PlayerState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_DashAttack_DropKick::LoadAnimation()
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
	Dir.Move("DashAttack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void PlayerState_DashAttack_DropKick::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 13,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	PlayerState_AttackBase::SetAttackCheckFrame(AniName, 4);
}



void PlayerState_DashAttack_DropKick::EnterState()
{
	PlayerState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);

	static const float4 AttackColPos = float4::Right * 50.f;
	static const float4 AttackColScale = float4::One * 100.f;
	PlayerState_AttackBase::SetAttackColValue(AttackColPos, AttackColScale);

	TotalDamage = Damage + DataMgr::GetPlayerAtt();

	SoundMgr::PlaySFX("Player_DropKick_Effect.wav");
	SoundMgr::PlaySFX("Player_DropKick_Voice.wav");
}





void PlayerState_DashAttack_DropKick::Update(float _DeltaTime)
{
	PlayerState_AttackBase::Update(_DeltaTime);

	PlayerState_AttackBase::Update_DashIneria(_DeltaTime, IneriaDuration);
	PlayerState_AttackBase::Update_SinVertical(IneriaDuration, MaxHeight);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
}


void PlayerState_DashAttack_DropKick::Attack(FieldEnemyBase* _Enemy)
{
	float4 PlayerMoveDir = FieldPlayer::GetPtr()->GetMoveDirVec();
	float4 EnemyLookPos = _Enemy->GetTransform()->GetWorldPosition();

	//플레이어 움직임의 반대 방향으로 바라본 후에 BlowBack처리돼야 함(블로우백은 뒤로 날라가니까 반대방향)
	EnemyLookPos -= PlayerMoveDir;
	_Enemy->Look(EnemyLookPos);


	bool Result = _Enemy->OnDamage_BlowBack(TotalDamage);
	if (false == Result)
		return;

	PlayerState_AttackBase::CreateHitEffect_Blow();
	SoundMgr::PlaySFX("Player_Dash_Hit.wav").SetVolume(2.f);
}

