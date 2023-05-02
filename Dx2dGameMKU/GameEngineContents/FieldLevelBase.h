#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "FieldCamController.h"
#include "FreeCamMoveController.h"

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

		return GPtr->Shared_This_dynamic_pointer<FieldLevelBase>();
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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
	void LevelChangeStart() override;

	void InitLevelArea(const float4& _Scale, const class TileInfoData& _TileData);

	inline std::shared_ptr<class BackGround> GetBG() const
	{
		return BGPtr;
	}

private:
	static FieldLevelBase* GPtr;

	std::shared_ptr<class BackGround> BGPtr = nullptr;
	std::shared_ptr<class FieldPlayer> PlayerPtr = nullptr;
	FieldCamController CamCtrl;
	FreeCamMoveController FreeCamDebugMoveCtrl;

	//GameEngineTransform PlayerDebugTransform;
};

