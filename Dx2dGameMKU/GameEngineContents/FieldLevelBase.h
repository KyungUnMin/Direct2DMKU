#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "FieldCamController.h"
#include "FreeCamMoveController.h"
#include "ResourceHelper.h"
#include "EnemySpawner.h"

class FieldPlayer;
class BackGround;

class FieldLevelBase : public GameEngineLevel
{
public:
	static std::shared_ptr<FieldLevelBase> GetPtr()
	{
		if (nullptr == GPtr)
		{
			MsgAssert("필드 레벨이 존재하지 않습니다");
			return nullptr;
		}

		return GPtr->DynamicThis<FieldLevelBase>();
	}

	FieldLevelBase();
	virtual ~FieldLevelBase()  = 0;

	FieldLevelBase(const FieldLevelBase& _Other) = delete;
	FieldLevelBase(FieldLevelBase&& _Other) noexcept = delete;
	FieldLevelBase& operator=(const FieldLevelBase& _Other) = delete;
	FieldLevelBase& operator=(const FieldLevelBase&& _Other) noexcept = delete;

	FieldCamController& GetCameraController()
	{
		return CamCtrl;
	}

	//bool IsBlockPos(const float4& _Pos);
	inline std::shared_ptr<BackGround> GetBackGround() const
	{
		return BGPtr;
	}

	inline EnemySpawner& GetEnemySpawner()
	{
		return EnemySpawnerCtrl;
	}
	

protected:
	const float BgmFadeDuration = 3.f;

	void Start() override;
	void Update(float _DeltaTime) override;
	
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	void Init(const float4& _Scale, const class TileInfoData& _TileData);

	void SetPlayerStartPosition(const float4& _StartPos);


	//첫번째 인자 : <텍스처 이름, 오프셋>, 두번째 인자 : GameEngineActorGUI가 컨트롤 할 배경의 인덱스
	void CreateBackGrounds(const std::vector<std::pair<std::string_view, float4>> _BackGroundInfoes, size_t _GuiSelect = UINT64_MAX);

	void CreateCollisionImage(const std::string_view& _ImageName);


	inline void SetDoorOpenFunc(std::function<void()> _DoorOpenFunc)
	{
		DoorOpenFunc = _DoorOpenFunc;
	}

	void CreateNpcs(const std::vector<class NpcCreateInfo>& _NpcInfoes);

	void OnTransView_ForDebug();

private:
	static FieldLevelBase* GPtr;

	std::shared_ptr<BackGround> BGPtr = nullptr;
	std::shared_ptr<FieldPlayer> PlayerPtr = nullptr;
	FieldCamController CamCtrl;
	FreeCamMoveController FreeCamDebugMoveCtrl;
	EnemySpawner EnemySpawnerCtrl = EnemySpawner(this);


	std::function<void()> DoorOpenFunc = nullptr;

	void Update_DoorOpen_ForDebug();
	void Update_CreateMoeny_ForDebug();

	void MoneyClear();
};

class NpcCreateInfo
{
public:
	std::string_view NpcFileName = "";
	float4 CreatePos = float4::Zero;
	bool RenderFlip = false;
	bool LookPlayerAtReact = true;
};