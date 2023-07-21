#pragma once
#include "TalkUIStateBase.h"

class TalkUIState_FadeOut : public TalkUIStateBase
{
public:
	TalkUIState_FadeOut();
	~TalkUIState_FadeOut();

	TalkUIState_FadeOut(const TalkUIState_FadeOut& _Other) = delete;
	TalkUIState_FadeOut(TalkUIState_FadeOut&& _Other) noexcept = delete;
	TalkUIState_FadeOut& operator=(const TalkUIState_FadeOut& _Other) = delete;
	TalkUIState_FadeOut& operator=(const TalkUIState_FadeOut&& _Other) noexcept = delete;

protected:
	void EnterState() override;
	void Update(float _DeltaTime) override;

private:

};

