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
	////������ �÷��̾�� ������ ������ ��� ���ÿ� ���� �� ����
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
		MsgAssert("�ִϸ��̼� �ε��� �迭�� �Ѱ���ϴ�");
		return;
	}

	AniFrameOffset[_Index] = _Offset;
}



void PlayerStateBase::EnterState()
{
	StateBase::EnterState();
	
	if (nullptr == SpritePtr || nullptr == AniInfoPtr)
	{
		MsgAssert("�ڽ��ʿ��� �ִϸ��̼��� ����� �ش� ������ �θ𿡰� �Ѱ����� �ʾҽ��ϴ�");
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
		MsgAssert("�ڽ��ʿ��� �ִϸ��̼��� ����� �ش� ������ �θ𿡰� �Ѱ����� �ʾҽ��ϴ�");
		return;
	}


	//���� �ִϸ��̼��� �ؽ�ó ũ�⸦ ������
	size_t NowAniFrame = AniInfoPtr->CurFrame;
	const SpriteInfo& AniInfo = SpritePtr->GetSpriteInfo(NowAniFrame);
	const float4 TextureSize = AniInfo.Texture->GetScale() * RCGDefine::ResourceScaleConvertor;


	std::shared_ptr<FieldPlayer> PlayerPtr = FieldPlayer::GetPtr();

	//�ش� �ִϸ��̼� �ؽ�ó ũ�⸸ŭ ������ ũ�� ����
	float Height = PlayerPtr->GetHeight();
	GameEngineTransform* RenderTrans = Renderer->GetTransform();
	RenderTrans->SetLocalScale(TextureSize);

	//�÷��̾��� ���� + �ؽ�ó ���� ���̸�ŭ ������
	float4 FinalOffest = float4::Up * (TextureSize.hy() + Height);
	
	//�ڽ��ʿ��� �������� ������ ������
	float4 Offset = AniFrameOffset[NowAniFrame];

	//�÷��̾ ������ ���� �ִٸ� �������� ����
	bool IsPlayerDirectionRight = PlayerPtr->IsRightDir();
	if (false == IsPlayerDirectionRight)
	{
		Offset.x = -Offset.x;
	}

	RenderTrans->SetLocalPosition(FinalOffest + Offset);

	//�������� �ٶ���� �ϴ� ���
	if (true == IsPlayerDirectionRight)
	{
		Renderer->GetTransform()->SetLocalPositiveScaleX();
	}
	//������ �ٶ���� �ϴ� ���
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
		MsgAssert("�÷��̾ �������� �ʽ��ϴ�");
		return;
	}

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
			MsgTextBox("PlayerStateBase.cpp���� GameEngineActorGUI�� Ȱ��ȭ �Ǿ����ϴ�");
			DebugOn = true;
		}
	}


	AniFrameOffset[FrameIndex] = DEBUG_ANI_OFFSET.GetLocalPosition();
}
