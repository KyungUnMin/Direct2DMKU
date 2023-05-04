#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "FieldCamController.h"
#include "FreeCamMoveController.h"
#include "ResourceHelper.h"

class FieldPlayer;

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

	bool IsBlockPos(const float4& _Pos);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
	void LevelChangeStart() override;

	void InitLevelArea(const float4& _Scale, const class TileInfoData& _TileData);

	void SetPlayerStartPosition(const float4& _StartPos);


	//첫번째 인자 : <텍스처 이름, 오프셋>, 두번째 인자 : GameEngineActorGUI가 컨트롤 할 배경의 인덱스
	void CreateBackGrounds(const std::vector<std::pair<std::string_view, float4>> _BackGroundInfoes, size_t _GuiSelect = UINT64_MAX);

	void CreateCollisionImage(const std::string_view& _ImageName);

private:
	static FieldLevelBase* GPtr;

	std::shared_ptr<class BackGround> BGPtr = nullptr;
	std::shared_ptr<FieldPlayer> PlayerPtr = nullptr;
	FieldCamController CamCtrl;
	FreeCamMoveController FreeCamDebugMoveCtrl;

	//GameEngineTransform PlayerDebugTransform;
};

