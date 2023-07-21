#pragma once
#include "TalkUIStateBase.h"

class GameEngineUIRenderer;

class TalkUIState_PlayerTalk : public TalkUIStateBase
{
public:
	TalkUIState_PlayerTalk();
	~TalkUIState_PlayerTalk() override;

	TalkUIState_PlayerTalk(const TalkUIState_PlayerTalk& _Other) = delete;
	TalkUIState_PlayerTalk(TalkUIState_PlayerTalk&& _Other) noexcept = delete;
	TalkUIState_PlayerTalk& operator=(const TalkUIState_PlayerTalk& _Other) = delete;
	TalkUIState_PlayerTalk& operator=(const TalkUIState_PlayerTalk&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;
	void Update(float _DeltaTime) override;
	void ExitState() override;

private:
	static const float4 RenderStartPos;
	static const float4 RenderDestPos;

	std::shared_ptr<GameEngineUIRenderer> PlayerRender = nullptr;


	enum class State
	{
		Appear,
		Talk,
		Wait,
		Disappear,
	};

	State CurState = State::Appear;

	void Update_Appear(float _DeltaTime);
	void Update_Talk(float _DeltaTime);
	void Update_Wait(float _DeltaTime);
	void Update_Disappear(float _DeltaTime);
};

