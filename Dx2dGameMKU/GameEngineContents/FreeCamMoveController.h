#pragma once

class GameEngineCamera;

class FreeCamMoveController
{
public:
	FreeCamMoveController();
	~FreeCamMoveController();

	FreeCamMoveController(const FreeCamMoveController& _Other) = delete;
	FreeCamMoveController(FreeCamMoveController&& _Other) noexcept = delete;
	FreeCamMoveController& operator=(const FreeCamMoveController& _Other) = delete;
	FreeCamMoveController& operator=(const FreeCamMoveController&& _Other) noexcept = delete;

	void Init(std::shared_ptr<GameEngineCamera> _Cam);
	void Update(float _DeltaTime);

protected:


private:
	std::shared_ptr<GameEngineCamera> CamPtr = nullptr;
	class GameEngineTransform* PlayerRenderTrans = nullptr;
	bool IsPrevFreeCam = false;
	float4 PlayerOriginPos = float4::Zero;


	void Update_FreeCam(float _DeltaTime);
};

