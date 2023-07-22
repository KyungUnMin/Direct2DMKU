#include "PrecompileHeader.h"
#include "PhoneState_Inventory.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineUIRenderer.h>

#include "KeyMgr.h"
#include "RCGEnums.h"
#include "SoundMgr.h"
#include "DataMgr.h"
#include "InventoryMgr.h"
#include "FontMgr.h"

#include "HandPhoneUI.h"
#include "UIFontRenderer.h"

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

const std::vector<std::string_view> PhoneState_Inventory::EatSfxs =
{
	"Phone_Inventory_Eat0.wav",
	"Phone_Inventory_Eat1.wav",
	"Phone_Inventory_Eat2.wav",
};

const float4 PhoneState_Inventory::DataTextColor = float4{0.f, 0.f, 0.f, 1.f};
const float4 PhoneState_Inventory::PreviewTextColor = float4{ 0.f, 0.f, 1.f, 1.f };


PhoneState_Inventory::PhoneState_Inventory()
{

}

PhoneState_Inventory::~PhoneState_Inventory()
{

}

void PhoneState_Inventory::Start() 
{
	PhoneStateBase::Start();

	Cursor = PhoneStateBase::CreateRender("HandPhone_Inven_Cursor.png");

	ItemRenders.resize(Positions.size(), { InvenItemType::Candy, nullptr });
	for (size_t i = 0; i < ItemRenders.size(); ++i)
	{
		ItemRenders[i].second = PhoneStateBase::CreateRender();
		ItemRenders[i].second->GetTransform()->SetLocalPosition(Positions[i]);
	}

	PlayerDataTexts.resize(static_cast<size_t>(DataTextType::COUNT));
	CreateTextRender(DataTextType::Level, FW1_TEXT_FLAG::FW1_CENTER, { 4.f, 57.f });
	CreateTextRender(DataTextType::Exp, FW1_TEXT_FLAG::FW1_LEFT, { -91.f, 63.f });
	CreateTextRender(DataTextType::RemainExp, FW1_TEXT_FLAG::FW1_LEFT, { 89.f, 63.f });
	CreateTextRender(DataTextType::HP, FW1_TEXT_FLAG::FW1_RIGHT, { -30.f, -3.f }, DataTextColor);
	CreateTextRender(DataTextType::MP, FW1_TEXT_FLAG::FW1_RIGHT, { -30.f, -35.f }, DataTextColor);
	CreateTextRender(DataTextType::AP, FW1_TEXT_FLAG::FW1_LEFT, { 60.f, -3.f }, DataTextColor);
	CreateTextRender(DataTextType::SP, FW1_TEXT_FLAG::FW1_LEFT, { 60.f, -35.f }, DataTextColor);
}


void PhoneState_Inventory::CreateTextRender(
	DataTextType _Type,
	FW1_TEXT_FLAG _Align,
	const float4& _Offset /*= float4::Zero*/,
	const float4& _Color /*= float4::White*/,
	float _Scale /*= 20.f*/)
{
	size_t Index = static_cast<size_t>(_Type);
	if (nullptr != PlayerDataTexts[Index])
	{
		MsgAssert("�ش� Ÿ���� �ؽ�Ʈ�� �̹� ������� �ֽ��ϴ�");
		return;
	}

	std::shared_ptr<UIFontRenderer> Render = nullptr;
	Render = GetPhone()->CreateComponent<UIFontRenderer>(FieldUIRenderOrder::Phone);
	Render->SetFont(FontMgr::GetFontName(FontType::Binggrae));
	Render->SetScale(_Scale);
	Render->SetText("0");
	Render->SetColor(_Color);
	Render->SetFontFlag(_Align);

	Render->GetTransform()->SetLocalPosition(_Offset);
	Render->Off();

	PlayerDataTexts[Index] = Render;
}






void PhoneState_Inventory::EnterState() 
{
	PhoneStateBase::EnterState();

	GetPhone()->ChangePhoneTexture("HandPhone_Inven_BackGround.png");

	PhoneStateType PrevUserState = GetPrevUserState();
	if (PhoneStateType::Weapon == PrevUserState)
	{
		NowCursorIndex = 4;
	}
	else if (PhoneStateType::Skill == PrevUserState)
	{
		NowCursorIndex = 0;
	}

	Cursor->On();
	CursorRenderMove();
	SettingItemUI();
	SettingOriginDataRender();
	SettingPreviewDataRender();
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
	for (size_t i = 0; i < ItemRenders.size(); ++i)
	{
		ItemRenders[i].second->Off();
	}

	//�κ��丮 ������ ���� �Ѱ�, �ؽ�ó ����
	for (size_t i = 0; i < Items.size(); ++i)
	{
		ItemRenders[i].second->On();

		size_t TexNameIndex = static_cast<size_t>(Items[i]);
		const std::string_view& TexName = ItemTexNames[TexNameIndex];
		ItemRenders[i].first = Items[i];
		ItemRenders[i].second->SetScaleToTexture(TexName);
	}
}


