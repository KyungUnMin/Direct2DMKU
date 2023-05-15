#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "FieldCamController.h"
#include "FreeCamMoveController.h"
#include "ResourceHelper.h"

class FieldPlayer;
class BackGround;

class FieldLevelBase : public GameEngineLevel
{
public:
	static std::shared_ptr<FieldLevelBase> GetPtr()
	{
		if (nullptr == GPtr)
		{
			MsgAssert("�ʵ� ������ �������� �ʽ��ϴ�");
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
	

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
	void LevelChangeStart() override;

	void Init(const float4& _Scale, const class TileInfoData& _TileData);

	void SetPlayerStartPosition(const float4& _StartPos);


	//ù��° ���� : <�ؽ�ó �̸�, ������>, �ι�° ���� : GameEngineActorGUI�� ��Ʈ�� �� ����� �ε���
	void CreateBackGrounds(const std::vector<std::pair<std::string_view, float4>> _BackGroundInfoes, size_t _GuiSelect = UINT64_MAX);

	void CreateCollisionImage(const std::string_view& _ImageName);

private:
	static FieldLevelBase* GPtr;

	std::shared_ptr<BackGround> BGPtr = nullptr;
	std::shared_ptr<FieldPlayer> PlayerPtr = nullptr;
	FieldCamController CamCtrl;
	FreeCamMoveController FreeCamDebugMoveCtrl;

	//GameEngineTransform PlayerDebugTransform;
};

