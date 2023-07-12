#pragma once
#include "EnemyStateBase.h"

class NoiseState_Sing : public EnemyStateBase
{
public:
	NoiseState_Sing();
	~NoiseState_Sing() override;

	NoiseState_Sing(const NoiseState_Sing& _Other) = delete;
	NoiseState_Sing(NoiseState_Sing&& _Other) noexcept = delete;
	NoiseState_Sing& operator=(const NoiseState_Sing& _Other) = delete;
	NoiseState_Sing& operator=(const NoiseState_Sing&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

private:
	static const std::string_view GuitarPlay_FileName;
	static const std::string_view GuitarSing_FileName;
	static const std::string_view FloorLine_FileName;


	static const float AniInterTime;
	static const std::vector<float> Durations;
	static const std::vector<size_t> SpawnTimeCount;

	static const std::vector<std::string_view> BgmSongNames;

	std::shared_ptr<class GameEngineSpriteRenderer> FloorLines = nullptr;
	std::vector<std::shared_ptr<class LightEffect>> Lights;

	float4 PlayerOriginColScale = float4::Zero;
	size_t CurPhase = -1;

	void LoadAnimation();
	void CreateAnimation();
	void CreateFloorLine();
	void CreateLights();
	void ChangePlayerColTrans();
	

	void Update_Rail();
	void Update_Floor();
	void CreateFloor();
};

