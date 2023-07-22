#pragma once
#include "UIBase.h"
#include <queue>

class GameEngineLevel;
class UIFontRenderer;
class GameEngineUIRenderer;

class TutorialUI : public UIBase
{
public:
	static void Update_CheckCallBack(GameEngineLevel* _Level);

	static void BindTurorial(
	const std::string_view& _Title,
	const std::string_view& _Desc, 
	std::function<bool()> _CheckFunc = nullptr);

private:
	struct TutorialData
	{
		std::function<bool()> CheckFunc = nullptr;
		std::string_view TutoTitle = "";
		std::string_view TutoDesc = "";
	};

	static std::list<TutorialData> AllCallBack;
	static std::queue<TutorialData> JopQueue;
	static TutorialUI* TutorialPtr;

	//-------------------STATIC---------------

public:
	TutorialUI();
	~TutorialUI() override;

	TutorialUI(const TutorialUI& _Other) = delete;
	TutorialUI(TutorialUI&& _Other) noexcept = delete;
	TutorialUI& operator=(const TutorialUI& _Other) = delete;
	TutorialUI& operator=(const TutorialUI&& _Other) noexcept = delete;

	void Init(const std::string_view& _Title, const std::string_view& _Desc);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void Destroy() override;

private:
	static GameEngineTime NewTime;
	static const std::vector<std::string_view> TexFileNames;
	static const float4 MoveStart;
	static const float4 MoveDest;

	enum class State
	{
		MoveIn,
		Wait,
		MoveOut,
	};


	std::shared_ptr<GameEngineUIRenderer> BoxRender = nullptr;
	std::shared_ptr<UIFontRenderer> TitleRender = nullptr;
	std::shared_ptr<UIFontRenderer> DescRender = nullptr;

	State CurState = State::MoveIn;

	const float AniDuration = 0.25f;
	const float MoveDuration = 0.5f;
	const float WaitDuration = 2.f;

	size_t TexIndex = 0;
	float AniTimer = 0.f;
	float MoveTimer = 0.f;
	


	void LoadImgRes();
	void CreateRenders();

	void Update_Ani(float _DeltaTime);
	bool Update_Move(float _DeltaTime, const float4& _Start, const float4& _Dest);

	void Update_MoveIn(float _DeltaTime);
	void Update_Wait(float _DeltaTime);
	void Update_MoveOut(float _DeltaTime);
};

