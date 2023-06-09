#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GatherEnergyEffect : public GameEngineActor
{
public:
	GatherEnergyEffect();
	~GatherEnergyEffect();

	GatherEnergyEffect(const GatherEnergyEffect& _Other) = delete;
	GatherEnergyEffect(GatherEnergyEffect&& _Other) noexcept = delete;
	GatherEnergyEffect& operator=(const GatherEnergyEffect& _Other) = delete;
	GatherEnergyEffect& operator=(const GatherEnergyEffect&& _Other) noexcept = delete;

	void Excute(float4 _LightColor, float _Duration = 0.5f);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view Light_FileName;
	static const float4 LightScale;

	static const size_t ParticleCount;
	static const float4 ParticleScale;

	struct ParticleData
	{
		std::shared_ptr<class GameEngineRenderer> Render = nullptr;
		float4 Color = float4::White;
		float4 Dir = float4::Zero;
		float Duration = 0.f;
	};

	std::shared_ptr<class GameEngineSpriteRenderer> Light = nullptr;

	//풀에서 대기중인 파티클(스택)
	std::vector<ParticleData> ReadyParticles;
	//동작중인 파티클(큐)
	std::list<ParticleData> ActionParticles;

	float Timer = 0.f;
	float Duration = 0.f;
	float ParticleCreateTime = 0.f;

	void ImageLoad();
	void CreateRenders();

	void Update_Light();
	void InstanceParticle();
};

