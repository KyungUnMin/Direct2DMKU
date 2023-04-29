#include "PrecompileHeader.h"
#include "FieldLevelBase.h"

#include <GameEngineCore/GameEngineCamera.h>

#include "RCGEnums.h"
#include "BackGround.h"
#include "FieldPlayer.h"
#include "Fader.h"

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
	GetMainCamera()->GetTransform()->SetWorldPosition(float4::Back * 1000.f);

	PlayerPtr = CreateActor<FieldPlayer>();
}

void FieldLevelBase::Update(float _DeltaTime)
{
	//사실 나중에 Enter, Exit가 들어오면 굳이 업데이트에서 해주지 않아도 된다
	GPtr = this;
	FieldPlayer::GPtr = PlayerPtr.get();
	
	CamCtrl.Update(_DeltaTime);
}



//이미지가 여러개 띄워질수 있다, 또한 애니메이션 이미지도 있다, -> 수정 필요
void FieldLevelBase::SettingBackImg(const std::string_view& _ResName,const float4& _MapScale)
{
	std::shared_ptr<BackGround> BGPtr = CreateActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	BGPtr->AddBackImg(_ResName, _MapScale);

	CamCtrl.Init(GetMainCamera(), _MapScale);
}



void FieldLevelBase::LevelChangeStart()
{
	CreateActor<Fader>()->Init(float4{ 0.f, 0.f, 0.f, 1.0f });
}