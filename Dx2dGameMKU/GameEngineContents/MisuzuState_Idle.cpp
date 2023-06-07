#include "PrecompileHeader.h"
#include "MisuzuState_Idle.h"

#include <GameEngineBase/GameEngineRandom.h>

#include "MisuzuFSM.h"

#include "FieldEnemyBase.h"

const std::string_view MisuzuState_Idle::AniName = "Idle";
const std::string_view MisuzuState_Idle::AniFileName = "Misuzu_Idle.png";
const std::pair<int, int> MisuzuState_Idle::AniCutFrame = std::pair<int, int>(5, 3);
const float MisuzuState_Idle::AniInterTime = 0.08f;

MisuzuState_Idle::MisuzuState_Idle()
{

}

MisuzuState_Idle::~MisuzuState_Idle()
{

}

void MisuzuState_Idle::Start() 
{
	EnemyState_IdleBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void MisuzuState_Idle::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Misuzu");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void MisuzuState_Idle::CreateAnimation() 
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 11,
		.FrameInter = AniInterTime
	});
}


void MisuzuState_Idle::EnterState()
{
	EnemyState_IdleBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
}


void MisuzuState_Idle::Update(float _DeltaTime) 
{
	EnemyState_IdleBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	//���ڷ� �� Ȯ���� ���� ���Ÿ� ���� �õ�
	if (true == FarAttackExcute(100))
		return;

	//���� ���·� �ٲٰų� Idle�� �����ϴ� ���
	if (true == EnemyState_IdleBase::ChangeAttackState())
		return;


	//Idle ���ð��� ���������� �̵����·� ����
	if (false == EnemyState_IdleBase::IsWaitFinished())
		return;


	GetFSM()->ChangeState(MisuzuStateType::Walk);
}


bool MisuzuState_Idle::FarAttackExcute(int _Percent)
{
	int RandValue = GameEngineRandom::MainRandom.RandomInt(0, 100);

	//Ȯ���� ���� ���� ���
	if (_Percent < RandValue)
		return false;

	size_t FarAttack = GetEnemyFsm()->GetRandomFarAttack();

	//�ش� Phase������ ���Ÿ� ������ ���� ���
	if (-1 == FarAttack)
		return false;

	GetFSM()->ChangeState(FarAttack);
	return true;
}