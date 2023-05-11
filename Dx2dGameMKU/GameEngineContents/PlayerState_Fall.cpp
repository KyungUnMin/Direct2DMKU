#include "PrecompileHeader.h"
#include "PlayerState_Fall.h"
#include "FieldPlayer.h"
#include "PlayerFSM.h"

const std::string_view PlayerState_Fall::AniName = "Fall";
const std::string_view PlayerState_Fall::AniFolderName = "PlayerFall";
const float PlayerState_Fall::AniInterTime = 0.08f;

PlayerState_Fall::PlayerState_Fall()
{

}

PlayerState_Fall::~PlayerState_Fall()
{

}

void PlayerState_Fall::Start()
{
	PlayerStateBase::Start();

	LoadAnimation();
	CreateAnimation();
}


void PlayerState_Fall::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Player");
	Dir.Move("Movement");
	GameEngineSprite::LoadFolder(Dir.GetPlusFileName(AniFolderName).GetFullPath());
}


void PlayerState_Fall::CreateAnimation()
{
	PlayerStateBase::SpritePtr = GameEngineSprite::Find(AniFolderName);

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = GetRenderer();
	PlayerStateBase::AniInfoPtr = Renderer->CreateAnimation(AniName, AniFolderName, AniInterTime, -1, -1, false);
}



void PlayerState_Fall::EnterState()
{
	PlayerStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);
	EnterHeight = FieldPlayer::GetPtr()->GetHeight();
}


void PlayerState_Fall::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);

	float Ratio = (GetLiveTime() / Duration);
	float NowHeight = EnterHeight * (1.f - Ratio);
	FieldPlayer::GetPtr()->SetHeight(NowHeight);
	if (1.f < Ratio)
	{
		GetFSM()->ChangeState(PlayerStateType::Idle);
		return;
	}

	Update_Move(_DeltaTime);
}

