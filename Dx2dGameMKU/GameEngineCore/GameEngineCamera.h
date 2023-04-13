#pragma once
#include "GameEngineActor.h"

class GameEngineCamera : public GameEngineActor
{
public:
	GameEngineCamera();
	~GameEngineCamera() override;

	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(const GameEngineCamera&& _Other) noexcept = delete;

	inline float4x4 GetView()
	{
		return View;
	}

	inline float4x4 GetProjection()
	{
		return Projection;
	}

	inline float4x4 GetViewPort()
	{
		return ViewPort;
	}

	//뷰포트 행렬을 GPU에 설정해준다(랜파 레스터라이저 과정을 위해 설정해준다)
	void Setting();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool FreeCamera = false;

	//카메라의 뷰 행렬
	float4x4 View;

	float4x4 Projection;
	float4x4 ViewPort;

	//뷰포트 행렬을 표현하는 Dx구조체
	D3D11_VIEWPORT ViewPortData = D3D11_VIEWPORT();

	float Near = 0.1f;
	float Far = 10000.f;
};