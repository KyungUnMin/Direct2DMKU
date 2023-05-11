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
	//어차피 플레이어는 게임이 끝날때 모두 동시에 죽을 것 같다
	if (nullptr != SpritePtr)
	{
		SpritePtr = nullptr;
	}
}

void PlayerStateBase::Start()
{
	StateBase::Start();
	BGPtr = FieldLevelBase::GetPtr()->GetBackGround();
}


void PlayerStateBase::EnterState()
{
	StateBase::EnterState();
	
	if (nullptr == SpritePtr || nullptr == AniInfoPtr)
	{
		MsgAssert("자식쪽에서 애니메이션을 만들고 해당 정보를 부모에게 넘겨주지 않았습니다");
		return;
	}

	PrevAniFrame = -1;
}

void PlayerStateBase::Update(float _DeltaTime)
{
	StateBase::Update(_DeltaTime);

	SettingRenderTransForAni();
}



void PlayerStateBase::SettingRenderTransForAni()
{
	if (nullptr == SpritePtr || nullptr == AniInfoPtr)
	{
		MsgAssert("자식쪽에서 애니메이션을 만들고 해당 정보를 부모에게 넘겨주지 않았습니다");
		return;
	}

	std::shared_ptr<GameEngineSpriteRenderer> Renderer = FieldPlayer::GetPtr()->GetRenderer();

	//자식에서 직접 애니메이션 크기를 지정해 준 경우
	if (false == AniScale.IsZero() && 
		AniScale != Renderer->GetTransform()->GetLocalScale())
	{
		Renderer->GetTransform()->SetLocalScale(AniScale);
		Renderer->GetTransform()->SetLocalPosition(float4::Up * AniScale.hy());
		return;
	}

	size_t NowAniFrame = AniInfoPtr->CurFrame;
	if (NowAniFrame == PrevAniFrame)
		return;

	//해당 애니메이션 텍스처 크기만큼 렌더러 크기 변경, 렌더러 오프셋 조정
	const SpriteInfo& AniInfo = SpritePtr->GetSpriteInfo(NowAniFrame);
	const float4 TextureSize = float4{ static_cast<float>(AniInfo.Texture->GetWidth()), static_cast<float>(AniInfo.Texture->GetHeight()) } *RCGDefine::ResourceScaleConvertor;
	Renderer->GetTransform()->SetLocalScale(TextureSize);
	Renderer->GetTransform()->SetLocalPosition(float4::Up * TextureSize.hy());

	PrevAniFrame = NowAniFrame;
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