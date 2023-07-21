#include "PrecompileHeader.h"
#include "TalkUIStateBase.h"

#include "KeyMgr.h"

#include "TalkUI.h"
#include "TalkUIFSM.h"
#include "UIFontRenderer.h"
#include <GameEngineCore/GameEngineUIRenderer.h>

const float TalkUIStateBase::FadeDuration = 0.2f;
const float4 TalkUIStateBase::FadeDestColor = float4{ 0.f, 0.f, 0.f ,0.5f };
const float TalkUIStateBase::RenderMoveDuration = 0.5f;

GameEngineTime TalkUIStateBase::Time;

TalkUIStateBase::TalkUIStateBase()
{

}

TalkUIStateBase::~TalkUIStateBase()
{

}


void TalkUIStateBase::Start()
{
	StateBase::Start();

	TalkFsm = GetConvertFSM<TalkUIFSM>();
	UIPtr = TalkFsm->GetUI();
}

void TalkUIStateBase::EnterState()
{
	StateBase::EnterState();
	Time.Reset();
	TalkLiveTime = 0.f;
}


void TalkUIStateBase::Update(float _DeltaTime)
{
	StateBase::Update(_DeltaTime);

	float DeltaTime = Time.TimeCheck();
	TalkLiveTime += DeltaTime;
}


void TalkUIStateBase::ChangeState(TalkUIState _NextState)
{
	TalkFsm->ChangeState<TalkUIState >(_NextState);
}

bool TalkUIStateBase::SkipTalk()
{
	if (false == KeyMgr::IsDown(KeyNames::Esc))
		return false;

	TalkUIState CurState = TalkFsm->GetNowState<TalkUIState>();
	if (TalkUIState::FadeIn == CurState)
	{
		MsgAssert("FadeIn상태에서는 TalkUIStateBase::SkipTalk 함수를 호출시킬수 없습니다");
	}

	if (TalkUIState::FadeOut == CurState)
	{
		MsgAssert("FadeOut상태에서는 TalkUIStateBase::SkipTalk 함수를 호출시킬수 없습니다");
	}

	if (TalkUIState::Wait == CurState)
	{
		MsgAssert("Wait상태에서는 TalkUIStateBase::SkipTalk 함수를 호출시킬수 없습니다");
	}

	ChangeState(TalkUIState::FadeOut);
	return true;
}

bool TalkUIStateBase::MoveRenderTrans(const float4& _Start, const float4& _Dest, GameEngineTransform* _Target)
{
	float Ratio = GetTalkLiveTime() / RenderMoveDuration;

	if (true == KeyMgr::IsDown(KeyNames::Z)
		|| true == KeyMgr::IsDown(KeyNames::X)
		|| true == KeyMgr::IsDown(KeyNames::C))
	{
		Ratio = 10.f;
	}

	const float4 RenderPos = float4::LerpClamp(_Start, _Dest, Ratio);
	_Target->SetLocalPosition(RenderPos);

	return (1.f <= Ratio);
}


void TalkUIStateBase::ChangeNextTalkState()
{
	TalkUIState CurState = TalkFsm->GetNowState<TalkUIState>();
	if ((TalkUIState::PlayerTalk != CurState) && (TalkUIState::NpcTalk != CurState))
	{
		MsgAssert("TalkUIStateBase::NextScriptState함수는 TalkUIState::PlayerTalk상태나 TalkUIState::NpcTalk 상태에서만 호출할 수 있습니다");
		return;
	}

	if (true == UIPtr->IsScriptEmpty())
	{
		ChangeState(TalkUIState::FadeOut);
		return;
	}

	const TextUI_ScripteInfo& Script = GetUI()->PickScript();
	if (true == Script.IsPlayerTalk)
	{
		ChangeState(TalkUIState::PlayerTalk);
	}
	else
	{
		ChangeState(TalkUIState::NpcTalk);
	}
}


void TalkUIStateBase::SettingScript(const std::string_view& _ScriptLine)
{
	ScriptLine.clear();
	CurText.clear();

	ScriptLine = GameEngineString::AnsiToUniCode(_ScriptLine);
	ScriptIndex = 0;
}


bool TalkUIStateBase::Update_TextRender(float _Duration)
{
	if (true == KeyMgr::IsDown(KeyNames::Z)
		|| true == KeyMgr::IsDown(KeyNames::X)
		|| true == KeyMgr::IsDown(KeyNames::C))
	{
		UIPtr->GetTextRender()->SetText(GameEngineString::UniCodeToAnsi(ScriptLine));
		return true;
	}

	if (TalkLiveTime < _Duration)
		return false;

	if (ScriptLine.size() <= ScriptIndex)
		return true;

	ResetTalkLiveTime();
	CurText = ScriptLine.substr(0, ++ScriptIndex);
	UIPtr->GetTextRender()->SetText(GameEngineString::UniCodeToAnsi(CurText));
	return false;
}