void PhoneState_Inventory::SettingOriginDataRender()
{
	OriginData.PlayerLevel = DataMgr::GetPlayerLevel();
	OriginData.PlayerExp = DataMgr::GetPlayerExp();
	OriginData.RestExp = (DataMgr::PlayerFullPoint - OriginData.PlayerExp);

	OriginData.PlayerHealthPoint = DataMgr::GetPlayerHP();
	OriginData.PlayerMagicPoint = DataMgr::GetPlayerMP();
	OriginData.PlayerAttackPoint = DataMgr::GetPlayerAtt();
	float PlayerSpeedPer = DataMgr::GetPlayerSpeedPer();
	OriginData.PlayerSP = static_cast<int>(PlayerSpeedPer * 100.f);

	SettingPlayerDataRender(OriginData);

	for (size_t i = 0; i < PlayerDataTexts.size(); ++i)
	{
		PlayerDataTexts[i]->On();
	}
}

void PhoneState_Inventory::SettingPreviewDataRender()
{
	//�ϴ� ��� �ؽ�Ʈ ���� ����(�����̶� ����ġ �κ��� ����)
	for (size_t i = 0; i < PlayerDataTexts.size(); ++i)
	{
		DataTextType Type = static_cast<DataTextType>(i);
		if (DataTextType::Level == Type || DataTextType::Exp == Type || DataTextType::RemainExp == Type)
			continue;

		PlayerDataTexts[i]->SetColor(DataTextColor);
	}

	//�ش� Ŀ���� �������� ���� ���
	if (false == ItemRenders[NowCursorIndex].second->IsUpdate())
	{
		//��� �ؽ�Ʈ�� ���� �÷��̾��� �����ͷ� ����
		SettingPlayerDataRender(OriginData);
		return;
	}

	//Ŀ���� �������� �ִ� ��� �̸����� ������ ����
	PreviewData = OriginData;
	int FullPoint = DataMgr::PlayerFullPoint;
	size_t TextIndex = -1;

	InvenItemType CursorItemType = ItemRenders[NowCursorIndex].first;
	switch (CursorItemType)
	{
	case InvenItemType::Candy:
		PreviewData.PlayerHealthPoint += 15;
		PreviewData.PlayerHealthPoint = std::clamp(PreviewData.PlayerHealthPoint, 0, FullPoint);
		TextIndex = static_cast<size_t>(DataTextType::HP);
		break;
	case InvenItemType::CottonCandy:
		PreviewData.PlayerMagicPoint += 60;
		PreviewData.PlayerMagicPoint = std::clamp(PreviewData.PlayerMagicPoint, 0, FullPoint);
		TextIndex = static_cast<size_t>(DataTextType::MP);
		break;
	case InvenItemType::GummyYummi:
		PreviewData.PlayerAttackPoint += 5;
		TextIndex = static_cast<size_t>(DataTextType::AP);
		break;
	case InvenItemType::MelonMint:
		PreviewData.PlayerSP += 5;
		TextIndex = static_cast<size_t>(DataTextType::SP);
		break;
	case InvenItemType::DoubleBurger:
		PreviewData.PlayerHealthPoint += 60;
		PreviewData.PlayerHealthPoint = std::clamp(PreviewData.PlayerHealthPoint, 0, FullPoint);
		TextIndex = static_cast<size_t>(DataTextType::HP);
		break;
	case InvenItemType::SingleBurger:
		PreviewData.PlayerHealthPoint += 30;
		PreviewData.PlayerHealthPoint = std::clamp(PreviewData.PlayerHealthPoint, 0, FullPoint);
		TextIndex = static_cast<size_t>(DataTextType::HP);
		break;
	case InvenItemType::TeckFried:
		PreviewData.PlayerMagicPoint += 10;
		PreviewData.PlayerMagicPoint = std::clamp(PreviewData.PlayerMagicPoint, 0, FullPoint);
		TextIndex = static_cast<size_t>(DataTextType::MP);
		break;
	case InvenItemType::TeckShake:
		PreviewData.PlayerMagicPoint += 20;
		PreviewData.PlayerMagicPoint = std::clamp(PreviewData.PlayerMagicPoint, 0, FullPoint);
		TextIndex = static_cast<size_t>(DataTextType::MP);
		break;
	}

	//�ؽ�Ʈ ������ ����
	SettingPlayerDataRender(PreviewData);

	//��µǴ� ��ġ�� ���� ����
	PlayerDataTexts[TextIndex]->SetColor(PreviewTextColor);
}

