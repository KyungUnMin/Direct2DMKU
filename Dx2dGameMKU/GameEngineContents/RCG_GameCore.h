#pragma once


class RCG_GameCore
{
public:
	RCG_GameCore();
	~RCG_GameCore();

	RCG_GameCore(const RCG_GameCore& _Other) = delete;
	RCG_GameCore(RCG_GameCore&& _Other) noexcept = delete;
	RCG_GameCore& operator=(const RCG_GameCore& _Other) = delete;
	RCG_GameCore& operator=(const RCG_GameCore&& _Other) noexcept = delete;

	static void GameStart();
	static void ContentsResourceInit();
	static void GameEnd();

protected:

private:
	static void LoadShaders();
	static void CreateBlends();
	static void CreateRenderingPipeLine();

	static void ClonePipeLineForShader(const std::string_view& _PipeName, const std::string_view& _ShaderName);
};

