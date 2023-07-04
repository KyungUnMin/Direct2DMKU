#include "PrecompileHeader.h"
#include "PlayerState_SpecialAttack_DAP.h"

#include <GameEngineCore/GameEngineLevel.h>

#include "RCGEnums.h"
#include "SoundMgr.h"

#include "FieldPlayer.h"
#include "PlayerFSM.h"
#include "DapEffect.h"
#include "FieldEnemyBase.h"
#include "FieldLevelBase.h"
#include "Fader.h"


const std::string_view PlayerState_SpecialAttack_DAP::AniName = "SpecialAttack_DAP";
const std::string_view PlayerState_SpecialAttack_DAP::AniFileName = "Player_SpecialAttack_DAP.png";
const std::pair<int, int> PlayerState_SpecialAttack_DAP::AniCutFrame = std::pair<int, int>(5, 5);
const float PlayerState_SpecialAttack_DAP::AniInterTime = 0.05f;
const size_t PlayerState_SpecialAttack_DAP::EffectCount = 50;
const int PlayerState_SpecialAttack_DAP::Damage = 20;

PlayerState_SpecialAttack_DAP::PlayerState_SpecialAttack_DAP()
{

}

PlayerState_SpecialAttack_DAP::~PlayerState_SpecialAttack_DAP()
{

}

void PlayerState_SpecialAttack_DAP::Start()
{
	PlayerState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
	CreateEffect();
}

void PlayerState_SpecialAttack_DAP::LoadAnimation()
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

void PlayerState_SpecialAttack_DAP::CreateAnimation()
{
	int FrameCnt = AniCutFrame.first * AniCutFrame.second;
	std::vector<float> FrameTime(static_cast<size_t>(FrameCnt), AniInterTime);
	FrameTime[3] = AniInterTime * 2.5f;

	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Loop = false,
		.FrameTime = FrameTime,
	});

	PlayerState_AttackBase::SetAttackCheckFrame(AniName, 4);

	Render->SetAnimationStartEvent(AniName, 5, []()
	{
		SoundMgr::PlaySFX("Player_Dap_Effect.wav");
	});
}

void PlayerState_SpecialAttack_DAP::CreateEffect()
{
	std::shared_ptr<FieldPlayer> PlayerPtr = FieldPlayer::GetPtr();
	GameEngineTransform* PlayerTrans = PlayerPtr->GetTransform();
	GameEngineLevel* Level = PlayerPtr->GetLevel();

	Effects.resize(EffectCount, nullptr);
	for (std::shared_ptr<DapEffect>& Effect : Effects)
	{
		Effect = Level->CreateActor<DapEffect>();
		Effect->GetTransform()->SetParent(PlayerTrans, false);
	}
}

void PlayerState_SpecialAttack_DAP::EnterState()
{
	PlayerState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	PlayerState_AttackBase::SetAttackColValue();
	TotalDamage = Damage + DataMgr::GetPlayerAtt();
}





void PlayerState_SpecialAttack_DAP::Update(float _DeltaTime)
{
	PlayerState_AttackBase::Update(_DeltaTime);

	//5번 프레임 이상일때부터
	size_t NowFrame = GetRenderer()->GetCurrentFrame();
	if (NowFrame < 5)
		return;

	float LiveTime = GetLiveTime();
	if ((EffectTime < LiveTime) && (Cursor < Effects.size()))
	{
		Effects[Cursor++]->Init();
		ResetLiveTime();
	}

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(PlayerStateType::Movement_Idle);
	return;

}


void PlayerState_SpecialAttack_DAP::ExitState()
{
	PlayerState_AttackBase::ExitState();

	Cursor = 0;
	EffectOnValue = false;
}

void PlayerState_SpecialAttack_DAP::Attack(FieldEnemyBase* _Enemy)
{
	bool Result = _Enemy->OnDamage_BlowBack(TotalDamage);
	if (false == Result)
		return;
	
	//이펙트 생성
	PlayerState_AttackBase::CreateHitEffect_Blow();
	SoundMgr::PlaySFX("Player_Dap_Hit.mp3").SetVolume(3.f);

	//화면 반짝임 이펙트
	/*if (true == EffectOnValue)
		return;


	EffectOnValue = true;
	std::shared_ptr<Fader> FadePtr = nullptr;
	FadePtr = FieldLevelBase::GetPtr()->CreateActor<Fader>(UpdateOrder::UI);
	FadePtr->Init(float4::One, 0.2f,[this]()
	{
		this->EffectEnd();
	});*/
}

