#pragma once
#include "TalkUIStateBase.h"

class TalkUIState_FadeIn : public TalkUIStateBase
{
public:
	TalkUIState_FadeIn();
	~TalkUIState_FadeIn();

	TalkUIState_FadeIn(const TalkUIState_FadeIn& _Other) = delete;
	TalkUIState_FadeIn(TalkUIState_FadeIn&& _Other) noexcept = delete;
	TalkUIState_FadeIn& operator=(const TalkUIState_FadeIn& _Other) = delete;
	TalkUIState_FadeIn& operator=(const TalkUIState_FadeIn&& _Other) noexcept = delete;

protected:
	void EnterState() override;
	void Update(float _DeltaTime) override;
	void ExitState() override;

private:
	float Timer = 0.f;
};

