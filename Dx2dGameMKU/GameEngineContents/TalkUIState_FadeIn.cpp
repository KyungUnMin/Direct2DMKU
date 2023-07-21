#include "PrecompileHeader.h"
#include "TalkUIState_FadeIn.h"


#include "RCG_GameCore.h"

#include "TalkUI.h"
#include "ShaderUIRenderer.h"
#include "UIFontRenderer.h"

TalkUIState_FadeIn::TalkUIState_FadeIn()
{

}

TalkUIState_FadeIn::~TalkUIState_FadeIn()
{

}

void TalkUIState_FadeIn::EnterState()
{
	TalkUIStateBase::EnterState();

	GameEngineTime::GlobalTime.SetGlobalTimeScale(0.f);
	RCG_GameCore::SetCurGameState(GameState::OnlyFieldUI);

	GetUI()->GetBackRender()->On();
}

void TalkUIState_FadeIn::Update(float _DeltaTime)
{
	TalkUIStateBase::Update(_DeltaTime);

	TalkUI* UIPtr = GetUI();
	float Ratio = TalkUIStateBase::GetTalkLiveTime() / TalkUIStateBase::FadeDuration;
	if (Ratio < 1.f)
	{
		const float4 FadeColor = float4::LerpClamp(float4::Null, TalkUIStateBase::FadeDestColor, Ratio);
		UIPtr->SetBackImgColor(FadeColor);
		return;
	}

	//뒷 배경 페이드 인
	UIPtr->SetBackImgColor(TalkUIStateBase::FadeDestColor);

	//스크립트 내용 비여있는지 예외처리
	if (true == UIPtr->IsScriptEmpty())
	{
		MsgAssert("TalkUI에 지정된 대화내용이 없습니다");
		return;
	}

	const TextUI_ScripteInfo& Script = UIPtr->PickScript();
	if (true == Script.IsPlayerTalk)
	{
		ChangeState(TalkUIState::PlayerTalk);
	}
	else
	{
		ChangeState(TalkUIState::NpcTalk);
	}
}


void TalkUIState_FadeIn::ExitState()
{
	TalkUIStateBase::ExitState();

	TalkUI* UIPtr = GetUI();
	UIPtr->GetTextRender()->On();
	UIPtr->GetTalkerNameRender()->On();
}