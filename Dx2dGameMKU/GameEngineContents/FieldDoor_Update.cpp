#include "PrecompileHeader.h"
#include "FieldDoor.h"

#include <GameEngineCore/GameEngineRenderer.h>

#include "KeyMgr.h"
#include "FieldPlayer.h"


void FieldDoor::CreateScaleState()
{
	ScaleFSM.Resize(State::COUNT);

	ScaleFSM.AddState(State::Wait, SimpleFSMState
	(
		std::bind(&FieldDoor::Update_ScaleWait, this, std::placeholders::_1)
	));

	ScaleFSM.AddState(State::Ready, SimpleFSMState
	(
		std::bind(&FieldDoor::Update_ScaleReady, this, std::placeholders::_1)
	));

	ScaleFSM.ChangeState(State::Wait);
}


void FieldDoor::Update_ScaleWait(float _DeltaTime)
{
	if (false == IsNearPlayer)
		return;

	ScaleFSM.ChangeState(State::Ready);
}



void FieldDoor::Update_ScaleReady(float _DeltaTime)
{
	std::shared_ptr<class GameEngineRenderer> Render = DoorLockValue ? LockRender : UnlockRender;
	if (nullptr == Render)
	{
		MsgAssert("현재 상태에 대한 문 이미지를 만들어주지 않았습니다");
		return;
	}

	GameEngineTransform* RenderTransform = Render->GetTransform();

	float4 OriginScale = float4::Zero;
	switch (ImageType)
	{
	case DoorType::Normal:
		OriginScale = DoorLockValue ? LockDoorScale : UnlockDoorScale;
		break;
	case DoorType::Gym:
		OriginScale = GymIconScale;
		break;
	case DoorType::Shop:
		OriginScale = ShopIconScale;
		break;
	}

	if (false == IsNearPlayer)
	{
		RenderTransform->SetLocalScale(OriginScale);
		ScaleFSM.ChangeState(State::Wait);
		return;
	}

	const float4 MaxAddScale = float4{ 5.f, 5.f };
	const float Duration = 0.25f;
	float LiveTime = ScaleFSM.GetStateLiveTime();

	float Ratio = (LiveTime / Duration);
	float4 NowAddScale = float4::LerpClamp(float4::Zero, MaxAddScale, Ratio);
	float4 NowScale = (OriginScale + NowAddScale);

	//Transform 내부 연산 줄이기 위함
	if (NowScale == RenderTransform->GetLocalScale())
		return;

	RenderTransform->SetLocalScale(NowScale);
}



//------------------------------------------



void FieldDoor::CreateAlphsState()
{
	AlphaFSM.Resize(State::COUNT);

	AlphaFSM.AddState(State::Wait, SimpleFSMState
	(
		std::bind(&FieldDoor::Update_AlphaWait, this, std::placeholders::_1)
	));

	AlphaFSM.AddState(State::Ready, SimpleFSMState
	(
		std::bind(&FieldDoor::Update_AlphaReady, this, std::placeholders::_1)
	));

	AlphaFSM.ChangeState(State::Wait);
}




void FieldDoor::Update_AlphaWait(float _DeltaTime)
{
	if (false == IsNearPlayer)
		return;

	if (false == KeyMgr::IsDown(KeyNames::Space))
		return;

	AlphaFSM.ChangeState(State::Ready);
}


void FieldDoor::Update_AlphaReady(float _DeltaTime) 
{
	if (false == KeyMgr::IsPress(KeyNames::Space) || (false == IsNearPlayer))
	{
		AlphaRatio.x = 0.f;
		AlphaFSM.ChangeState(State::Wait);
		return;
	}

	const float Duration = 0.5f;
	float LiveTime = AlphaFSM.GetStateLiveTime();
	AlphaRatio.x = (LiveTime / Duration);
}