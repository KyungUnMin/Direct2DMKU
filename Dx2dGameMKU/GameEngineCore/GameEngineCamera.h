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

	//����Ʈ ����� GPU�� �������ش�(���� �����Ͷ����� ������ ���� �������ش�)
	void Setting();

	//ī�޶� ��������
	void SetProjectionType(CameraType _Type)
	{
		ProjectionType = _Type;
	}

	//����ī�޶� �������
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

	//ī�޶��� �� ���
	float4x4 View;

	float4x4 Projection;
	float4x4 ViewPort;

	//����ī�޶� ��带 �����ϱ� �� ����
	TransformData OldData;

	//���� ���
	CameraType ProjectionType = CameraType::None;

	//����Ʈ ����� ǥ���ϴ� Dx����ü
	D3D11_VIEWPORT ViewPortData = D3D11_VIEWPORT();

	//ī�޶� �ʺ� ����
	float Width = 0.0f;
	float Height = 0.0f;

	//ȭ�� �þ߰�
	float FOV = 60.0f;

	float Near = 0.1f;
	float Far = 10000.f;
};