#include "PrecompileHeader.h"
#include "FieldLevelBase.h"

#include <GameEngineCore/GameEngineCamera.h>

#include "RCGEnums.h"
#include "BackGround.h"
#include "FieldPlayer.h"

FieldLevelBase* FieldLevelBase::GPtr = nullptr;

FieldLevelBase::FieldLevelBase()
{

}

FieldLevelBase::~FieldLevelBase()
{

}


void FieldLevelBase::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);

	//나중에 EnterLevel 생기면 거기서 생성 삭제 하자
	CreateActor<FieldPlayer>();

}

void FieldLevelBase::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);

	if (true == GetMainCamera()->IsFreeCamera())
	{
		GPtr = nullptr;
		return;
	}

	GPtr = this;
	CamCtrl.Update(_DeltaTime);
}


void FieldLevelBase::SettingBackImg(const std::string_view& _ResName,const float4& _MapScale)
{
	std::shared_ptr<BackGround> BGPtr = CreateActor<BackGround>(static_cast<int>(Field_UpdateOrder::BackGround));
	BGPtr->SettingBackImg(_ResName, _MapScale);

	CamCtrl.Init(GetMainCamera(), _MapScale);
}
