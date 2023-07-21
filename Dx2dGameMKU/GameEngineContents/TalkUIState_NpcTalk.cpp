#include "PrecompileHeader.h"
#include "TalkUIState_NpcTalk.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "RCGEnums.h"

#include "TalkUI.h"
#include "UIFontRenderer.h"

const float4 TalkUIState_NpcTalk::RenderStartPos = float4{ 1200.f, -100.f };
const float4 TalkUIState_NpcTalk::RenderDestPos = float4{ 300.f, -100.f };

TalkUIState_NpcTalk::TalkUIState_NpcTalk()
{

}

TalkUIState_NpcTalk::~TalkUIState_NpcTalk()
{

}


void TalkUIState_NpcTalk::Start()
{
	TalkUIStateBase::Start();

	TalkUI* UIPtr = GetUI();
	NpcRender = UIPtr->CreateComponent<GameEngineUIRenderer>(FieldUIRenderOrder::Conversation);
	NpcRender->GetTransform()->SetLocalPosition(RenderStartPos);
	NpcRender->Off();
}

void TalkUIState_NpcTalk::EnterState()
{
	TalkUIStateBase::EnterState();

	TalkUI* UIPtr = GetUI();

	const TextUI_ScripteInfo& Script = UIPtr->PopScript();
	NpcRender->SetScaleToTexture(Script.TexName);
	NpcRender->On();

	TalkUIStateBase::SettingScript(Script.TextValue);
	UIPtr->GetTalkerNameRender()->SetText(Script.TalkerName);
	CurState = State::Appear;
}

void TalkUIState_NpcTalk::Update(float _DeltaTime)
{
	TalkUIStateBase::Update(_DeltaTime);

	if (true == TalkUIStateBase::SkipTalk())
		return;

	switch (CurState)
	{
	case TalkUIState_NpcTalk::State::Appear:
		Update_Appear(_DeltaTime);
		break;
	case TalkUIState_NpcTalk::State::Talk:
		Update_Talk(_DeltaTime);
		break;
	case TalkUIState_NpcTalk::State::Wait:
		Update_Wait(_DeltaTime);
		break;
	case TalkUIState_NpcTalk::State::Disappear:
		Update_Disappear(_DeltaTime);
		break;
	}
}

void TalkUIState_NpcTalk::Update_Appear(float _DeltaTime)
{
	bool IsMoveFinish = TalkUIStateBase::MoveRenderTrans(RenderStartPos, RenderDestPos, NpcRender->GetTransform());
	if (false == IsMoveFinish)
		return;

	CurState = State::Talk;
	ResetTalkLiveTime();
}

void TalkUIState_NpcTalk::Update_Talk(float _DeltaTime)
{
	if (false == TalkUIStateBase::Update_TextRender())
		return;

	CurState = State::Wait;
	ResetTalkLiveTime();
}


void TalkUIState_NpcTalk::Update_Wait(float _DeltaTime)
{
	if (GetTalkLiveTime() < 0.5f)
		return;

	CurState = State::Disappear;
	ResetTalkLiveTime();
}


void TalkUIState_NpcTalk::Update_Disappear(float _DeltaTime)
{
	bool IsMoveFinish = TalkUIStateBase::MoveRenderTrans(RenderDestPos, RenderStartPos, NpcRender->GetTransform());
	if (false == IsMoveFinish)
		return;

	TalkUIStateBase::ChangeNextTalkState();
}


void TalkUIState_NpcTalk::ExitState()
{
	TalkUIStateBase::ExitState();

	NpcRender->Off();
	CurState = State::Appear;
	GetUI()->GetTextRender()->SetText("");
}