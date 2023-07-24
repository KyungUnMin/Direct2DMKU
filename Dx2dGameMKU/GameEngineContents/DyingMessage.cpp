#include "PrecompileHeader.h"
#include "DyingMessage.h"

#include <GameEngineBase/GameEngineRandom.h>

#include "FontMgr.h"

#include "UIFontRenderer.h"


DyingMessage::DyingMessage()
{

}

DyingMessage::~DyingMessage()
{

}


void DyingMessage::Start() 
{
	UIBase::Start();

	const float4 NameOffset = float4{ -450.f, -302.f };
	const float4 ValueOffset = float4{ -430.f, -302.f };


	MsgNameRender = CreateComponent<UIFontRenderer>(FieldUIRenderOrder::DyingMsg);
	MsgValueRender = CreateComponent<UIFontRenderer>(FieldUIRenderOrder::DyingMsg);

	MsgNameRender->SetFont(FontMgr::GetFontName(FontType::Binggrae));
	MsgNameRender->SetScale(30);
	MsgNameRender->SetColor(float4::White);
	MsgNameRender->SetFontFlag(FW1_TEXT_FLAG::FW1_RIGHT);

	MsgValueRender->SetFont(FontMgr::GetFontName(FontType::Binggrae));
	MsgValueRender->SetScale(30);
	MsgValueRender->SetColor(float4::White);
	MsgValueRender->SetFontFlag(FW1_TEXT_FLAG::FW1_LEFT);

	MsgNameRender->GetTransform()->SetLocalPosition(NameOffset);
	MsgValueRender->GetTransform()->SetLocalPosition(ValueOffset);

	RenderOff();
}







void DyingMessage::SetMsg(EnemyType _Type)
{
	std::string_view OwnerName = "";
	std::string_view MsgValue = "";
	float4 Color = float4::White;


	//이름
	size_t OwnerIndex = static_cast<size_t>(_Type);
	if (MsgOwnerNames.size() <= OwnerIndex)
	{
		MsgAssert("인자로 들어온 타입이 다잉메세지 스크립트의 배열의 범위를 초과하였습니다");
		return;
	}
	OwnerName = MsgOwnerNames[OwnerIndex];
	if (true == OwnerName.empty())
		return;



	//메세지 내용
	if (MsgScript.size() <= OwnerIndex)
	{
		MsgAssert("인자로 들어온 타입이 다잉메세지 스크립트의 배열의 범위를 초과하였습니다");
		return;
	}
	const std::vector<std::string_view>& OwnerScript = MsgScript[OwnerIndex];
	int RandNum = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(OwnerScript.size() - 1));
	MsgValue = OwnerScript[static_cast<size_t>(RandNum)];


	//색상
	if (MsgColors.size() <= OwnerIndex)
	{
		MsgAssert("인자로 들어온 타입이 다잉메세지 스크립트의 배열의 범위를 초과하였습니다");
		return;
	}
	Color = MsgColors[OwnerIndex];


	MsgNameRender->SetText(OwnerName);
	MsgValueRender->SetText("");
	MsgNameRender->SetColor(Color);

	CurState = State::Print;
	Message = GameEngineString::AnsiToUniCode(MsgValue);
	Cursor = 0;
	

	RenderOn();
	ResetLiveTime();
}


void DyingMessage::RenderOff()
{
	MsgNameRender->Off();
	MsgValueRender->Off();
}

void DyingMessage::RenderOn() 
{
	MsgNameRender->On();
	MsgValueRender->On();
}



void DyingMessage::Update(float _DeltaTime) 
{
	UIBase::Update(_DeltaTime);

	switch (CurState)
	{
	case DyingMessage::State::Ready:
		break;
	case DyingMessage::State::Print:
		Update_Print(_DeltaTime);
		break;
	case DyingMessage::State::Wait:
		Update_Wait(_DeltaTime);
		break;
	}
}




void DyingMessage::Update_Print(float _DeltaTime)
{
	static const float Duration = 0.05f;
	if (GetLiveTime() < Duration)
		return;

	++Cursor;
	if (Message.size() <= Cursor)
	{
		MsgValueRender->SetText(GameEngineString::UniCodeToAnsi(Message));
		CurState = State::Wait;
		ResetLiveTime();
		return;
	}

	std::string SubString = GameEngineString::UniCodeToAnsi(Message.substr(0, Cursor));
	MsgValueRender->SetText(SubString);
}

void DyingMessage::Update_Wait(float _DeltaTime)
{
	static const float Duration = 2.f;
	if (GetLiveTime() < Duration)
		return;

	RenderOff();
	CurState = State::Ready;
	ResetLiveTime();
}



void DyingMessage::LevelChangeEnd()
{
	UIBase::LevelChangeEnd();
	RenderOff();
}