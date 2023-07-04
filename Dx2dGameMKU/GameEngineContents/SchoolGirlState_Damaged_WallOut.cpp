#include "PrecompileHeader.h"
#include "SchoolGirlState_Damaged_WallOut.h"

#include "SchoolGirlFSM.h"
#include "FieldEnemyBase.h"

const std::string_view SchoolGirlState_Damaged_WallOut::AniName = "WallOut";
const std::string_view SchoolGirlState_Damaged_WallOut::AniFileName = "SchoolGirl_WallOut.png";
const std::pair<int, int> SchoolGirlState_Damaged_WallOut::AniCutFrame = std::pair<int, int>(5, 1);
const float SchoolGirlState_Damaged_WallOut::AniInterTime = 0.1f;

SchoolGirlState_Damaged_WallOut::SchoolGirlState_Damaged_WallOut()
{

}

SchoolGirlState_Damaged_WallOut::~SchoolGirlState_Damaged_WallOut()
{

}



void SchoolGirlState_Damaged_WallOut::Start()
{
	EnemyState_DamagedBase::Start();
	LoadAnimation();
	CreateAnimation();

	EnemyState_DamagedBase::SetGroundBlow();
	EnemyState_DamagedBase::SetBlowValue(StartReflectSize, Duration);
}


void SchoolGirlState_Damaged_WallOut::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("SchoolGirl");
	Dir.Move("Damaged");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void SchoolGirlState_Damaged_WallOut::CreateAnimation()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	Render->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 2,
		.Loop = false,
		.FrameTime = std::vector<float>{0.2f, 0.05f, 0.05f},
	});
}


void SchoolGirlState_Damaged_WallOut::EnterState()
{
	EnemyState_DamagedBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	SetReflectDirection();

	SoundMgr::PlaySFX("FemaleEnemy_WallOut.wav").SetVolume(0.8f);
}

void SchoolGirlState_Damaged_WallOut::SetReflectDirection()
{
	//Enemy�� ���� == ƨ�������� ����
	bool ReflectDir = EnemyStateBase::IsRightDir();
	EnemyState_DamagedBase::Set_BlowDir(ReflectDir);
}


void SchoolGirlState_Damaged_WallOut::Update(float _DeltaTime)
{
	EnemyState_DamagedBase::Update(_DeltaTime);

	//�����κ��� ƨ���� ������
	EnemyState_DamagedBase::Update_BlowBack(_DeltaTime);

	if (GetLiveTime() < Duration)
		return;

	GetFSM()->ChangeState(SchoolGirlStateType::Damaged_Dazed);
}