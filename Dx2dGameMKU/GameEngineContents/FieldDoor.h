#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "LevelMgr.h"
#include "SimpleFSM.h"

enum class DoorType
{
	Normal,
	Gym,
	Shop
};


class FieldDoor : public GameEngineActor
{
public:
	static LevelNames GetRegistNextLevel()
	{
		return RegistNextLevel;
	}

	FieldDoor();
	~FieldDoor() override;

	FieldDoor(const FieldDoor& _Other) = delete;
	FieldDoor(FieldDoor&& _Other) noexcept = delete;
	FieldDoor& operator=(const FieldDoor& _Other) = delete;
	FieldDoor& operator=(const FieldDoor&& _Other) noexcept = delete;

	void Init(DoorType _Type, const float4& _RenderOffset = float4::Zero);
	void Unlock(LevelNames _NextLevel);

	inline bool IsOpened() const
	{
		return (LevelNames::OpeningLevel != NextLevel);
	}

	inline bool IsNearWithPlayer() const
	{
		return IsNearPlayer;
	}

protected:
	void Update(float _DeltaTime) override;


private:
	static const std::string_view LockDoorName;
	static const float4 LockDoorScale;

	static const std::string_view UnlockDoorName;
	static const float4 UnlockDoorScale;

	static const std::string_view ShopIconName;
	static const float4 ShopIconScale;

	static const std::string_view GymIconName;
	static const float4 GymIconScale;

	static LevelNames RegistNextLevel;

	std::shared_ptr<class GameEngineRenderer> LockRender = nullptr;
	std::shared_ptr<class GameEngineRenderer> UnlockRender = nullptr;

	DoorType ImageType = DoorType::Normal;
	bool DoorLockValue = true;
	LevelNames NextLevel = LevelNames::OpeningLevel;
	bool IsNearPlayer = false;
	const float FadeTime = 0.5f;

	void ImgResLoad();
	void CreateDoorImage(
		const std::string_view& _ImageName, 
		const float4& _Scale
		,bool _IsLockImage
		,const float4& _RenderOffset);

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

	struct ShaderData
	{
		const float OriginAlpha = 0.5f;
		float Ratio = 0.f;
		float Garbage1 = 0.f;
		float Garbage2 = 0.f;
	};

	ShaderData AlphaRatio;

	void CreateScaleState();
	void CreateAlphsState();

	void Update_ScaleWait(float _DeltaTime);
	void Update_ScaleReady(float _DeltaTime);

	void Update_AlphaWait(float _DeltaTime);
	void Update_AlphaReady(float _DeltaTime);


};

