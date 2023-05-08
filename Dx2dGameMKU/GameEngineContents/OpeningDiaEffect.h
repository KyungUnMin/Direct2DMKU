#pragma once
#include <GameEngineCore/GameEngineActor.h>

class OpeningDiaEffect : public GameEngineActor
{
public:
	OpeningDiaEffect();
	~OpeningDiaEffect() override;

	OpeningDiaEffect(const OpeningDiaEffect& _Other) = delete;
	OpeningDiaEffect(OpeningDiaEffect&& _Other) noexcept = delete;
	OpeningDiaEffect& operator=(const OpeningDiaEffect& _Other) = delete;
	OpeningDiaEffect& operator=(const OpeningDiaEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

