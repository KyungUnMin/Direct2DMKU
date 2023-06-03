#pragma once
#include <GameEngineCore/GameEngineActor.h>

class DapEffect : public GameEngineActor
{
public:
	DapEffect();
	~DapEffect() override;

	DapEffect(const DapEffect& _Other) = delete;
	DapEffect(DapEffect&& _Other) noexcept = delete;
	DapEffect& operator=(const DapEffect& _Other) = delete;
	DapEffect& operator=(const DapEffect&& _Other) noexcept = delete;

	void Init();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view EffectImgName;
	static float4 EffectScale;

	static const float MoveOffset;
	static float4 StartOffset;
	static float4 DestOffset;

	std::shared_ptr<class GameEngineRenderer> RenderPtr = nullptr;
	float4 ShaderLinkColor = float4::One;

	float Timer = 0.f;
	const float Duration = 0.2f;
	


	void LoadEffectImage();
	void CreateRender();
	void SettingColor();
	float GetStepRand(float _StepValue = 0.3f);
};
