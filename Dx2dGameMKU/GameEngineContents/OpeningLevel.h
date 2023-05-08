#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class GameEngineVideo;

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
	void Update(float _DeltaTime) override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class GameEngineVideo> OpeningVideo = nullptr;
	std::shared_ptr<class OpeningActor> OpeningCtrl = nullptr;

};

