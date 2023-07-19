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
		MsgAssert("인벤토리의 커서가 배열의 영역을 초과하여 접근하였습니다");
		return;
	}

	Cursor->GetTransform()->SetLocalPosition(Positions[NowCursorIndex]);
}


void PhoneState_Inventory::SettingItemUI()
{
	std::vector<InvenItemType> Items = InventoryMgr::GetItems();
	if (Positions.size() < Items.size())
	{
		MsgAssert("인벤토리 매니저에 있는 아이템의 갯수가 인벤토리 창에서 표현할 수 있는 아이템 갯수보다 많이 존재합니다");
		return;
	}

	//일단 모두 끄기
	for (std::shared_ptr<GameEngineUIRenderer> ItemRender : ItemRenders)
	{
		ItemRender->Off();
	}

	//인벤토리 정보에 따라 켜고, 텍스처 세팅
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

	//ESC를 눌렀을땐 Close로 변경
	if (true == KeyMgr::IsDown(KeyNames::Esc))
	{
		GetPhoneFSM()->ChangeState(PhoneStateType::Close);
		return;
	}

	//TODO : 확인 버튼

	Update_CursorMove();
}


void PhoneState_Inventory::Update_CursorMove()
{
	bool IsMove = false;

	//오른쪽 키를 누른경우
	if (true == KeyMgr::IsDown(KeyNames::RightArrow))
	{
		//커서가 가장 오른쪽에 있던 경우
		if (4 == NowCursorIndex || 9 == NowCursorIndex)
		{
			SoundMgr::PlaySFX("Phone_ChangeUserState.wav");
			GetPhoneFSM()->ChangeState(PhoneStateType::Weapon);
			return;
		}

		++NowCursorIndex;
		IsMove = true;
	}

	//왼쪽 키를 누른 경우
	else if (true == KeyMgr::IsDown(KeyNames::LeftArrow))
	{
		//커서가 가장 왼쪽에 있던 경우
		if (0 == NowCursorIndex || 5 == NowCursorIndex)
		{
			SoundMgr::PlaySFX("Phone_ChangeUserState.wav");
			GetPhoneFSM()->ChangeState(PhoneStateType::Skill);
			return;
		}

		--NowCursorIndex;
		IsMove = true;
	}

	//위쪽 키를 누른 경우
	else if (true == KeyMgr::IsDown(KeyNames::UpArrow))
	{
		//커서가 위쪽에 있던 경우 아래쪽으로 이동
		if (NowCursorIndex < 5)
		{
			NowCursorIndex = NowCursorIndex + 5;
		}
		//커서가 아래쪽에 있던 경우 위쪽으로 이동
		else
		{
			NowCursorIndex = NowCursorIndex - 5;
		}

		IsMove = true;
	}

	//아래쪽 키를 누른 경우
	else if (true == KeyMgr::IsDown(KeyNames::DownArrow))
	{
		//커서가 위쪽에 있던 경우
		if (NowCursorIndex < 5)
		{
			NowCursorIndex = NowCursorIndex + 5;
		}
		//커서가 아래쪽에 있던 경우
		else
		{
			NowCursorIndex = NowCursorIndex - 5;
		}

		IsMove = true;
	}

	if (false == IsMove)
		return;

	//커서 위치 이동
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
