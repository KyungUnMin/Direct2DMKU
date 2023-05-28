#pragma once

class GameEngineCamera;

enum class CameraCtrlState
{
	PlayerTrace,
	MoveToFixed,
	Fixed,
	Shake,
};

class FieldCamController
{
public:
	friend class FieldLevelBase;

	FieldCamController();
	~FieldCamController();

	FieldCamController(const FieldCamController& _Other) = delete;
	FieldCamController(FieldCamController&& _Other) noexcept = delete;
	FieldCamController& operator=(const FieldCamController& _Other) = delete;
	FieldCamController& operator=(const FieldCamController&& _Other) noexcept = delete;

	inline void SetTraceState()
	{
		CurState = CameraCtrlState::PlayerTrace;
	}

	void SetFixedState(const float4& _DestPos);
	
	void SetShakeState(float _ShakeDuration, float _ShakeRange = 5.f);

protected:


private:
	CameraCtrlState CurState = CameraCtrlState::PlayerTrace;
	std::shared_ptr<GameEngineCamera> Cam = nullptr;
	
	//Common
	float4 PrevPos = float4::Zero;
	float Timer = 0.f;

	//Trace
	float4 MapScale = float4::Zero;
	const float TraceYOffset = 80.f;

	//MoveToFixedSDA
	float4 DestPos = float4::Zero;

	//Shake
	float ShakeRange = 5.f;
	float ShakeDuration = 0.0f;
	CameraCtrlState PrevState = CameraCtrlState::Shake;



	void Init(std::shared_ptr<GameEngineCamera> _Cam,const float4& _MapScale);

	void Update(float _DeltaTime);

	//카메라 상태에 따른 Update들
	void Update_CamState(float _DeltaTime);
	void Update_Trace(float _DeltaTime);
	void Update_MoveToFixed(float _DeltaTime);
	void Update_Shake(float _DeltaTime);


	//--------ZOOM-----------------

public:
	static const float ZoomOrigin;

	//부드럽게 줌 변경
	void SetZoom(float _Per, float _Duration);

	//바로 줌 변경
	void SetZoom(float _Per = ZoomOrigin);

private:
	float ZoomTimer = 0.f;
	float ZoomMoveDuration = -1.f;
	float DestZoomPercent = 1.0f;
	float PrevZoomPercent = 1.0f;


	void Update_Zoom(float _DeltaTime);
};

