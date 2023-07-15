#include "PrecompileHeader.h"
#include "ShopItem_CursorBar.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "RCGEnums.h"
#include "RCGDefine.h"
#include "KeyMgr.h"
#include "SoundMgr.h"

#include "Shop_GymLevel.h"
#include "ShopSlotController.h"

const std::string_view ShopItem_CursorBar::BarRenderName = "ShopUI_SelectionBar.png";
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
	//���� Ȯ�� �ǻ縦 ���� �ڽ�
	std::shared_ptr<GameEngineUIRenderer> ConfirmBox = CreateComponent<GameEngineUIRenderer>(ShopUIRenderOrder::Cursor);
	ConfirmBox->SetTexture(ConfirmRenderName);
	ConfirmBoxTrans = ConfirmBox->GetTransform();
	ConfirmBoxTrans->SetLocalScale(ConfirmRenderScale);
	ConfirmBoxTrans->SetLocalPosition(ConfirmInnerOffset);

	//�������� ������ �� �ִ� �ڽ�
	std::shared_ptr<GameEngineUIRenderer> BarRender = CreateComponent<GameEngineUIRenderer>(ShopUIRenderOrder::Cursor);
	BarRender->SetTexture(BarRenderName);
	BarRender->GetTransform()->SetLocalScale(BarRenderScale);

	//���� ������ ü������ ���
	if (nullptr != dynamic_cast<Shop_GymLevel*>(GetLevel()))
	{
		BarFirstPos = GymBarFirstPos;
		BarLastPos = GymBarLastPos;
	}

	GetTransform()->SetLocalPosition(BarFirstPos);

	MaxCursor = ShopSlotController::MaxSlot;
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

	//Ȯ�� �˾��� ���ִ� ��쿣 Ŀ�� �̵��� �����Ǿ� ����
	if (true == IsConfirmation)
	{
		if ((true == IsPushDown) || (true == IsPushUp))
		{
			SoundMgr::PlaySFX("Shop_Cursor_CantMove.wav").SetVolume(0.5f);
		}
		return;
	}

	//Ŀ�� �̵��� ����ƴ��� ����
	bool IsPosChanged = false;

	//�Ʒ�Ű�� ���� ���
	if (true == IsPushDown)
	{
		//�Ʒ��� �̵��Ҽ� ���ٸ�
		if (MaxCursor == CurrentIndex)
		{
			SoundMgr::PlaySFX("Shop_Cursor_CantMove.wav").SetVolume(0.5f);
			return;
		}

		//�̵��Ҽ� �ִٸ�
		IsPosChanged = true;
		++CurrentIndex;
	}

	//���� Ű�� ���� ���
	else if (true == IsPushUp)
	{
		//���� �̵��Ҽ� ���ٸ�
		if (CurrentIndex == 0)
		{
			SoundMgr::PlaySFX("Shop_Cursor_CantMove.wav").SetVolume(0.5f);
			return;
		}

		//�̵��� �� �ִٸ�
		IsPosChanged = true;
		--CurrentIndex;
	}

	//�̹� �����ӿ��� Ŀ���� �̵���������
	if (false == IsPosChanged)
		return;

	//ȿ���� �� ��ġ ����
	SoundMgr::PlaySFX("Shop_Cursor_Move.wav").SetVolume(0.3f);
	const float Ratio = static_cast<float>(CurrentIndex) / static_cast<float>(MaxCursor);
	float4 NextPos = float4::LerpClamp(BarFirstPos, BarLastPos, Ratio);
	GetTransform()->SetLocalPosition(NextPos);
}

void ShopItem_CursorBar::Update_ComfirmMove(float _DeltaTime)
{
	//Ȯ�� �˾�â ��ȣ�ۿ� ó��
	InteractConfilm();

	//Ȯ�� �˾�â �̵� ����
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

	//Ok��ư�̳� Back��ư�� ��� ������ ���� ���
	if (false == IsPushOk && false == IsPushBack)
		return false;

	//Ȯ�� �˾��� ���� �ʾҴµ�, �� ��ư�� ���� ���
	if (false == IsConfirmation && true == IsPushBack)
	{
		SoundMgr::PlaySFX("Shop_Cursor_CantMove.wav").SetVolume(0.5f);
		return false;
	}

	//Ȯ�� �˾��� ���� �ʾҴµ�, OK��ư�� ���� ���
	if (false == IsConfirmation && true == IsPushOk)
	{
		SoundMgr::PlaySFX("Shop_Cursur_Ok.wav").SetVolume(0.2f);
	}

	//Ȯ�� �˾��� ���ִµ�, OK��ư�� ���� ���
	else if (true == IsConfirmation && true == IsPushOk)
	{
		//���� �ӽ�
		SoundMgr::PlaySFX("Shop_Cursur_Ok.wav").SetVolume(0.2f);
		//�ݹ� ȣ��
	}

	//Ȯ�� �˾��� ���ִµ�, Back��ư�� ���� ���
	else if (true == IsConfirmation && true == IsPushBack)
	{
		SoundMgr::PlaySFX("Shop_Cursor_Back.wav").SetVolume(0.3f);
	}


	IsConfirmation = !IsConfirmation;
	ConfirmTime = 0.f;
	return true;
}




void ShopItem_CursorBar::Reset()
{
	CurrentIndex = 0;

	ConfirmTime = -1.f;
	IsConfirmation = false;
	GetTransform()->SetLocalPosition(BarFirstPos);
	ConfirmBoxTrans->SetLocalPosition(ConfirmInnerOffset);
}
