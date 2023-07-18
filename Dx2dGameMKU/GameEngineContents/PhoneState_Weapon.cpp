#include "PrecompileHeader.h"
#include "PhoneState_Weapon.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "KeyMgr.h"
#include "RCGEnums.h"

#include "HandPhoneUI.h"


const std::vector<float4> PhoneState_Weapon::CursorPoses
{
	{-88.f, -33.f},	{-28.f, -33.f},	{32.f, -33.f},		{92.f, -33.f},
	{-88.f, -97.f},	{-28.f, -97.f},	{32.f, -97.f},		{92.f, -97.f},
};

PhoneState_Weapon::PhoneState_Weapon()
{

}

PhoneState_Weapon::~PhoneState_Weapon()
{

}


void PhoneState_Weapon::Start() 
{
	PhoneStateBase::Start();

	Cursor = GetPhone()->CreateComponent<GameEngineUIRenderer>(FieldUIRenderOrder::Phone);
	Cursor->SetScaleToTexture("HandPhone_Weapone_Cursor.png");
	Cursor->Off();
}

void PhoneState_Weapon::EnterState() 
{
	PhoneStateBase::EnterState();

	GetPhone()->ChangePhoneTexture("HandPhone_Weapon_BackGround.png");

	NowCursorIndex = 0;
	PhoneStateType LastUserState = GetPhoneFSM()->GetLastUserState();
	if (PhoneStateType::Skill == LastUserState)
	{
		NowCursorIndex = 3;
	}

	Cursor->On();
	MoveCursorRender();
}


void PhoneState_Weapon::MoveCursorRender()
{
	GameEngineTransform* CursorTrans = Cursor->GetTransform();
	const float4& CursorPos = CursorPoses[NowCursorIndex];
	CursorTrans->SetLocalPosition(CursorPos);
}

void PhoneState_Weapon::Update(float _DeltaTime)
{
	PhoneStateBase::Update(0.f);

	//오른쪽 키를 누른경우
	if (true == KeyMgr::IsDown(KeyNames::RightArrow))
	{
		//커서가 가장 오른쪽에 있던 경우
		if (3 == NowCursorIndex || 7 == NowCursorIndex)
		{
			//FSM 기술쪽으로 변경
			return;
		}
		
		++NowCursorIndex;
	}

	//왼쪽 키를 누른 경우
	else if (true == KeyMgr::IsDown(KeyNames::LeftArrow))
	{
		//커서가 가장 왼쪽에 있던 경우
		if (0 == NowCursorIndex || 4 == NowCursorIndex)
		{
			//FSM 소지품쪽으로 변경
			return;
		}

		--NowCursorIndex;
	}

	//위쪽 키를 누른 경우
	else if (true == KeyMgr::IsDown(KeyNames::UpArrow))
	{
		//커서가 위쪽에 있던 경우 아래쪽으로 이동
		if (NowCursorIndex < 4)
		{
			NowCursorIndex = NowCursorIndex + 4;
		}
		//커서가 아래쪽에 있던 경우 위쪽으로 이동
		else
		{
			NowCursorIndex = NowCursorIndex - 4;
		}
	}

	//아래쪽 키를 누른 경우
	else if (true == KeyMgr::IsDown(KeyNames::DownArrow))
	{
		//커서가 위쪽에 있던 경우
		if (NowCursorIndex < 4)
		{
			NowCursorIndex = NowCursorIndex + 4;
		}
		//커서가 아래쪽에 있던 경우
		else
		{
			NowCursorIndex = NowCursorIndex - 4;
		}
	}

	//커서 위치 이동
	MoveCursorRender();
}

void PhoneState_Weapon::ExitState()
{
	PhoneStateBase::ExitState();

	PhoneStateType NextState = GetFSM()->GetNowState<PhoneStateType>();
	if (false == IsUserState(NextState))
		return;
		
	//TODO
}

