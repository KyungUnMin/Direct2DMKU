#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "LevelMgr.h"
#include "SimpleFSM.h"

class FieldDoor : public GameEngineActor
{
public:
	FieldDoor();
	~FieldDoor() override;

	FieldDoor(const FieldDoor& _Other) = delete;
	FieldDoor(FieldDoor&& _Other) noexcept = delete;
	FieldDoor& operator=(const FieldDoor& _Other) = delete;
	FieldDoor& operator=(const FieldDoor&& _Other) noexcept = delete;

	void Unlock(LevelNames _NextLevel);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:
	static const std::string_view LockDoorName;
	static const std::string_view UnlockDoorName;
	static const float4 LockDoorScale;
	static const float4 UnlockDoorScale;

	std::shared_ptr<class GameEngineRenderer> LockRender = nullptr;
	std::shared_ptr<class GameEngineRenderer> UnlockRender = nullptr;

	bool DoorLockValue = true;
	LevelNames NextLevel = LevelNames::OpeningLevel;
	bool IsNearPlayer = false;

	void ImgResLoad();
	void CreateDoorImg();
	void CheckNearPlayer();


	//--------FSM_UPDATE-----------

private:
	enum class State
	{
		Wait,
		Ready,

		COUNT
	};

	SimpleFSM ScaleFSM;
	SimpleFSM AlphaFSM;
	float4 AlphaRatio = float4::Zero;

	void CreateScaleState();
	void CreateAlphsState();

	void Update_ScaleWait(float _DeltaTime);
	void Update_ScaleReady(float _DeltaTime);

	void Update_AlphaWait(float _DeltaTime);
	void Update_AlphaReady(float _DeltaTime);


};

