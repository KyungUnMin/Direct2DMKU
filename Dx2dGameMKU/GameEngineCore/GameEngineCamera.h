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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool FreeCamera = false;

	//카메라의 뷰 행렬
	float4x4 View;
	float4x4 Projection;
};

