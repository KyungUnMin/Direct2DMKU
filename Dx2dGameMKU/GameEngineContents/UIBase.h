#pragma once
#include <GameEngineCore/GameEngineActor.h>

class UIBase : public GameEngineActor
{
public:
	UIBase();
	virtual ~UIBase() = 0;

	UIBase(const UIBase& _Other) = delete;
	UIBase(UIBase&& _Other) noexcept = delete;
	UIBase& operator=(const UIBase& _Other) = delete;
	UIBase& operator=(const UIBase&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineTransform* CamTrans = nullptr;
	float4 PrevCamPos = float4::Zero;
};

