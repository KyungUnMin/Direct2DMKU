#pragma once
#include "UIBase.h"

class Fader : public UIBase
{
public:
	Fader();
	~Fader() override;

	Fader(const Fader& _Other) = delete;
	Fader(Fader&& _Other) noexcept = delete;
	Fader& operator=(const Fader& _Other) = delete;
	Fader& operator=(const Fader&& _Other) noexcept = delete;

	inline void Init(
		const float4& _StartColor = float4{0.f, 0.f, 0.f, 0.f},
		float _Duration = 0.5f,
		std::function<void()> _FinishCallback = nullptr)
	{
		FadeColor = _StartColor;
		Duration = _Duration;
		Callback = _FinishCallback;

		IsFadeIn = (FadeColor.w < 0.5f) ? true : false;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static Fader* IsFading;

	float4 FadeColor = float4::One;
	bool IsFadeIn = false;
	float Duration = 0.f;
	std::function<void()> Callback;

	std::shared_ptr<class GameEngineUIRenderer> RenderPtr = nullptr;
};

