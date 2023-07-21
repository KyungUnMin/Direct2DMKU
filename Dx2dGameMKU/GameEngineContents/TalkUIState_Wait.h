#pragma once
#include "TalkUIStateBase.h"

class TalkUIState_Wait : public TalkUIStateBase
{
public:
	TalkUIState_Wait();
	~TalkUIState_Wait() override;

	TalkUIState_Wait(const TalkUIState_Wait& _Other) = delete;
	TalkUIState_Wait(TalkUIState_Wait&& _Other) noexcept = delete;
	TalkUIState_Wait& operator=(const TalkUIState_Wait& _Other) = delete;
	TalkUIState_Wait& operator=(const TalkUIState_Wait&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:
	std::shared_ptr<class GameEngineCollision> Collider = nullptr;
};

