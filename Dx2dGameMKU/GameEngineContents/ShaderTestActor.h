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
	struct GlichData
	{
		float Timer = 0.f;
		float Speed = 10.f;
		float Count = 30.f;
		float WaveDiff = 0.3f;
	};

	GlichData Data;
};

