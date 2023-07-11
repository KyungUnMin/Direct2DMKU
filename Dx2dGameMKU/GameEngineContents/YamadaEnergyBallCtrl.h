#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <GameEnginePlatform/GameEngineSound.h>

class YamadaEnergyBall;

class YamadaEnergyBallCtrl : public GameEngineActor
{
public:
	YamadaEnergyBallCtrl();
	~YamadaEnergyBallCtrl() override;

	YamadaEnergyBallCtrl(const YamadaEnergyBallCtrl& _Other) = delete;
	YamadaEnergyBallCtrl(YamadaEnergyBallCtrl&& _Other) noexcept = delete;
	YamadaEnergyBallCtrl& operator=(const YamadaEnergyBallCtrl& _Other) = delete;
	YamadaEnergyBallCtrl& operator=(const YamadaEnergyBallCtrl&& _Other) noexcept = delete;

	inline void Init(float _Duration)
	{
		Duration = _Duration;
	}

	void Clear();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	//<포인터, 삼각함수의 각도>
	std::vector<std::pair<std::shared_ptr<YamadaEnergyBall>, float>> Balls;

	float Duration = -1.f;

	const float OriginXRadius = 200.f;
	const float OriginYRadius = 100.f;

	const float RadiusOffsetX = 600.f;
	const float RadiusOffsetY = 300.f;

	float XRadius = 200.f;
	float YRadius = 100.f;
	float RadiusTimer = 0.f;

	GameEngineSoundPlayer EnergyBallSfx;

	void Update_Rotation(float _DeltaTime);
	void Update_RadiusRange(float _DeltaTime);
};

