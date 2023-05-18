#include "PrecompileHeader.h"
#include "PlayerState_DamagedBase.h"

#include <GameEngineCore/GameEngineSprite.h>


#include "RCGDefine.h"


const std::string_view PlayerState_DamagedBase::NormalDamage_FileName = "Player_GetHit.png";

PlayerState_DamagedBase::PlayerState_DamagedBase()
{

}

PlayerState_DamagedBase::~PlayerState_DamagedBase()
{

}

void PlayerState_DamagedBase::Start()
{
	PlayerStateBase::Start();

	PlayerStateBase::DirChangeOff();
	LoadNormalDamagedImage();
}

void PlayerState_DamagedBase::LoadNormalDamagedImage()
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
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(NormalDamage_FileName).GetFullPath(), 5, 3);
}