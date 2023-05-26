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

	//이 카메라에 등록된 렌더러들을 카메라 렌더타겟에 그린다
	void Render(float _DeltaTime) override;

	//이 카메라에 대한 뷰행렬을 계산한다, 추가로 뷰포트 행렬도 계산된다
	void CameraTransformUpdate();


	//이 카메라의 렌더타켓 리턴
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
	//렌더러는 카메라가 관리한다.
	//카메라에 있는 렌더타켓에 이 렌더러들을 그린다.
	std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>> Renderers;

	//해당 Render오더가 Sort되고 있는지 여부
	std::map<int, SortType> SortValues;

	//물체가 카메라영역 안에 존재하는지 판단하기 위한 충돌정보
	DirectX::BoundingOrientedBox Box;

	bool FreeCamera = false;

	float ZoomRatio = 1.0f;

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


	//이 카메라의 도화지가 될 렌더타겟
	std::shared_ptr<GameEngineRenderTarget> CamTarget;

	//이 카메라에 렌더러를 등록한다(렌더러에서 호출)
	void PushRenderer(std::shared_ptr<GameEngineRenderer> _Render);

	//렌더러 중 Death된 렌더러는 제거
	void Release();
};