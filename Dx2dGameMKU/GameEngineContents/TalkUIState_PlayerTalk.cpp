#include "PrecompileHeader.h"
#include "TalkUIState_PlayerTalk.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "RCGEnums.h"

#include "TalkUI.h"
#include "UIFontRenderer.h"

const float4 TalkUIState_PlayerTalk::RenderStartPos = float4{ -1200.f, -100.f };
const float4 TalkUIState_PlayerTalk::RenderDestPos = float4{ -300.f, -100.f};

TalkUIState_PlayerTalk::TalkUIState_PlayerTalk()
{

}

TalkUIState_PlayerTalk::~TalkUIState_PlayerTalk()
{

}


void TalkUIState_PlayerTalk::Start() 
{
	TalkUIStateBase::Start();

	TalkUI* UIPtr = GetUI();
	PlayerRender = UIPtr->CreateComponent<GameEngineUIRenderer>(FieldUIRenderOrder::Conversation);
	PlayerRender->GetTransform()->SetLocalPosition(RenderStartPos);
	PlayerRender->Off();
}

void TalkUIState_PlayerTalk::EnterState() 
{
	TalkUIStateBase::EnterState();

	TalkUI* UIPtr = GetUI();

	const TextUI_ScripteInfo& Script = UIPtr->PopScript();
	PlayerRender->SetScaleToTexture(Script.TexName);
	PlayerRender->On();

	TalkUIStateBase::SettingScript(Script.TextValue);
	UIPtr->GetTalkerNameRender()->SetText(Script.TalkerName);
	CurState = State::Appear;
}

void TalkUIState_PlayerTalk::Update(float _DeltaTime) 
{
	TalkUIStateBase::Update(_DeltaTime);

	if (true == TalkUIStateBase::SkipTalk())
		return;

	switch (CurState)
	{
	case TalkUIState_PlayerTalk::State::Appear:
		Update_Appear(_DeltaTime);
		break;
	case TalkUIState_PlayerTalk::State::Talk:
		Update_Talk(_DeltaTime);
		break;
	case TalkUIState_PlayerTalk::State::Wait:
		Update_Wait(_DeltaTime);
		break;
	case TalkUIState_PlayerTalk::State::Disappear:
		Update_Disappear(_DeltaTime);
		break;
	}
}

void TalkUIState_PlayerTalk::Update_Appear(float _DeltaTime)
{
	bool IsMoveFinish = TalkUIStateBase::MoveRenderTrans(RenderStartPos, RenderDestPos, PlayerRender->GetTransform());
	if (false == IsMoveFinish)
		return;

	CurState = State::Talk;
	ResetTalkLiveTime();
}

void TalkUIState_PlayerTalk::Update_Talk(float _DeltaTime)
{
	if (false == TalkUIStateBase::Update_TextRender())
		return;

	CurState = State::Wait;
	ResetTalkLiveTime();
}


void TalkUIState_PlayerTalk::Update_Wait(float _DeltaTime)
{
	if (GetTalkLiveTime() < 0.5f)
		return;

	CurState = State::Disappear;
	ResetTalkLiveTime();
}


void TalkUIState_PlayerTalk::Update_Disappear(float _DeltaTime) 
{
	bool IsMoveFinish = TalkUIStateBase::MoveRenderTrans(RenderDestPos, RenderStartPos, PlayerRender->GetTransform());
	if (false == IsMoveFinish)
		return;

	TalkUIStateBase::ChangeNextTalkState();
}


void TalkUIState_PlayerTalk::ExitState()
{
	TalkUIStateBase::ExitState();

	PlayerRender->Off();
	CurState = State::Appear;
	GetUI()->GetTextRender()->SetText("");
}