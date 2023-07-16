#include "PrecompileHeader.h"
#include "ShopItem_CursorBar.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "RCGEnums.h"
#include "RCGDefine.h"
#include "KeyMgr.h"
#include "SoundMgr.h"

#include "Shop_GymLevel.h"
#include "ShopSlotController.h"
#include "ShopItemBlockBase.h"
#include "ShopUI_ResultText.h"

std::weak_ptr<GameEngineUIRenderer> ShopItem_CursorBar::CursorBar;

const std::string_view ShopItem_CursorBar::ConfirmRenderName = "ShopUI_ConfirmBox.png";

const float4 ShopItem_CursorBar::ConfirmRenderScale = float4{ 200.f, 140.f } *0.7f;
const float4 ShopItem_CursorBar::BarRenderScale = float4{ 610.f, 255.f } * 0.7f;

const float4 ShopItem_CursorBar::ShopBarFirstPos = float4{ 370.f, 30.f };
const float4 ShopItem_CursorBar::ShopBarLastPos = float4{ 320.f, -200.f };

const float4 ShopItem_CursorBar::GymBarFirstPos = float4{ 350.f, 70.f };
const float4 ShopItem_CursorBar::GymBarLastPos = float4{ 300.f, -180.f };

const float4 ShopItem_CursorBar::ConfirmInnerOffset = { -100.f, 25.f, 0.f };
const float4 ShopItem_CursorBar::ConfirmOutOffset = { -280.f, 50.f, 0.f };

size_t ShopItem_CursorBar::CurrentIndex = 0;




ShopItem_CursorBar::ShopItem_CursorBar()
{

}

ShopItem_CursorBar::~ShopItem_CursorBar()
{
	
}


void ShopItem_CursorBar::Start()
{
	//구매 확인 의사를 묻는 박스
	std::shared_ptr<GameEngineUIRenderer> ConfirmBox = CreateComponent<GameEngineUIRenderer>(ShopUIRenderOrder::Cursor);
	ConfirmBox->SetTexture(ConfirmRenderName);
	ConfirmBoxTrans = ConfirmBox->GetTransform();
	ConfirmBoxTrans->SetLocalScale(ConfirmRenderScale);
	ConfirmBoxTrans->SetLocalPosition(ConfirmInnerOffset);

	//아이템을 선택할 수 있는 박스
	BarRender = CreateComponent<GameEngineUIRenderer>(ShopUIRenderOrder::Cursor);
	BarRender->GetTransform()->SetLocalScale(BarRenderScale);

	//현제 레벨이 체육관인 경우
	if (nullptr != dynamic_cast<Shop_GymLevel*>(GetLevel()))
	{
		BarFirstPos = GymBarFirstPos;
		BarLastPos = GymBarLastPos;
	}

	GetTransform()->SetLocalPosition(BarFirstPos);

	MaxCursor = ShopSlotController::MaxSlot;
}


void ShopItem_CursorBar::CreateItemDescRender()
{
	std::list<std::shared_ptr<GameEngineActor>> AllItemData;
	AllItemData = GetLevel()->GetActorGroup(UpdateOrder::ShopItemData);

	if (AllItemData.size() != (ShopSlotController::MaxSlot + 1))
	{
		MsgAssert("슬롯의 갯수가 잘못되었습니다");
		return;
	}

	AllItemDesc.resize(AllItemData.size());
	for (std::shared_ptr<GameEngineActor> ItemDataActor : AllItemData)
	{
		std::shared_ptr<ShopItemBlockBase> ItemData = nullptr;
		ItemData = std::dynamic_pointer_cast<ShopItemBlockBase>(ItemDataActor);
		if (nullptr == ItemData)
		{
			MsgAssert("UpdateOrder::ShopItemData그룹에 ShopItemBlockBase가 아닌 다른 객체가 존재합니다");
			return;
		}



		int Index = ItemData->GetIndex();
		const float Ratio = static_cast<float>(Index) / static_cast<float>(MaxCursor);
		float4 DescWorldPos = float4::LerpClamp(BarFirstPos, BarLastPos, Ratio);

		std::shared_ptr<GameEngineUIRenderer> DescRender = nullptr;
		DescRender = CreateComponent<GameEngineUIRenderer>(ShopUIRenderOrder::Desc);
		
		GameEngineTransform* DescTrans = DescRender->GetTransform();
		DescTrans->SetLocalScale(BarRenderScale);
		DescTrans->SetWorldPosition(DescWorldPos);

		DescRender->SetTexture(ItemData->GetInfoTexName());
		if (0 == Index)
		{
			DescRender->Off();
		}

		AllItemDesc[static_cast<size_t>(Index)] = DescRender;
	}
}


