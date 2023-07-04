#include "PrecompileHeader.h"
#include "MisuzuState_Taunt.h"

#include "SoundMgr.h"

#include "MisuzuFSM.h"
#include "FieldEnemyBase.h"

const std::string_view MisuzuState_Taunt::AniName = "Taunt";
const std::string_view MisuzuState_Taunt::AniFileName = "Misuzu_Taunt.png";
const std::pair<int, int> MisuzuState_Taunt::AniCutFrame = std::pair<int, int>(5, 5);
const float MisuzuState_Taunt::AniInterTime = 0.08f;

const std::vector<std::string_view> MisuzuState_Taunt::LaughSounds =
{
	"Misuzu_Taunt (1).wav",
	"Misuzu_Taunt (2).wav",
	"Misuzu_Taunt (3).wav",
	"Misuzu_Taunt (4).wav",
	"Misuzu_Taunt (5).wav",
};

MisuzuState_Taunt::MisuzuState_Taunt()
{

}

MisuzuState_Taunt::~MisuzuState_Taunt()
{

}

void MisuzuState_Taunt::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}

void MisuzuState_Taunt::LoadAnimation()
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

void MisuzuState_Taunt::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.Start = 0,
		.End = 22,
		.FrameInter = AniInterTime,
		.Loop = false,
	});
}


void MisuzuState_Taunt::EnterState()
{
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);

	SoundMgr::PlaySFX(LaughSounds[SoundIndex]);
	SoundIndex = (SoundIndex + 1) % LaughSounds.size();
}


void MisuzuState_Taunt::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(MisuzuStateType::Idle);
}



