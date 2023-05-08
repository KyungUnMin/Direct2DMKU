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
	struct LinkDataStruct
	{
		float4 LinkData1 = float4{ 1.f, 0.f, 0.f, 1.f };
		float4 LinkData2 = float4{1.f, 0.f, 0.f, 0.f};
	};

	LinkDataStruct LinkData;
};

