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

	//�� ��� ���̵� ��
	UIPtr->SetBackImgColor(TalkUIStateBase::FadeDestColor);

	//��ũ��Ʈ ���� ���ִ��� ����ó��
	if (true == UIPtr->IsScriptEmpty())
	{
		MsgAssert("TalkUI�� ������ ��ȭ������ �����ϴ�");
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