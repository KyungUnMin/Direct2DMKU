#pragma once
#include "UIBase.h"

class GameEngineUIRenderer;
class UIFontRenderer;

class ContinueBox : public UIBase
{
public:
	ContinueBox();
	~ContinueBox() override;

	ContinueBox(const ContinueBox& _Other) = delete;
	ContinueBox(ContinueBox&& _Other) noexcept = delete;
	ContinueBox& operator=(const ContinueBox& _Other) = delete;
	ContinueBox& operator=(const ContinueBox&& _Other) noexcept = delete;

	inline void Init(std::function<void()> _ContinueCallBack)
	{
		ContinueCallBack = _ContinueCallBack;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::vector<std::string_view> Box_Textures;
	static const std::string_view Cursor_FileName;
	static const float4 CursorOffsets[2];
	static const std::pair<float4, float4> MoveOffsets;

	static GameEngineTime NewTime;
	static const float MoveDuration;

	std::function<void()> ContinueCallBack = nullptr;

	std::shared_ptr<GameEngineUIRenderer> BoxRender = nullptr;
	std::shared_ptr<GameEngineUIRenderer> CursorRender = nullptr;

	std::shared_ptr<UIFontRenderer> LeftSelectRender = nullptr;
	std::shared_ptr<UIFontRenderer> RightSelectRender = nullptr;

	size_t CursorIndex = 0;
	size_t BoxAniIndex = 0;
	float BoxAniTimer = 0.f;
	float NewLiveTime = 0.f;


	enum class State
	{
		Raise,
		Wait,
		Sink,
	};

	State CurState = State::Raise;

	void LoadResImage();
	void CreateRenders();
	void CreateTexts();

	void Update_Raise();
	void Update_BoxAni(float _DeltaTime);
	void Update_Wait();
	void Update_Sink();

	bool Update_Move(const float4& _Start, const float4& _Dest);
};

