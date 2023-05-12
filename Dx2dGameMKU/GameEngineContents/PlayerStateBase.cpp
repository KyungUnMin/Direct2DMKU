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
	////어차피 플레이어는 게임이 끝날때 모두 동시에 죽을 것 같다
	//if (nullptr != SpritePtr)
	//{
	//	SpritePtr = nullptr;
	//}
}




void PlayerStateBase::Start()
{
	StateBase::Start();
	BGPtr = FieldLevelBase::GetPtr()->GetBackGround();
	Renderer = FieldPlayer::GetPtr()->GetRenderer();
}

void PlayerStateBase::SetAnimationInfo(std::shared_ptr<GameEngineSprite> _SpritePtr, std::shared_ptr<AnimationInfo> _AniInfoPtr)
{
	SpritePtr = _SpritePtr;
	AniInfoPtr = _AniInfoPtr;
	
	AniFrameOffset.resize(SpritePtr->GetSpriteCount(), float4::Zero);
}

void PlayerStateBase::SetAniFrameOffset(size_t _Index, const float4& _Offset)
{
	if (SpritePtr->GetSpriteCount() <= _Index)
	{
		MsgAssert("애니메이션 인덱스 배열을 넘겼습니다");
		return;
	}

	AniFrameOffset[_Index] = _Offset;
}



void PlayerStateBase::EnterState()
{
	StateBase::EnterState();
	
	if (nullptr == SpritePtr || nullptr == AniInfoPtr)
	{
		MsgAssert("자식쪽에서 애니메이션을 만들고 해당 정보를 부모에게 넘겨주지 않았습니다");
		return;
	}

}





void PlayerStateBase::Update(float _DeltaTime)
{
	StateBase::Update(_DeltaTime);

	//UPDATE_DEBUG_ANI_OFFSET();

	SettingRenderTransForAni();
}



void PlayerStateBase::SettingRenderTransForAni()
{
	if (nullptr == SpritePtr || nullptr == AniInfoPtr)
	{
		MsgAssert("자식쪽에서 애니메이션을 만들고 해당 정보를 부모에게 넘겨주지 않았습니다");
		return;
	}


	//현재 애니메이션의 텍스처 크기를 가져옴
	size_t NowAniFrame = AniInfoPtr->CurFrame;
	const SpriteInfo& AniInfo = SpritePtr->GetSpriteInfo(NowAniFrame);
	const float4 TextureSize = AniInfo.Texture->GetScale() * RCGDefine::ResourceScaleConvertor;


	std::shared_ptr<FieldPlayer> PlayerPtr = FieldPlayer::GetPtr();

	//해당 애니메이션 텍스처 크기만큼 렌더러 크기 변경
	float Height = PlayerPtr->GetHeight();
	GameEngineTransform* RenderTrans = Renderer->GetTransform();
	RenderTrans->SetLocalScale(TextureSize);

	//플레이어의 높이 + 텍스처 절반 높이만큼 오프셋
	float4 FinalOffest = float4::Up * (TextureSize.hy() + Height);
	
	//자식쪽에서 설정해준 별개의 오프셋
	float4 Offset = AniFrameOffset[NowAniFrame];

	//플레이어가 왼쪽을 보고 있다면 오프셋을 반전
	bool IsPlayerDirectionRight = PlayerPtr->IsRightDir();
	if (false == IsPlayerDirectionRight)
	{
		Offset.x = -Offset.x;
	}

	RenderTrans->SetLocalPosition(FinalOffest + Offset);

	//오른쪽을 바라봐야 하는 경우
	if (true == IsPlayerDirectionRight)
	{
		Renderer->GetTransform()->SetLocalPositiveScaleX();
	}
	//왼쪽을 바라봐야 하는 경우
	else
	{
		Renderer->GetTransform()->SetLocalNegativeScaleX();
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



#include "GUIManager.h"
#include "GameEngineActorGUI.h"


void PlayerStateBase::UPDATE_DEBUG_ANI_OFFSET()
{

	size_t FrameIndex = AniInfoPtr->CurFrame;

	if (nullptr == TransformViewer)
	{
		TransformViewer = GUIManager::Find<GameEngineActorGUI>();
		TransformViewer->SetTarget(&DEBUG_ANI_OFFSET);

		static bool DebugOn = false;
		if (false == DebugOn)
		{
			MsgTextBox("PlayerStateBase.cpp에서 GameEngineActorGUI가 활성화 되었습니다");
			DebugOn = true;
		}
	}


	AniFrameOffset[FrameIndex] = DEBUG_ANI_OFFSET.GetLocalPosition();
}
