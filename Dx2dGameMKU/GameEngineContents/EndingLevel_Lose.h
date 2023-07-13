#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class EndingLevel_Lose : public GameEngineLevel
{
public:
	EndingLevel_Lose();
	~EndingLevel_Lose();

	EndingLevel_Lose(const EndingLevel_Lose& _Other) = delete;
	EndingLevel_Lose(EndingLevel_Lose&& _Other) noexcept = delete;
	EndingLevel_Lose& operator=(const EndingLevel_Lose& _Other) = delete;
	EndingLevel_Lose& operator=(const EndingLevel_Lose&& _Other) noexcept = delete;

protected:
	void Start() override;
	//void Update(float _DeltaTime) override;

private:

};

