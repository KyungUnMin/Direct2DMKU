#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class EndingLevel_Win : public GameEngineLevel
{
public:
	EndingLevel_Win();
	~EndingLevel_Win();

	EndingLevel_Win(const EndingLevel_Win& _Other) = delete;
	EndingLevel_Win(EndingLevel_Win&& _Other) noexcept = delete;
	EndingLevel_Win& operator=(const EndingLevel_Win& _Other) = delete;
	EndingLevel_Win& operator=(const EndingLevel_Win&& _Other) noexcept = delete;

protected:
	void Start() override;
	void LevelChangeStart() override;
	void Update(float _DeltaTime) override;

private:

	
};

