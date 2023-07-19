#include "PrecompileHeader.h"
#include "PhoneState_Inventory.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "KeyMgr.h"
#include "RCGEnums.h"
#include "SoundMgr.h"
#include "DataMgr.h"
#include "InventoryMgr.h"

#include "HandPhoneUI.h"

const std::vector<float4> PhoneState_Inventory::Positions =
{
	{-118.f, -118.f	},	{-58.f, -118.f},		{2.f, -118.f},		{62.f, -118.f	},	{123.f, -118.f},
	{-118.f, -179.f	},	{-58.f, -179.f},		{2.f, -179.f},		{62.f, -179.f	},	{123.f, -179.f},
};

const std::vector<std::string_view> PhoneState_Inventory::ItemTexNames =
{
	"HandPhone_Inven_Candy.png",
	"HandPhone_Inven_CottonCandy.png",
	"HandPhone_Inven_GummyYummi.png",
	"HandPhone_Inven_MelonMint.png",

	"HandPhone_Inven_DoubleBurger.png",
	"HandPhone_Inven_SingleBurger.png",
	"HandPhone_Inven_TeckFried.png",
	"HandPhone_Inven_TeckShake.png",
};

PhoneState_Inventory::PhoneState_Inventory()
{

}

PhoneState_Inventory::~PhoneState_Inventory()
{

}

#include "GUIManager.h"
#include "GameEngineActorGUI.h"
#include "CrossTownLevel1.h"
#include "FieldLevelBase.h"


void PhoneState_Inventory::Start() 
{
	PhoneStateBase::Start();

	Cursor = PhoneStateBase::CreateRender("HandPhone_Inven_Cursor.png");

	ItemRenders.resize(Positions.size());
	for (size_t i = 0; i < ItemRenders.size(); ++i)
	{
		ItemRenders[i] = PhoneStateBase::CreateRender();
		ItemRenders[i]->GetTransform()->SetLocalPosition(Positions[i]);
	}

	/*if (nullptr == std::dynamic_pointer_cast<CrossTownLevel1>(FieldLevelBase::GetPtr()))
		return;
	
	GUIManager::CreateGui<GameEngineActorGUI>()->SetTarget(Cursor->GetTransform());*/
}

void PhoneState_Inventory::EnterState() 
{
	PhoneStateBase::EnterState();

	GetPhone()->ChangePhoneTexture("HandPhone_Inven_BackGround.png");

	Cursor->On();
	CursorRenderMove();
	SettingItemUI();
}


void PhoneState_Inventory::CursorRenderMove()
{
	if (Positions.size() <= NowCursorIndex)
	{
		MsgAssert("�κ��丮�� Ŀ���� �迭�� ������ �ʰ��Ͽ� �����Ͽ����ϴ�");
		return;
	}

	Cursor->GetTransform()->SetLocalPosition(Positions[NowCursorIndex]);
}


void PhoneState_Inventory::SettingItemUI()
{
	std::vector<InvenItemType> Items = InventoryMgr::GetItems();
	if (Positions.size() < Items.size())
	{
		MsgAssert("�κ��丮 �Ŵ����� �ִ� �������� ������ �κ��丮 â���� ǥ���� �� �ִ� ������ �������� ���� �����մϴ�");
		return;
	}

	//�ϴ� ��� ����
	for (std::shared_ptr<GameEngineUIRenderer> ItemRender : ItemRenders)
	{
		ItemRender->Off();
	}

	//�κ��丮 ������ ���� �Ѱ�, �ؽ�ó ����
	for (size_t i = 0; i < Items.size(); ++i)
	{
		ItemRenders[i]->On();

		size_t TexNameIndex = static_cast<size_t>(Items[i]);
		const std::string_view& TexName = ItemTexNames[TexNameIndex];
		ItemRenders[i]->SetScaleToTexture(TexName);
	}
}


void PhoneState_Inventory::Update(float _DeltaTime) 
{
	PhoneStateBase::Update(0.f);

	//ESC�� �������� Close�� ����
	if (true == KeyMgr::IsDown(KeyNames::Esc))
	{
		GetPhoneFSM()->ChangeState(PhoneStateType::Close);
		return;
	}

	//TODO : Ȯ�� ��ư

	Update_CursorMove();
}


void PhoneState_Inventory::Update_CursorMove()
{
	bool IsMove = false;

	//������ Ű�� �������
	if (true == KeyMgr::IsDown(KeyNames::RightArrow))
	{
		//Ŀ���� ���� �����ʿ� �ִ� ���
		if (4 == NowCursorIndex || 9 == NowCursorIndex)
		{
			SoundMgr::PlaySFX("Phone_ChangeUserState.wav");
			GetPhoneFSM()->ChangeState(PhoneStateType::Weapon);
			return;
		}

		++NowCursorIndex;
		IsMove = true;
	}

	//���� Ű�� ���� ���
	else if (true == KeyMgr::IsDown(KeyNames::LeftArrow))
	{
		//Ŀ���� ���� ���ʿ� �ִ� ���
		if (0 == NowCursorIndex || 5 == NowCursorIndex)
		{
			SoundMgr::PlaySFX("Phone_ChangeUserState.wav");
			GetPhoneFSM()->ChangeState(PhoneStateType::Skill);
			return;
		}

		--NowCursorIndex;
		IsMove = true;
	}

	//���� Ű�� ���� ���
	else if (true == KeyMgr::IsDown(KeyNames::UpArrow))
	{
		//Ŀ���� ���ʿ� �ִ� ��� �Ʒ������� �̵�
		if (NowCursorIndex < 5)
		{
			NowCursorIndex = NowCursorIndex + 5;
		}
		//Ŀ���� �Ʒ��ʿ� �ִ� ��� �������� �̵�
		else
		{
			NowCursorIndex = NowCursorIndex - 5;
		}

		IsMove = true;
	}

	//�Ʒ��� Ű�� ���� ���
	else if (true == KeyMgr::IsDown(KeyNames::DownArrow))
	{
		//Ŀ���� ���ʿ� �ִ� ���
		if (NowCursorIndex < 5)
		{
			NowCursorIndex = NowCursorIndex + 5;
		}
		//Ŀ���� �Ʒ��ʿ� �ִ� ���
		else
		{
			NowCursorIndex = NowCursorIndex - 5;
		}

		IsMove = true;
	}

	if (false == IsMove)
		return;

	//Ŀ�� ��ġ �̵�
	CursorRenderMove();

	if (0 == NowCursorIndex || 1 == NowCursorIndex)
	{
		//SoundMgr::PlaySFX("Phone_Weapon_MoveCursor.wav").SetVolume(0.5f);
	}
	else
	{
		//SoundMgr::PlaySFX("Phone_Inventory_CursorMove.wav");
	}

	SoundMgr::PlaySFX("Phone_Inventory_CursorMove.wav");
}



void PhoneState_Inventory::ExitState() 
{
	PhoneStateBase::ExitState();

	PhoneStateType NextState = GetFSM()->GetNowState<PhoneStateType>();
	if (false == IsUserState(NextState))
		return;

	Cursor->Off();
	for (size_t i = 0; i < ItemRenders.size(); ++i)
	{
		ItemRenders[i]->Off();
	}
}
