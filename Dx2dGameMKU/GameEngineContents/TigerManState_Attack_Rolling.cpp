#include "PrecompileHeader.h"
#include "TigerManState_Attack_Rolling.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "DataMgr.h"
#include "RCGEnums.h"
#include "SoundMgr.h"

#include "TigerManFSM.h"
#include "FieldPlayer.h"
#include "FieldEnemyBase.h"
#include "BackGround.h"

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

	SoundMgr::PlaySFX("TigerMan_RollingEnter.wav");
	SoundMgr::PlaySFX("TigerMan_Rolling_Voice.wav");
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
		MsgAssert("TigerMan Rolling ��ų�� ���� ���°� COUNT�� �Ǿ� �ֽ��ϴ�");
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
	Update_Sfx(_DeltaTime);

	//Rolling�� ���۵ǰ� ���� �帥 �ð�
	float Time = GetLiveTime() - RollInTime;
	
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	float RollingRatio = (Time / Duration);
	//TracePlayer(RollingRatio, _DeltaTime);
	TracePlayer(_DeltaTime);


	if (RollingRatio < 1.f)
		return;

	//�׻� �ִϸ��̼��� �������� State �����
	if (false == Render->IsAnimationEnd())
		return;
	
	//Rolling�� ��������
	CurState = State::RoolEnd;
	Render->ChangeAnimation(AniNames[static_cast<size_t>(CurState)]);
	SoundMgr::PlaySFX("TigerMan_RollingEnter.wav");
}


void TigerManState_Attack_Rolling::Update_Sfx(float _DeltaTime)
{
	static float Timer = 0.f;
	Timer += _DeltaTime;
	if (Timer < 0.3f)
		return;

	Timer = 0.f;
	SoundMgr::PlaySFX("TigerMan_Rolling.wav");
}


void TigerManState_Attack_Rolling::TracePlayer(float _DeltaTime)
{
	//�÷��̾ ���ϴ� ����
	float4 DirToPlayer = GetVecToPlayer();
	DirToPlayer.Normalize();

	//�׻� �÷��̾� �ٶ󺸱�
	EnemyStateBase::ChangeRenderDirection();

	//���ӵ� ���ϱ�
	TraceVec += DirToPlayer * TraceAcc * _DeltaTime;

	//�ִ� �ӵ� ���Ѽ�
	if (MaxSpeed < TraceVec.Size())
	{
		TraceVec.Normalize();
		TraceVec *= MaxSpeed;
	}


	//������ ������ ��ġ ���
	GameEngineTransform* EnemyTrans = GetEnemy()->GetTransform();
	float4 NowPos = EnemyTrans->GetLocalPosition();
	float4 NextPos = NowPos + (TraceVec * _DeltaTime);

	//���� ���� ���1
	std::shared_ptr<BackGround> BGPtr = GetBackGround();
	if (true == BGPtr->IsBlockPos(NextPos))
	{
		TraceVec = -TraceVec;
		return;
	}

	//���� ���� ���2
	std::pair<int, int> GriNextPos = BGPtr->GetGridFromPos(NextPos);
	if (true == BGPtr->IsBlockGrid(GriNextPos.first, GriNextPos.second))
	{
		TraceVec = -TraceVec;
		return;
	}

	//���� �̵�
	EnemyTrans->SetLocalPosition(NextPos);

	//�÷��̾�� ���� ó��
	AttackCheck();
	//��ų
	TeamKill();
}

void TigerManState_Attack_Rolling::TeamKill()
{
	static std::vector<std::shared_ptr<GameEngineCollision>> ColGroup;
	std::shared_ptr<GameEngineCollision> AttackCollider = GetAttackCollider();

	//�浹 üũ, �浹 ��������
	ColGroup.clear();
	if (false == AttackCollider->CollisionAll(CollisionOrder::EnemyMain, ColGroup, ColType::SPHERE3D, ColType::SPHERE3D))
		return;


	FieldEnemyBase* ThisPtr = GetEnemy();
	GameEngineTransform* ThisTrans = ThisPtr->GetTransform();

	//�浹�� Enemy�� �������
	for (std::shared_ptr<GameEngineCollision> EnemyCol : ColGroup)
	{
		if (EnemyCol->GetActor() == ThisPtr)
			continue;

		FieldEnemyBase* EnemyPtr = dynamic_cast<FieldEnemyBase*>(EnemyCol->GetActor());
		if (nullptr == EnemyPtr)
		{
			MsgAssert("Enemy�� �ƴ� ��ü�� EnemyMain�ݸ����� ������ �ֽ��ϴ�");
			return;
		}

		//�浹�� Enemy ���� ����
		GameEngineTransform* EnemyTrans = EnemyPtr->GetTransform();

		//(�� <- This) �������� �浹�� ���
		if (EnemyTrans->GetWorldPosition().x < ThisTrans->GetWorldPosition().x)
		{
			//���� �ٶ󺸱�
			EnemyTrans->SetLocalNegativeScaleX();
		}
		//(This -> ��) �������� �浹�� ���
		else
		{
			//������ �ٶ󺸱�
			EnemyTrans->SetLocalPositiveScaleX();
		}

		EnemyPtr->OnDamage_BlowBack(Damage);
	}
}


void TigerManState_Attack_Rolling::Attack()
{
	float LiveTime = GetLiveTime();
	if (LiveTime < (LastAttack + AttackWaitTime))
		return;

	LastAttack = LiveTime;
	bool Result = FieldPlayer::GetPtr()->OnDamage_BlowBack(Damage);
	
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
	TraceVec = float4::Zero;
}



