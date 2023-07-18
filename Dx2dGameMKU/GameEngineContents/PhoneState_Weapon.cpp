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

	//������ Ű�� �������
	if (true == KeyMgr::IsDown(KeyNames::RightArrow))
	{
		//Ŀ���� ���� �����ʿ� �ִ� ���
		if (3 == NowCursorIndex || 7 == NowCursorIndex)
		{
			//FSM ��������� ����
			return;
		}
		
		++NowCursorIndex;
	}

	//���� Ű�� ���� ���
	else if (true == KeyMgr::IsDown(KeyNames::LeftArrow))
	{
		//Ŀ���� ���� ���ʿ� �ִ� ���
		if (0 == NowCursorIndex || 4 == NowCursorIndex)
		{
			//FSM ����ǰ������ ����
			return;
		}

		--NowCursorIndex;
	}

	//���� Ű�� ���� ���
	else if (true == KeyMgr::IsDown(KeyNames::UpArrow))
	{
		//Ŀ���� ���ʿ� �ִ� ��� �Ʒ������� �̵�
		if (NowCursorIndex < 4)
		{
			NowCursorIndex = NowCursorIndex + 4;
		}
		//Ŀ���� �Ʒ��ʿ� �ִ� ��� �������� �̵�
		else
		{
			NowCursorIndex = NowCursorIndex - 4;
		}
	}

	//�Ʒ��� Ű�� ���� ���
	else if (true == KeyMgr::IsDown(KeyNames::DownArrow))
	{
		//Ŀ���� ���ʿ� �ִ� ���
		if (NowCursorIndex < 4)
		{
			NowCursorIndex = NowCursorIndex + 4;
		}
		//Ŀ���� �Ʒ��ʿ� �ִ� ���
		else
		{
			NowCursorIndex = NowCursorIndex - 4;
		}
	}

	//Ŀ�� ��ġ �̵�
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

