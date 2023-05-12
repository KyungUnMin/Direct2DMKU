#include "PrecompileHeader.h"
#include "PlayerState_Idle.h"

#include "KeyMgr.h"
#include "PlayerFSM.h"

const std::string_view PlayerState_Idle::AniName = "Idle";
const std::string_view PlayerState_Idle::AniFolderName = "PlayerIdle";
const float PlayerState_Idle::AniInterTime = 0.08f;

PlayerState_Idle::PlayerState_Idle()
{

}

PlayerState_Idle::~PlayerState_Idle()
{

}



void PlayerState_Idle::Start()
{
	PlayerStateBase::Start();

	SetArrowKey();
	LoadAnimation();
	CreateAnimation();
}


void PlayerState_Idle::SetArrowKey()
{
	ArrowKeyNames.reserve(4);
	ArrowKeyNames.push_back(KeyNames::UpArrow);
	ArrowKeyNames.push_back(KeyNames::DownArrow);
	ArrowKeyNames.push_back(KeyNames::RightArrow);
	ArrowKeyNames.push_back(KeyNames::LeftArrow);
}



void PlayerState_Idle::LoadAnimation()
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



void PlayerState_Idle::CreateAnimation()
{
	PlayerStateBase::SpritePtr = GameEngineSprite::Find(AniFolderName);

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = GetRenderer();
	PlayerStateBase::AniInfoPtr = Renderer->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFolderName,
		.FrameInter = AniInterTime
	});
}


void PlayerState_Idle::EnterState()
{
	PlayerStateBase::EnterState();

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = GetRenderer();
	Renderer->ChangeAnimation(AniName);
}




void PlayerState_Idle::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);
	
	for (KeyNames Arrow : ArrowKeyNames)
	{
		if (false == KeyMgr::IsPress(Arrow))
			continue;

		GetFSM()->ChangeState(PlayerStateType::Move);
		return;
	}

	if (true == KeyMgr::IsPress(KeyNames::Space))
	{
		GetFSM()->ChangeState(PlayerStateType::Jump);
		return;
	}

}

