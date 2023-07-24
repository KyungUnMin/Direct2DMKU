#include "PrecompileHeader.h"
#include "TalkUIState_FadeOut.h"

#include "RCG_GameCore.h"

#include "TalkUI.h"
#include "UIFontRenderer.h"
#include "FieldLevelBase.h"
#include "DyingMessage.h"

TalkUIState_FadeOut::TalkUIState_FadeOut()
{

}

TalkUIState_FadeOut::~TalkUIState_FadeOut()
{

}

void TalkUIState_FadeOut::EnterState()
{
	TalkUIStateBase::EnterState();

	TalkUI* UIPtr = GetUI();
	UIPtr->GetTextRender()->On();
	UIPtr->GetTalkerNameRender()->Off();
	FieldLevelBase::GetPtr()->GetDyingMsgCtrl()->RenderOn();
}



void TalkUIState_FadeOut::Update(float _DeltaTime)
{
	TalkUIStateBase::Update(_DeltaTime);

	TalkUI* UIPtr = GetUI();
	float Ratio = TalkUIStateBase::GetTalkLiveTime() / TalkUIStateBase::FadeDuration;
	if (Ratio < 1.f)
	{
		const float4 FadeColor = float4::LerpClamp(TalkUIStateBase::FadeDestColor, float4::Null, Ratio);
		UIPtr->SetBackImgColor(FadeColor);
		return;
	}

	GameEngineTime::GlobalTime.SetGlobalTimeScale(1.f);
	RCG_GameCore::SetCurGameState(GameState::OnField);
	UIPtr->Death();
}
