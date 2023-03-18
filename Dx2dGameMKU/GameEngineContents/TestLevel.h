#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class TestLevel : public GameEngineLevel
{
public:
	TestLevel();
	~TestLevel() override;

	TestLevel(const TestLevel& _Other) = delete;
	TestLevel(TestLevel&& _Other) noexcept = delete;
	TestLevel& operator=(const TestLevel& _Other) = delete;
	TestLevel& operator=(const TestLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;

private:

};