void PhoneState_Inventory::SettingPlayerDataRender(const PlayerData& _Data)
{
	size_t Index = -1;

	Index = static_cast<size_t>(DataTextType::Level);
	PlayerDataTexts[Index]->SetText(GameEngineString::ToString(_Data.PlayerLevel));

	Index = static_cast<size_t>(DataTextType::Exp);
	PlayerDataTexts[Index]->SetText(GameEngineString::ToString(_Data.PlayerExp));

	Index = static_cast<size_t>(DataTextType::RemainExp);
	PlayerDataTexts[Index]->SetText(GameEngineString::ToString(_Data.RestExp));

	Index = static_cast<size_t>(DataTextType::HP);
	PlayerDataTexts[Index]->SetText(GameEngineString::ToString(_Data.PlayerHealthPoint) + "%");

	Index = static_cast<size_t>(DataTextType::MP);
	PlayerDataTexts[Index]->SetText(GameEngineString::ToString(_Data.PlayerMagicPoint) + "%");

	Index = static_cast<size_t>(DataTextType::AP);
	PlayerDataTexts[Index]->SetText(GameEngineString::ToString(_Data.PlayerAttackPoint));

	Index = static_cast<size_t>(DataTextType::SP);
	PlayerDataTexts[Index]->SetText(GameEngineString::ToString(_Data.PlayerSP) + "%");
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

	//TODO : �������ͽ� â


	//������ �Ա�
	if (true == Update_Eat())
		return;

	Update_CursorMove();
}

bool PhoneState_Inventory::Update_Eat()
{
	bool IsEquip = false;
	IsEquip |= KeyMgr::IsDown(KeyNames::Z);
	IsEquip |= KeyMgr::IsDown(KeyNames::X);
	IsEquip |= KeyMgr::IsDown(KeyNames::C);

	//�ƹ� �ϵ� �Ͼ�� ����
	if (false == IsEquip)
		return false;

	if (10 <= NowCursorIndex)
	{
		MsgAssert("�κ��丮 Ŀ���� �ε����� �迭�� ������ �ʰ��Ͽ����ϴ�");
		return false;
	}

	const InvenItemType& ItemType = ItemRenders[NowCursorIndex].first;
	std::shared_ptr<GameEngineUIRenderer> ItemRender = ItemRenders[NowCursorIndex].second;

	//���ִ� ĭ�� ������ ���
	if (false == ItemRender->IsUpdate())
	{
		SoundMgr::PlaySFX("Phone_Inventory_SelectEmpty.wav");
		return false;
	}


	switch (ItemType)
	{
	case InvenItemType::Candy:
		DataMgr::PlusPlayerHP(15);
		break;
	case InvenItemType::CottonCandy:
		DataMgr::PlusPlayerMP(60);
		break;
	case InvenItemType::GummyYummi:
		DataMgr::PlusPlayerAtt(5);
		break;
	case InvenItemType::MelonMint:
		DataMgr::PlusPlayerSpeed(0.05f);
		break;
	case InvenItemType::DoubleBurger:
		DataMgr::PlusPlayerHP(60);
		break;
	case InvenItemType::SingleBurger:
		DataMgr::PlusPlayerHP(30);
		break;
	case InvenItemType::TeckFried:
		DataMgr::PlusPlayerMP(10);
		break;
	case InvenItemType::TeckShake:
		DataMgr::PlusPlayerMP(20);
		break;
	}

	//���� ���
	int RandNum = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(EatSfxs.size() - 1));
	SoundMgr::PlaySFX(EatSfxs[static_cast<size_t>(RandNum)]);

	ItemRender->Off();
	InventoryMgr::Erase(ItemType);

	//�÷��̾� ������ �� ����
	SettingOriginDataRender();

	//�ؽ�Ʈ ������ ����(���� ���� ���..)
	SettingPreviewDataRender();

	return true;
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
	SettingPreviewDataRender();

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
		ItemRenders[i].second->Off();
	}

	for (size_t i = 0; i < PlayerDataTexts.size(); ++i)
	{
		PlayerDataTexts[i]->Off();
	}
}
