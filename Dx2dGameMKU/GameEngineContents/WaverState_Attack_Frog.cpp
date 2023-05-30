#include "PrecompileHeader.h"
#include "WaverState_Attack_Frog.h"

#include "DataMgr.h"

#include "WaverFSM.h"
#include "FieldPlayer.h"

const std::string_view WaverState_Attack_Frog::AniName = "Attack_Frog";
const std::string_view WaverState_Attack_Frog::AniFileName = "Waver_Frog.png";
const std::pair<int, int> WaverState_Attack_Frog::AniCutFrame = std::pair<int, int>(5, 5);
const float WaverState_Attack_Frog::AniInterTime = 0.06f;
const int WaverState_Attack_Frog::Damage = 5;

WaverState_Attack_Frog::WaverState_Attack_Frog()
{

}

WaverState_Attack_Frog::~WaverState_Attack_Frog()
{

}

void WaverState_Attack_Frog::Start()
{
	EnemyState_AttackBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void WaverState_Attack_Frog::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Waver");
	Dir.Move("Attack");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void WaverState_Attack_Frog::CreateAnimation()
{
	size_t AniFrmCnt = static_cast<size_t>(AniCutFrame.first * AniCutFrame.second - 1);
	std::vector<float> AniInters(AniFrmCnt, AniInterTime);
	AniInters[1] = 0.5f;

	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 23,
		.Loop = false,
		.FrameTime = AniInters
	});

	//2�� �����Ӻ��� �̵�
	EnemyState_AttackBase::SetMoveEvent(AniName, 2);

	//2~5�� �����ӵ��� �浹 üũ
	for (size_t i = 2; i < 6; ++i)
	{
		EnemyState_AttackBase::SetAttackCheckFrame(AniName, i, true);
	}
}


void WaverState_Attack_Frog::EnterState()
{
	EnemyState_AttackBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnemyState_AttackBase::SetAttackColValue(float4::Zero);
}



void WaverState_Attack_Frog::Update(float _DeltaTime)
{
	EnemyState_AttackBase::Update(_DeltaTime);

	size_t CurFrame = GetRenderer()->GetCurrentFrame();
	if (CurFrame < 2)
		return;

	JumpTimer += _DeltaTime;
	EnemyStateBase::Update_SinJump(JumpTimer, JumpDuration, JumpMaxHeight);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//���� ���� �ۿ� �ִٸ� idle
	if (GetSightRadius() < GetVecToPlayer().Size())
	{
		GetFSM()->ChangeState(WaverStateType::Idle);
		return;
	}

	//1/n�� Idle, �������� ����� �ٸ� ����
	WaverStateType RandomAttack = static_cast<WaverStateType>(GetEnemyFsm()->GetRandomAttack());
	if (GetStateEnum<WaverStateType>() == RandomAttack)
	{
		GetFSM()->ChangeState(WaverStateType::Idle);
	}
	else
	{
		GetFSM()->ChangeState(RandomAttack);
	}
}



void WaverState_Attack_Frog::Attack()
{
	//������ ������ �� ���ķ� AniInterTime�ð���ŭ �귯�� Attack ����
	float LiveTime = GetLiveTime();
	if (LiveTime < LastAttackTime + AniInterTime)
		return;

	LastAttackTime = LiveTime;
	bool Result = false;
	size_t CurFrame = GetRenderer()->GetCurrentFrame();

	if (2 == CurFrame)
	{
		Result = FieldPlayer::GetPtr()->OnDamage_Jaw();
	}
	else if (3 == CurFrame)
	{
		Result = FieldPlayer::GetPtr()->OnDamage_Face();
	}
	else if (4 == CurFrame)
	{
		Result = FieldPlayer::GetPtr()->OnDamage_Stomach();
	}
	else if (5 == CurFrame)
	{
		Result = FieldPlayer::GetPtr()->OnDamage_BlowBack();
	}
	else
	{
		MsgAssert("WaverState_Attack_Frog�� ó���� �� ���� �������� ���Խ��ϴ�");
		return;
	}

	if (false == Result)
		return;

	DataMgr::MinusPlayerHP(Damage);
}

void WaverState_Attack_Frog::ExitState()
{
	EnemyState_AttackBase::ExitState();
	LastAttackTime = 0.f;
	JumpTimer = 0.f;
}