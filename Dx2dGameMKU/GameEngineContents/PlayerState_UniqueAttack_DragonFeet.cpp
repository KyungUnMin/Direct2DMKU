#include "PrecompileHeader.h"
#include "PlayerState_UniqueAttack_DragonFeet.h"


#include "DataMgr.h"
#include "SoundMgr.h"
#include "FieldCamController.h"

#include "PlayerFSM.h"
#include "FieldLevelBase.h"
#include "FieldEnemyBase.h"

const int PlayerState_UniqueAttack_DragonFeet::NeedMp = 20;

const std::string_view PlayerState_UniqueAttack_DragonFeet::AniName = "UniqueAttack_DragonFeet";
const std::string_view PlayerState_UniqueAttack_DragonFeet::AniFileName = "Player_UniqueAttack_DragonFeet.png";
const std::pair<int, int> PlayerState_UniqueAttack_DragonFeet::AniCutFrame = std::pair<int, int>(7, 4);
const float PlayerState_UniqueAttack_DragonFeet::AniInterTime = 0.05f;

const int PlayerState_UniqueAttack_DragonFeet::NormalDamage= 5;
const int PlayerState_UniqueAttack_DragonFeet::LastDamage = 25;
std::map<size_t, std::function<void(FieldEnemyBase* _Enemy)>> PlayerState_UniqueAttack_DragonFeet::AttackCallBacks;

PlayerState_UniqueAttack_DragonFeet::PlayerState_UniqueAttack_DragonFeet()
{

}

PlayerState_UniqueAttack_DragonFeet::~PlayerState_UniqueAttack_DragonFeet()
{

}

void PlayerState_UniqueAttack_DragonFeet::Start()
{
	PlayerState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
	SetAniEvents();

	CamCtrl = &(FieldLevelBase::GetPtr()->GetCameraController());
}

void PlayerState_UniqueAttack_DragonFeet::LoadAnimation()
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
	Dir.Move("UniqueAttack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void PlayerState_UniqueAttack_DragonFeet::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 21,
		.FrameInter = AniInterTime,
		.Loop = false
	});
}



void PlayerState_UniqueAttack_DragonFeet::SetAniEvents()
{
	static bool IsSeted = false;
	if (false == IsSeted)
	{
		AttackCallBacks[4] = [](FieldEnemyBase* _Enemy) 
		{
			if (true == _Enemy->OnDamage_Face(NormalDamage))
				PlayerState_AttackBase::CreateHitEffect_Face();
		};
		AttackCallBacks[5] = [](FieldEnemyBase* _Enemy) 
		{
			if (true == _Enemy->OnDamage_Jaw(NormalDamage))
				PlayerState_AttackBase::CreateHitEffect_Jaw();
		};
		AttackCallBacks[6] = [](FieldEnemyBase* _Enemy) 
		{
			if (true == _Enemy->OnDamage_Stomach(NormalDamage))
				PlayerState_AttackBase::CreateHitEffect_Stomach();
		};
		AttackCallBacks[7] = [](FieldEnemyBase* _Enemy) 
		{
			if (true == _Enemy->OnDamage_Stomach(NormalDamage))
				PlayerState_AttackBase::CreateHitEffect_Stomach();
		};
		AttackCallBacks[8] = [](FieldEnemyBase* _Enemy) 
		{
			if (true == _Enemy->OnDamage_Jaw(NormalDamage))
				PlayerState_AttackBase::CreateHitEffect_Jaw();
		};
		AttackCallBacks[9] = [](FieldEnemyBase* _Enemy) 
		{
			if (true == _Enemy->OnDamage_Face(NormalDamage))
				PlayerState_AttackBase::CreateHitEffect_Face();
		};
		AttackCallBacks[10] = [](FieldEnemyBase* _Enemy) 
		{
			if (true == _Enemy->OnDamage_Stomach(NormalDamage))
				PlayerState_AttackBase::CreateHitEffect_Stomach();
		};
		AttackCallBacks[11] = [](FieldEnemyBase* _Enemy) 
		{
			if (true == _Enemy->OnDamage_Stomach(NormalDamage))
				PlayerState_AttackBase::CreateHitEffect_Stomach();
		};
		AttackCallBacks[12] = [](FieldEnemyBase* _Enemy) 
		{
			if (true == _Enemy->OnDamage_Face(NormalDamage))
				PlayerState_AttackBase::CreateHitEffect_Face();
		};
		AttackCallBacks[14] = [](FieldEnemyBase* _Enemy) 
		{
			if (true == _Enemy->OnDamage_BlowBack(LastDamage))
				PlayerState_AttackBase::CreateHitEffect_Blow();
		};
		IsSeted = true;
	}

	for (std::pair<size_t, std::function<void(FieldEnemyBase* _Enemy)>> Pair :  AttackCallBacks)
	{
		size_t EventIndex = Pair.first;
		PlayerState_AttackBase::SetAttackCheckFrame(AniName, EventIndex);
	}
}




void PlayerState_UniqueAttack_DragonFeet::EnterState()
{
	PlayerState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	DataMgr::MinusPlayerMP(NeedMp);
	PlayerState_AttackBase::SetAttackColValue();

	static size_t Index = 0;
	if ((Index++) % 2)
	{
		SoundMgr::PlaySFX("Player_DragonFeet_Voice1.wav");
	}
	else
	{
		SoundMgr::PlaySFX("Player_DragonFeet_Voice2.wav");
	}

	SoundMgr::PlaySFX("Player_DragonFeet_Effect.wav");
}



void PlayerState_UniqueAttack_DragonFeet::Update(float _DeltaTime)
{
	PlayerState_AttackBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//TODO

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
	return;

}




void PlayerState_UniqueAttack_DragonFeet::Attack(FieldEnemyBase* _Enemy)
{
	//처음 공격을 맞췄을때
	if (false == IsHit)
	{
		CamCtrl->SetShakeState(0.5f);
		IsHit = true;
	}


	size_t CurFrame = GetRenderer()->GetCurrentFrame();

	std::map<size_t, std::function<void(FieldEnemyBase* _Enemy)>>::iterator FindIter = AttackCallBacks.find(CurFrame);

	if (AttackCallBacks.end() == FindIter)
	{
		MsgAssert("이벤트를 설정한 애니메이션에 해당되는 콜백이 존재하지 않습니다");
		return;
	}

	SoundMgr::PlaySFX("HitEffective.wav").SetVolume(2.5f);
	FindIter->second(_Enemy);
}


void PlayerState_UniqueAttack_DragonFeet::ExitState()
{
	PlayerState_AttackBase::ExitState();
	IsHit = false;
}

