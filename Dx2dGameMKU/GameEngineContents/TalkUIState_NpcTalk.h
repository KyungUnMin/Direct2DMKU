#pragma once
#include "TalkUIStateBase.h"

class GameEngineUIRenderer;

class TalkUIState_NpcTalk : public TalkUIStateBase
{
public:
	TalkUIState_NpcTalk();
	~TalkUIState_NpcTalk() override;

	TalkUIState_NpcTalk(const TalkUIState_NpcTalk& _Other) = delete;
	TalkUIState_NpcTalk(TalkUIState_NpcTalk&& _Other) noexcept = delete;
	TalkUIState_NpcTalk& operator=(const TalkUIState_NpcTalk& _Other) = delete;
	TalkUIState_NpcTalk& operator=(const TalkUIState_NpcTalk&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;
	void Update(float _DeltaTime) override;
	void ExitState() override;

private:
	static const float4 RenderStartPos;
	static const float4 RenderDestPos;

	std::shared_ptr<GameEngineUIRenderer> NpcRender = nullptr;

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

