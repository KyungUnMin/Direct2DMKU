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

	//현재 구조에서는 UI에서 생각보다 이 순서가 중요할 것이다
	inline void SetOffsetFromCam(const float4& _Offset)
	{
		OffsetFromCam = _Offset;
	}

private:
	GameEngineTransform* CamTrans = nullptr;
	float4 PrevCamPos = float4::Zero;
	float4 OffsetFromCam = float4::Forward;
};

