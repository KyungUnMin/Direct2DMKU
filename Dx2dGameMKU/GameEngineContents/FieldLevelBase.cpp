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

	//ī�޶� ĳ���͸� ���� �ٴϰ� ���� ������ ������ ���Ѵ�.

	/*std::weak_ptr<FieldPlayer> Player = FieldPlayer::GetPtr();
	if (false == Player.expired())
	{
		std::shared_ptr<FieldPlayer> SPtr = Player.lock();
		int a = 10;
	}*/

}


void FieldLevelBase::SettingBackImg(const std::string_view& _ResName,const float4& _MapScale)
{
	MapScale = _MapScale;

	std::shared_ptr<BackGround> BGPtr = CreateActor<BackGround>(static_cast<int>(Field_UpdateOrder::BackGround));
	BGPtr->SettingBackImg(_ResName, _MapScale);
}
