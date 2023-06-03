#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineTransform.h>

class BossVersus_PostProcessing : public GameEnginePostProcess
{
public:
	BossVersus_PostProcessing();
	~BossVersus_PostProcessing();

	BossVersus_PostProcessing(const BossVersus_PostProcessing& _Other) = delete;
	BossVersus_PostProcessing(BossVersus_PostProcessing&& _Other) noexcept = delete;
	BossVersus_PostProcessing& operator=(const BossVersus_PostProcessing& _Other) = delete;
	BossVersus_PostProcessing& operator=(const BossVersus_PostProcessing&& _Other) noexcept = delete;

	inline void On(float _Duration = 1.f, std::function<void()> _CallBack = nullptr)
	{
		Flag = true;
		Duration = _Duration;
		CallBack = _CallBack;
	}


protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;

private:
	struct ShaderData
	{
		const float4 FireColor = float4{ 1.f, 0.f, 0.f, 1.f };

		float NoiseFilterValue = 1.0f;
		const float NoiseImageScale = 5.f; /*±âÁ¸°ª 5.0f*/
		const float OffsetRatio = 0.01f;
		const float Garbage2 = 0.f;
	};

	ShaderData CBufferData;
	bool Flag = false;
	float Timer = 0.f;
	float Duration = 1.f;
	
	std::shared_ptr<GameEngineRenderUnit> RenderUnit;
	std::function<void()> CallBack = nullptr;
	GameEngineTransform GarbageTrans;

	bool Update_CalData(float _DeltaTime);
};

