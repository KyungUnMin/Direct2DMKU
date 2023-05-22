#include "PrecompileHeader.h"
#include "PlayerState_SpecialAttack_DonkeyKick.h"


#include <GameEngineCore/GameEngineLevel.h>

#include "FieldPlayer.h"
#include "PlayerFSM.h"
#include "FieldEnemyBase.h"


const std::string_view PlayerState_SpecialAttack_DonkeyKick::AniName = "SpecialAttack_DonkeyKick";
const std::string_view PlayerState_SpecialAttack_DonkeyKick::AniFileName = "Player_SpecialAttack_DonkeyKick.png";
const std::pair<int, int> PlayerState_SpecialAttack_DonkeyKick::AniCutFrame = std::pair<int, int>(5, 3);
const float PlayerState_SpecialAttack_DonkeyKick::AniInterTime = 0.08f;
const int PlayerState_SpecialAttack_DonkeyKick::Damage = 15;

PlayerState_SpecialAttack_DonkeyKick::PlayerState_SpecialAttack_DonkeyKick()
{

}

PlayerState_SpecialAttack_DonkeyKick::~PlayerState_SpecialAttack_DonkeyKick()
{

}

void PlayerState_SpecialAttack_DonkeyKick::Start()
{
	PlayerState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_SpecialAttack_DonkeyKick::LoadAnimation()
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
	Dir.Move("SpecialAttack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void PlayerState_SpecialAttack_DonkeyKick::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 11,
		.FrameInter = AniInterTime,
		.Loop = false,
	});

	PlayerState_AttackBase::SetAttackCheckFrame(AniName, 4);
}


void PlayerState_SpecialAttack_DonkeyKick::EnterState()
{
	PlayerState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	PlayerState_AttackBase::SetAttackColValue(float4::Left * 100.f);
	TotalDamage = Damage + DataMgr::GetPlayerAtt();
}





void PlayerState_SpecialAttack_DonkeyKick::Update(float _DeltaTime)
{
	PlayerState_AttackBase::Update(_DeltaTime);

	
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
	return;

}

void PlayerState_SpecialAttack_DonkeyKick::Attack(FieldEnemyBase* _Enemy)
{
	static const float4 Offset = float4::Left * 100.f + float4::Up * 150.f + float4::Back * 100.f;
	bool Result = _Enemy->OnDamage_Jaw(TotalDamage);
	if (true == Result)
	{
		PlayerState_AttackBase::CreateHitEffect(Offset);
	}
}

