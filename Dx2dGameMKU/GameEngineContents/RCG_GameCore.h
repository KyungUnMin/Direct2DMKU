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
	static void GameEnd();

protected:

private:

};