void ShopItem_CursorBar::LevelChangeStart()
{
	GameEngineActor::LevelChangeStart();
	CursorBar = BarRender;
}




void ShopItem_CursorBar::ChangeCursorTex(const std::string_view& _CursorTex)
{
	if (true == CursorBar.expired())
	{
		MsgAssert("CursorBar가 nullptr이여서 커서의 텍스처를 변경할 수 없습니다");
		return;
	}

	std::shared_ptr<GameEngineUIRenderer> BarRender = CursorBar.lock();
	BarRender->SetTexture(_CursorTex);
}



void ShopItem_CursorBar::Update(float _DeltaTime)
{
	Update_CursorMove();
	Update_ComfirmMove(_DeltaTime);
}




void ShopItem_CursorBar::Update_CursorMove()
{
	bool IsPushDown = KeyMgr::IsDown(KeyNames::DownArrow);
	bool IsPushUp = KeyMgr::IsDown(KeyNames::UpArrow);

	if (false == IsPushDown && false == IsPushUp)
		return;

	//확인 팝업이 떠있는 경우엔 커서 이동이 금지되어 있음
	if (true == IsConfirmation)
	{
		if ((true == IsPushDown) || (true == IsPushUp))
		{
			SoundMgr::PlaySFX("Shop_Cursor_CantMove.wav").SetVolume(0.5f);
		}
		return;
	}

	//커서 이동이 변경됐는지 유무
	bool IsPosChanged = false;

	//아래키를 누른 경우
	if (true == IsPushDown)
	{
		//아래로 이동할수 없다면
		if (MaxCursor == CurrentIndex)
		{
			SoundMgr::PlaySFX("Shop_Cursor_CantMove.wav").SetVolume(0.5f);
			return;
		}

		//이동할수 있다면
		IsPosChanged = true;
		++CurrentIndex;
	}

	//위쪽 키를 누른 경우
	else if (true == IsPushUp)
	{
		//위로 이동할수 없다면
		if (CurrentIndex == 0)
		{
			SoundMgr::PlaySFX("Shop_Cursor_CantMove.wav").SetVolume(0.5f);
			return;
		}

		//이동할 수 있다면
		IsPosChanged = true;
		--CurrentIndex;
	}

	//이번 프레임에서 커서가 이동했을때만
	if (false == IsPosChanged)
		return;

	//현재 커서에 따라 아이템 정보렌더 On/Off
	PerceiveCursorMove();

	//효과음 및 위치 변경
	SoundMgr::PlaySFX("Shop_Cursor_Move.wav").SetVolume(0.3f);
	const float Ratio = static_cast<float>(CurrentIndex) / static_cast<float>(MaxCursor);
	float4 NextPos = float4::LerpClamp(BarFirstPos, BarLastPos, Ratio);
	GetTransform()->SetLocalPosition(NextPos);
}

void ShopItem_CursorBar::PerceiveCursorMove()
{
	for (size_t i = 0; i < AllItemDesc.size(); ++i)
	{
		if (i == CurrentIndex)
		{
			AllItemDesc[i]->Off();
		}
		else
		{
			AllItemDesc[i]->On();
		}
	}
}




