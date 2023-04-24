#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class OpeningLevel : public GameEngineLevel
{
public:
	OpeningLevel();
	~OpeningLevel() override;

	OpeningLevel(const OpeningLevel& _Other) = delete;
	OpeningLevel(OpeningLevel&& _Other) noexcept = delete;
	OpeningLevel& operator=(const OpeningLevel& _Other) = delete;
	OpeningLevel& operator=(const OpeningLevel&& _Other) noexcept = delete;

protected:
	void Start() override;


private:
	

};

