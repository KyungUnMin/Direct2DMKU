#pragma once
#include <GameEngineCore/GameEngineActor.h>

class ShaderTestActor : public GameEngineActor
{
public:
	ShaderTestActor();
	~ShaderTestActor() override;

	ShaderTestActor(const ShaderTestActor& _Other) = delete;
	ShaderTestActor(ShaderTestActor&& _Other) noexcept = delete;
	ShaderTestActor& operator=(const ShaderTestActor& _Other) = delete;
	ShaderTestActor& operator=(const ShaderTestActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	struct WaveData
	{
		float4 Color = float4::Zero;
		float Time = 0.0f;
		float Duration = 0.5f;
	};

	std::vector<std::pair<std::shared_ptr<class GameEngineRenderer>, WaveData>> Waves;
	int OffIndex = -1;
};

