#pragma once


class ContentsCore
{
public:
	ContentsCore();
	~ContentsCore();

	ContentsCore(const ContentsCore& _Other) = delete;
	ContentsCore(ContentsCore&& _Other) noexcept = delete;
	ContentsCore& operator=(const ContentsCore& _Other) = delete;
	ContentsCore& operator=(const ContentsCore&& _Other) noexcept = delete;

	static void GameStart();
	static void GameEnd();

protected:

private:
	
};

