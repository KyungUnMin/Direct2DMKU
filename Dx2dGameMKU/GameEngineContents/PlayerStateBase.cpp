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
		MsgAssert("�÷��̾ �������� �ʽ��ϴ�");
		return;
	}

	//float4 CheckPos = PlayerPtr->GetPivot() + (MoveDir * _DeltaTime);
	//const std::vector<TestDesk*>& Desks = GetPlayerFsm()->GetDesks();

	//for (TestDesk* Desk : Desks)
	//{
	//	//å�� ��ġ���� �÷��̾ �� ȭ�� �Ʒ��ʿ� �ִ� ���
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

	GameEngineTransform* PlayerTrans = PlayerPtr->GetTransform();
	float4 NextPos = PlayerTrans->GetLocalPosition() + (MoveDir * _DeltaTime);

	if (true == BGPtr->IsBlockPos(NextPos))
		return;

	//Enemy���� ��ã�⶧���� �׸��� ������ε� �̵� ��ġ ���´�
	std::pair<int, int> GridPos = BGPtr->GetGridFromPos(NextPos);
	if (true == BGPtr->IsBlockGrid(GridPos.first, GridPos.second))
		return;

	PlayerTrans->SetLocalPosition(NextPos);
}