void ShopItem_CursorBar::Update_ComfirmMove(float _DeltaTime)
{
	//확인 팝업창 상호작용 처리
	InteractConfilm();

	//확인 팝업창 이동 연출
	const float Duration = 0.2f;

	if (ConfirmTime < 0.f)
		return;

	ConfirmTime += _DeltaTime;

	float Ratio = (ConfirmTime / Duration);
	if (1.1f < Ratio)
		return;

	float4 NextOffset = float4::Zero;
	if (true == IsConfirmation)
	{
		NextOffset = float4::LerpClamp(ConfirmInnerOffset, ConfirmOutOffset, Ratio);
	}
	else
	{
		NextOffset = float4::LerpClamp(ConfirmOutOffset, ConfirmInnerOffset, Ratio);
	}

	if (NextOffset == ConfirmBoxTrans->GetLocalPosition())
		return;

	ConfirmBoxTrans->SetLocalPosition(NextOffset);
}

bool ShopItem_CursorBar::InteractConfilm()
{
	bool IsPushOk = KeyMgr::IsDown(KeyNames::Z);
	bool IsPushBack = KeyMgr::IsDown(KeyNames::X);

	//Ok버튼이나 Back버튼을 모두 누르지 않은 경우
	if (false == IsPushOk && false == IsPushBack)
		return false;
	

	//확인 팝업이 뜨지 않았는데, 백 버튼을 누른 경우
	if (false == IsConfirmation && true == IsPushBack)
	{
		SoundMgr::PlaySFX("Shop_Cursor_CantMove.wav").SetVolume(0.5f);
		return false;
	}

	//확인 팝업이 뜨지 않았는데, OK버튼을 누른 경우
	if (false == IsConfirmation && true == IsPushOk)
	{
		SoundMgr::PlaySFX("Shop_Cursur_Ok.wav").SetVolume(0.2f);
	}

	//확인 팝업이 떠있는데, OK버튼을 누른 경우
	else if (true == IsConfirmation && true == IsPushOk)
	{
		//사운드 임시(구매 사운드 따로 찾아서 넣자)
		//SoundMgr::PlaySFX("Shop_Cursur_Ok.wav").SetVolume(0.2f);
		BuyItem();
	}

	//확인 팝업이 떠있는데, Back버튼을 누른 경우
	else if (true == IsConfirmation && true == IsPushBack)
	{
		SoundMgr::PlaySFX("Shop_Cursor_Back.wav").SetVolume(0.3f);
	}


	IsConfirmation = !IsConfirmation;
	ConfirmTime = 0.f;
	return true;
}

void ShopItem_CursorBar::BuyItem()
{
	int SelectIndex = static_cast<int>(CurrentIndex);

	std::list<std::shared_ptr<GameEngineActor>> AllItemData;
	AllItemData = GetLevel()->GetActorGroup(UpdateOrder::ShopItemData);
	for (std::shared_ptr<GameEngineActor> ItemDataActor : AllItemData)
	{
		std::shared_ptr<ShopItemBlockBase> ItemData = nullptr;
		ItemData = std::dynamic_pointer_cast<ShopItemBlockBase>(ItemDataActor);
		if (nullptr == ItemData)
		{
			MsgAssert("UpdateOrder::ShopItemData그룹에 ShopItemBlockBase가 아닌 다른 객체가 존재합니다");
			return;
		}

		int ItemIndex = ItemData->GetIndex();
		if (SelectIndex != ItemIndex)
			continue;

		ShopResultType Result = ItemData->IsAvailable();
		SetResultText(Result);

		if (ShopResultType::BuyOk == Result)
		{
			SoundMgr::PlaySFX("Shop_Buy.wav");
			ItemData->Buy();
		}
		else
		{
			SoundMgr::PlaySFX("Shop_CantBuy.mp3");
		}
		return;
	}
}

void ShopItem_CursorBar::SetResultText(ShopResultType _Result)
{
	ShopUI_ResultText* ResultText = ShopUI_ResultText::GetGPtr();
	float4 ThisWorldPos = GetTransform()->GetWorldPosition();

	ResultText->TextOn(_Result);
	ResultText->GetTransform()->SetWorldPosition(ThisWorldPos);
}



void ShopItem_CursorBar::Reset()
{
	CurrentIndex = 0;
	PerceiveCursorMove();

	ConfirmTime = -1.f;
	IsConfirmation = false;
	GetTransform()->SetLocalPosition(BarFirstPos);
	ConfirmBoxTrans->SetLocalPosition(ConfirmInnerOffset);
}



