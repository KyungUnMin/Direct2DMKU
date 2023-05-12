#include "PrecompileHeader.h"
#include "PlayerStateBase.h"


#include "KeyMgr.h"

#include "FieldPlayer.h"
#include "FieldLevelBase.h"
#include "BackGround.h"

const std::vector<KeyNames> PlayerStateBase::IdleCheckKeys =
{
	KeyNames::DownArrow,
	KeyNames::UpArrow,
	KeyNames::RightArrow,
	KeyNames::LeftArrow,
	KeyNames::Space

};

PlayerStateBase::PlayerStateBase()
{

}

PlayerStateBase::~PlayerStateBase()
{
	
}




void PlayerStateBase::Start()
{
	StateBase::Start();

	BGPtr = FieldLevelBase::GetPtr()->GetBackGround();
	Renderer = FieldPlayer::GetPtr()->GetRenderer();
}





void PlayerStateBase::Update(float _DeltaTime)
{
	StateBase::Update(_DeltaTime);

	SettingHeightRender();
	SettingDirectionRender();
}


void PlayerStateBase::SettingHeightRender()
{
	float NowHeight = FieldPlayer::GetPtr()->GetHeight();
	Renderer->GetTransform()->SetLocalPosition(float4::Up * NowHeight);
}

void PlayerStateBase::SettingDirectionRender()
{
	std::shared_ptr<FieldPlayer> PlayerPtr = FieldPlayer::GetPtr();
	GameEngineTransform* PlayerTrans = PlayerPtr->GetTransform();

	if (true == FieldPlayer::GetPtr()->IsRightDir())
	{
		PlayerTrans->SetLocalPositiveScaleX();
	}
	else
	{
		PlayerTrans->SetLocalNegativeScaleX();
	}
}




bool PlayerStateBase::Check_Idle()
{
	for (KeyNames Key : IdleCheckKeys)
	{
		if (true == KeyMgr::IsPress(Key))
			return false;
	}

	return true;
}




void PlayerStateBase::Update_Move(float _DeltaTime, const float4& _Speed)
{
	float4 MoveDir = float4::Zero;
	if (true == KeyMgr::IsPress(KeyNames::RightArrow))
	{
		MoveDir += float4::Right;
	}
	else if (true == KeyMgr::IsPress(KeyNames::LeftArrow))
	{
		MoveDir += float4::Left;
	}

	if (true == KeyMgr::IsPress(KeyNames::UpArrow))
	{
		MoveDir += float4::Up;
	}
	else if (true == KeyMgr::IsPress(KeyNames::DownArrow))
	{
		MoveDir += float4::Down;
	}

	if (true == MoveDir.IsZero())
		return;

	MoveDir.Normalize();
	MoveDir.x *= _Speed.x;
	MoveDir.y *= _Speed.y;
	MoveDir.z = MoveDir.y;

	std::shared_ptr<FieldPlayer> PlayerPtr = FieldPlayer::GetPtr();
	if (nullptr == PlayerPtr)
	{
		MsgAssert("플레이어가 존재하지 않습니다");
		return;
	}

	GameEngineTransform* PlayerTrans = PlayerPtr->GetTransform();
	float4 NextPos = PlayerTrans->GetLocalPosition() + (MoveDir * _DeltaTime);

	if (true == BGPtr->IsBlockPos(NextPos))
		return;

	//Enemy들의 길찾기때문에 그리드 기반으로도 이동 위치 막는다
	std::pair<int, int> GridPos = BGPtr->GetGridFromPos(NextPos);
	if (true == BGPtr->IsBlockGrid(GridPos.first, GridPos.second))
		return;

	PlayerTrans->SetLocalPosition(NextPos);
}

