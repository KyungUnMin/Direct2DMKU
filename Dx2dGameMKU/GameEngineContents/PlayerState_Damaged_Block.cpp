#include "PrecompileHeader.h"
#include "PlayerState_Damaged_Block.h"

#include <GameEngineCore/GameEngineLevel.h>

#include "RCGEnums.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "SkillMgr.h"

#include "PlayerFSM.h"
#include "FieldPlayer.h"
#include "HitEffect.h"

const std::string_view PlayerState_Damaged_Block::AniFileName = "Player_Block.png";

const std::vector<PlayerState_Damaged_Block::AniInfo> PlayerState_Damaged_Block::AniInfoes =
{
	{"Block",		0,		0,		FLT_MAX,	false},
	{"Damage",	1,		2,		0.1f,				false},
	{"Exit",			2,		2,		0.1f,				false}
};

PlayerState_Damaged_Block::PlayerState_Damaged_Block()
{

}

PlayerState_Damaged_Block::~PlayerState_Damaged_Block()
{

}

void PlayerState_Damaged_Block::Start()
{
	PlayerState_DamagedBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void PlayerState_Damaged_Block::LoadAnimation()
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
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), 5, 1);
}



void PlayerState_Damaged_Block::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	
	for (const AniInfo& Info : AniInfoes)
	{
		Render->CreateAnimation
		({
			.AnimationName = Info.AniName,
			.SpriteName = AniFileName,
			.Start = Info.Start,
			.End = Info.End,
			.FrameInter = Info.InterTime,
			.Loop = Info.Loop
		});
	}
}


void PlayerState_Damaged_Block::EnterState()
{
	PlayerState_DamagedBase::EnterState();

	CurState = State::Block;
	size_t Index = static_cast<size_t>(CurState);
	GetRenderer()->ChangeAnimation(AniInfoes[Index].AniName);

	SoundMgr::PlaySFX("Player_Block_Effect.wav");
}

void PlayerState_Damaged_Block::Update(float _DeltaTime)
{
	PlayerState_DamagedBase::Update(_DeltaTime);

	switch (CurState)
	{
	case PlayerState_Damaged_Block::State::Block:
		Update_Block();
		break;
	case PlayerState_Damaged_Block::State::Damage:
		Update_Damage();
		break;
	case PlayerState_Damaged_Block::State::Exit:
		Update_Exit();
		break;
	}
}


void PlayerState_Damaged_Block::Update_Block()
{
	//특수 공격(동키킥)
	if (true == KeyMgr::IsPress(KeyNames::X) && SkillMgr::HasSkill(PlayerStateType::SpecialAttack_DonkeyKick))
	{
		GetFSM()->ChangeState(PlayerStateType::SpecialAttack_DonkeyKick);
		return;
	}


	if (true == KeyMgr::IsPress(KeyNames::LeftShift))
		return;

	CurState = State::Exit;
	size_t Index = static_cast<size_t>(CurState);
	GetRenderer()->ChangeAnimation(AniInfoes[Index].AniName);
}


void PlayerState_Damaged_Block::OnDamage()
{
	static const float4 Offset = float4::Up * 100.f + float4::Back * 100.f;

	//상태를 State::Damage로 변경
	CurState = State::Damage;
	size_t Index = static_cast<size_t>(CurState);
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	Render->ChangeAnimation(AniInfoes[Index].AniName);
	SoundMgr::PlaySFX("Player_Block_Hit.wav");
	

	//방어 이펙트를 생성하고
	GameEngineActor* PlayerPtr = Render->GetActor();
	std::shared_ptr<HitEffect> EffectPtr = PlayerPtr->GetLevel()->CreateActor<HitEffect>(UpdateOrder::Effect);
	EffectPtr->OffHitSpark();
	EffectPtr->SetAirMaxRatio(0.5f);

	GameEngineTransform* PlayerTrans = PlayerPtr->GetTransform();
	GameEngineTransform* EffectTrans = EffectPtr->GetTransform();

	//자식으로 넣는다
	EffectTrans->SetParent(PlayerTrans);
	EffectTrans->SetLocalPosition(Offset);
}


void PlayerState_Damaged_Block::Update_Damage()
{
	if (false == KeyMgr::IsPress(KeyNames::LeftShift))
	{
		CurState = State::Exit;
		size_t Index = static_cast<size_t>(CurState);
		GetRenderer()->ChangeAnimation(AniInfoes[Index].AniName);
		return;
	}

	std::shared_ptr<GameEngineSpriteRenderer> RenderPtr = GetRenderer();
	if (false == RenderPtr->IsAnimationEnd())
		return;

	CurState = State::Block;
	size_t Index = static_cast<size_t>(CurState);
	RenderPtr->ChangeAnimation(AniInfoes[Index].AniName);
}


void PlayerState_Damaged_Block::Update_Exit() 
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
}

