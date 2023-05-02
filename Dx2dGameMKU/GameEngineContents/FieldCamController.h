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
	
	void SetShakeState(float _ShakeDuration);

protected:


private:
	CameraCtrlState CurState = CameraCtrlState::PlayerTrace;
	std::shared_ptr<GameEngineCamera> Cam = nullptr;
	
	bool PrevCamMode = false;
	bool IsFreeCamMode = false;

	//Common
	float4 PrevPos = float4::Zero;
	float Timer = 0.f;

	//Trace
	float4 MapScale = float4::Zero;
	const float TraceYOffset = 80.f;

	//MoveToFixedSDA
	float4 DestPos = float4::Zero;

	//Shake
	float ShakeDuration = 0.0f;
	CameraCtrlState PrevState = CameraCtrlState::Shake;

	//FreeCamera(��������)
	float PlayerGravity = 0.f;
	float4 PlayerOriginOffset = float4::Zero;
	std::shared_ptr<class GameEngineSpriteRenderer> PlayerRender = nullptr;

	void Init(std::shared_ptr<GameEngineCamera> _Cam,const float4& _MapScale);

	void Update(float _DeltaTime);

	void Update_Trace(float _DeltaTime);
	void Update_MoveToFixed(float _DeltaTime);
	void Update_Shake(float _DeltaTime);

	void Update_FreeCam(float _DeltaTime);
};

