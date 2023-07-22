#pragma once


enum class GameState
{
	OnField,
	IntroMovie,
	OnlyFieldUI,
	HandPhoneUI,
	Tutorial,
	PlayerKO,
};

class RCG_GameCore
{
public:
	RCG_GameCore(const RCG_GameCore& _Other) = delete;
	RCG_GameCore(RCG_GameCore&& _Other) noexcept = delete;
	RCG_GameCore& operator=(const RCG_GameCore& _Other) = delete;
	RCG_GameCore& operator=(const RCG_GameCore&& _Other) noexcept = delete;

	static void GameStart();
	static void GameEnd();

	static GameState GetCurGameState()
	{
		return CurState;
	}

	static void SetCurGameState(GameState _State)
	{
		CurState = _State;
	}

protected:

private:
	static GameState CurState;
	static std::vector<GameEngineFile> FontFiles;


	static void ContentsResourceInit();
	static void LoadShaders();
	static void CreateBlends();
	static void CreateRenderingPipeLine();

	static void ClonePipeLineForShader(const std::string_view& _PipeName, const std::string_view& _ShaderName);

	RCG_GameCore();
	virtual ~RCG_GameCore() = 0;
};

