#pragma once
#include "GameEngineActor.h"
#include "GameEngineEnum.h"

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

	//카메라 투영설정
	void SetProjectionType(CameraType _Type)
	{
		ProjectionType = _Type;
	}

	//프리카메라 모드인지
	inline bool IsFreeCamera()
	{
		return FreeCamera;
	}

	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

protected:
	void Start() override;

private:
	bool FreeCamera = false;

	//카메라의 뷰 행렬
	float4x4 View;

	float4x4 Projection;
	float4x4 ViewPort;

	//프리카메라 모드를 실행하기 전 상태
	TransformData OldData;

	//투영 모드
	CameraType ProjectionType = CameraType::None;

	//뷰포트 행렬을 표현하는 Dx구조체
	D3D11_VIEWPORT ViewPortData = D3D11_VIEWPORT();

	//카메라 너비 높이
	float Width = 0.0f;
	float Height = 0.0f;

	//화면 시야각
	float FOV = 60.0f;

	float Near = 0.1f;
	float Far = 10000.f;
};