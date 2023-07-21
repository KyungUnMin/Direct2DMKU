#pragma once
#include "StateBase.h"

class TalkUIFSM;
class TalkUI;
enum class TalkUIState;
class GameEngineTransform;

class TalkUIStateBase : public StateBase
{
public:
	TalkUIStateBase();
	~TalkUIStateBase() override;

	TalkUIStateBase(const TalkUIStateBase& _Other) = delete;
	TalkUIStateBase(TalkUIStateBase&& _Other) noexcept = delete;
	TalkUIStateBase& operator=(const TalkUIStateBase& _Other) = delete;
	TalkUIStateBase& operator=(const TalkUIStateBase&& _Other) noexcept = delete;

protected:
	static const float FadeDuration;
	static const float4 FadeDestColor;
	static const float RenderMoveDuration;


	void EnterState() override;
	void Start() override;
	void Update(float _DeltaTime) override;

	inline TalkUIFSM* GetTalkFsm() const
	{
		return TalkFsm;
	}

	inline TalkUI* GetUI() const 
	{
		return UIPtr;
	}

	void ChangeState(TalkUIState _NextState);

	inline float GetTalkLiveTime()
	{
		return TalkLiveTime;
	}

	inline void ResetTalkLiveTime()
	{
		TalkLiveTime = 0.f;
	}

	bool SkipTalk();

	bool MoveRenderTrans(const float4& _Start, const float4& _Dest, GameEngineTransform* _Target);

	void ChangeNextTalkState();

	

	void SettingScript(const std::string_view& _ScriptLine);

	bool Update_TextRender(float _Duration = 0.05f);



private:
	static GameEngineTime Time;

	TalkUIFSM* TalkFsm = nullptr;
	TalkUI* UIPtr = nullptr;
	float TalkLiveTime = 0.f;


	std::wstring CurText;
	std::wstring ScriptLine;
	size_t ScriptIndex = 0;
};

