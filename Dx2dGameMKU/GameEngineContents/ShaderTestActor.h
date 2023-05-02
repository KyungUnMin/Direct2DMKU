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
	float4 LinkData = float4::Zero;
	float Timer = 0.f;
};

