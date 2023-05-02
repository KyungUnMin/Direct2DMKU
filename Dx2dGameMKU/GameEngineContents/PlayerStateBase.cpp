#include "PrecompileHeader.h"
#include "PlayerStateBase.h"

#include "KeyMgr.h"
#include "FieldPlayer.h"

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

	//float4 CheckPos = PlayerPtr->GetPivot() + (MoveDir * _DeltaTime);
	//const std::vector<TestDesk*>& Desks = GetPlayerFsm()->GetDesks();

	//for (TestDesk* Desk : Desks)
	//{
	//	//책상 위치보다 플레이어가 더 화면 아래쪽에 있는 경우
	//	if (Desk->GetPos().y < PlayerPtr->GetPos().y)
	//		continue;

	//	GameEngineCollision* DeskCol = Desk->GetCurHeightCollision();
	//	bool Result = GameEngineCollision::CollisionRectToPoint
	//	(
	//		{ DeskCol->GetActorPlusPos(), DeskCol->GetScale() }, { CheckPos }
	//	);

	//	if (true == Result)
	//		return;
	//}

	//PlayerPtr->SetMove(MoveDir * _DeltaTime);

	PlayerPtr->GetTransform()->AddLocalPosition(MoveDir * _DeltaTime);
}