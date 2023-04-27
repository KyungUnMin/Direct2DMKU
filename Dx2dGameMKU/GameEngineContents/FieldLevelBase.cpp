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

	PlayerPtr = CreateActor<FieldPlayer>();
}

void FieldLevelBase::Update(float _DeltaTime)
{
	//��� ���߿� Enter, Exit�� ������ ���� ������Ʈ���� ������ �ʾƵ� �ȴ�
	GPtr = this;
	FieldPlayer::GPtr = PlayerPtr.get();
	
	CamCtrl.Update(_DeltaTime);
}

//�̹����� ������ ������� �ִ�, ���� �ִϸ��̼� �̹����� �ִ�, -> ���� �ʿ�
void FieldLevelBase::SettingBackImg(const std::string_view& _ResName,const float4& _MapScale)
{
	std::shared_ptr<BackGround> BGPtr = CreateActor<BackGround>(static_cast<int>(Field_UpdateOrder::BackGround));
	BGPtr->AddBackImg(_ResName, _MapScale);

	CamCtrl.Init(GetMainCamera(), _MapScale);
}
