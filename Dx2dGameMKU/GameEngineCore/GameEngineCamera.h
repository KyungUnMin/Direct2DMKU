#pragma once
#include "GameEngineActor.h"
#include "GameEngineEnum.h"

enum class SortType
{
	None,
	ZSort,
	YSort,
};

class GameEngineRenderer;
class GameEngineRenderTarget;

class GameEngineCamera : public GameEngineActor
{
	friend GameEngineLevel;
	friend GameEngineRenderer;

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

	//�� ī�޶� ��ϵ� ���������� ī�޶� ����Ÿ�ٿ� �׸���
	void Render(float _DeltaTime) override;

	//�� ī�޶� ���� ������� ����Ѵ�, �߰��� ����Ʈ ��ĵ� ���ȴ�
	void CameraTransformUpdate();


	//�� ī�޶��� ����Ÿ�� ����
	inline std::shared_ptr<GameEngineRenderTarget> GetCamTarget() const
	{
		return CamTarget;
	}

	bool IsView(const TransformData& _TransData);

	template<typename EnumType>
	void SetSortType(EnumType _Index, SortType _Sort)
	{
		SetSortType(static_cast<int>(_Index), _Sort);
	}

	inline void SetSortType(int _Index, SortType _Sort)
	{
		SortValues[_Index] = _Sort;
	}

	inline void AddZoomRatio(float _Value)
	{
		ZoomRatio -= _Value;
	}

	inline void SetZoomRatio(float _Value)
	{
		ZoomRatio = _Value;
	}

	inline float GetZoomRatio() const
	{
		return ZoomRatio;
	}

protected:
	void Start() override;

private:
	//�������� ī�޶� �����Ѵ�.
	//ī�޶� �ִ� ����Ÿ�Ͽ� �� ���������� �׸���.
	std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>> Renderers;

	//�ش� Render������ Sort�ǰ� �ִ��� ����
	std::map<int, SortType> SortValues;

	//��ü�� ī�޶󿵿� �ȿ� �����ϴ��� �Ǵ��ϱ� ���� �浹����
	DirectX::BoundingOrientedBox Box;

	bool FreeCamera = false;

	float ZoomRatio = 1.0f;

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


	//�� ī�޶��� ��ȭ���� �� ����Ÿ��
	std::shared_ptr<GameEngineRenderTarget> CamTarget;

	//�� ī�޶� �������� ����Ѵ�(���������� ȣ��)
	void PushRenderer(std::shared_ptr<GameEngineRenderer> _Render);

	//������ �� Death�� �������� ����
	void Release();
};