#include "PrecompileHeader.h"
#include "TigerManState_Attack_Rolling.h"

#include "DataMgr.h"

#include "TigerManFSM.h"
#include "FieldPlayer.h"

const std::vector<std::string_view> TigerManState_Attack_Rolling::AniNames = 
{
	"Attack_RollStart",
	"Attack_Rolling",
	"Attack_RollEnd"
};

const std::vector<std::string_view> TigerManState_Attack_Rolling::AniFileNames = 
{
	"TigerMan_CircusLowStart.png",
	"TigerMan_CircusRolling.png",
	"TigerMan_CircusEnd.png"
};

const std::vector <std::pair<int, int>> TigerManState_Attack_Rolling::AniCutFrames = 
{
	{5, 2},{5, 1},{5, 1}
};

const std::vector <std::pair<size_t, size_t>> TigerManState_Attack_Rolling::AniIndexes =
{
	{0,6},{0, 3},{0,4}
};

const float TigerManState_Attack_Rolling::AniInterTime = 0.08f;
const int TigerManState_Attack_Rolling::Damage = 5;

TigerManState_Attack_Rolling::TigerManState_Attack_Rolling()
{

}

TigerManState_Attack_Rolling::~TigerManState_Attack_Rolling()
{

}

void TigerManState_Attack_Rolling::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void TigerManState_Attack_Rolling::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("TigerMan");
	Dir.Move("Attack");

	for (size_t i = 0; i < static_cast<size_t>(State::COUNT); ++i)
	{
		const std::string_view& AniFileName = AniFileNames[i];
		const std::pair<int, int>& AniCutFrame = AniCutFrames[i];
		GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
	}
}

void TigerManState_Attack_Rolling::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	for (size_t i = 0; i < static_cast<size_t>(State::COUNT); ++i)
	{
		bool IsLoop = false;
		float InterTime = AniInterTime;
		if (State::Rolling == static_cast<State>(i))
		{
			IsLoop = true;
			InterTime = AniInterTime * 0.75f;
		}

		Render->CreateAnimation
		({
			.AnimationName = AniNames[i],
			.SpriteName = AniFileNames[i],
			.Start = AniIndexes[i].first,
			.End = AniIndexes[i].second,
			.FrameInter = InterTime,
			.Loop = IsLoop
		});
	}
}


void TigerManState_Attack_Rolling::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniNames[static_cast<size_t>(CurState)]);
	EnemyState_AttackBase::SetAttackColValue(float4::Zero);
}



void TigerManState_Attack_Rolling::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

	switch (CurState)
	{
	case TigerManState_Attack_Rolling::State::RollStart:
		Update_RollStart();
		break;
	case TigerManState_Attack_Rolling::State::Rolling:
		Update_Rolling(_DeltaTime);
		break;
	case TigerManState_Attack_Rolling::State::RoolEnd:
		Update_RollEnd();
		break;
	default:
	{
		MsgAssert("TigerMan Rolling 스킬의 현재 상태가 COUNT로 되어 있습니다");
		return;
	}
	}
}





void TigerManState_Attack_Rolling::Update_RollStart()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	if (false == Render->IsAnimationEnd())
		return;

	CurState = State::Rolling;
	GetRenderer()->ChangeAnimation(AniNames[static_cast<size_t>(CurState)]);
	RollInTime = GetLiveTime();
}



void TigerManState_Attack_Rolling::Update_Rolling(float _DeltaTime)
{
	//Rolling이 시작되고 나서 흐른 시간
	float Time = GetLiveTime() - RollInTime;
	
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	//Rolling중일때
	if (Time < RollingDuration)
	{
		//플레이어 추적
		EnemyState_AttackBase::Update_AccTraceAttack(_DeltaTime);
		return;
	}

	//항상 애니메이션이 끝날때만 State 변경됨
	if (false == Render->IsAnimationEnd())
	{
		EnemyState_AttackBase::Update_AccTraceAttack(_DeltaTime);
		return;
	}
	
	//Rolling이 끝났을때
	CurState = State::RoolEnd;
	Render->ChangeAnimation(AniNames[static_cast<size_t>(CurState)]);
}


void TigerManState_Attack_Rolling::Attack()
{
	float LiveTime = GetLiveTime();
	if (LiveTime < (LastAttack + AttackWaitTime))
		return;

	LastAttack = LiveTime;
	bool Result = FieldPlayer::GetPtr()->OnDamage_BlowBack();
	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}



void TigerManState_Attack_Rolling::Update_RollEnd()
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(TigerManStateType::Idle);
}



void TigerManState_Attack_Rolling::ExitState()
{
	EnemyState_AttackBase::ExitState();

	CurState = State::RollStart;
	RollInTime = 0.f;
	LastAttack = 0.f;
}