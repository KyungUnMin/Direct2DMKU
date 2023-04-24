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
	std::shared_ptr<class GameEngineRenderer> RenderPtr = nullptr;
	float4 Timer = float4::Zero;
};

