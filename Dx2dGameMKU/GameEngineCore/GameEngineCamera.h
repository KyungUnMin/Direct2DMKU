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

	//����Ʈ ����� GPU�� �������ش�(���� �����Ͷ����� ������ ���� �������ش�)
	void Setting();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool FreeCamera = false;

	//ī�޶��� �� ���
	float4x4 View;

	float4x4 Projection;
	float4x4 ViewPort;

	//����Ʈ ����� ǥ���ϴ� Dx����ü
	D3D11_VIEWPORT ViewPortData = D3D11_VIEWPORT();

	float Near = 0.1f;
	float Far = 10000.f;
};