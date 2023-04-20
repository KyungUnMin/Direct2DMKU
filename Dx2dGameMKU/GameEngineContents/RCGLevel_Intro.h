#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class RCGLevel_Intro : public GameEngineLevel
{
public:
	RCGLevel_Intro();
	~RCGLevel_Intro() override;

	RCGLevel_Intro(const RCGLevel_Intro& _Other) = delete;
	RCGLevel_Intro(RCGLevel_Intro&& _Other) noexcept = delete;
	RCGLevel_Intro& operator=(const RCGLevel_Intro& _Other) = delete;
	RCGLevel_Intro& operator=(const RCGLevel_Intro&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class GameEngineVideo> Video = nullptr;

	void CreateVideo();
};

