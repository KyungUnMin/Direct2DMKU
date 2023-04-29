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
	BGPtr = CreateActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
}


void FieldLevelBase::InitLevelArea(const float4& _Scale, const TileInfoData& _TileData)
{
	BGPtr->InitLevelArea(_Scale, _TileData);
	CamCtrl.Init(GetMainCamera(), _Scale);
}


void FieldLevelBase::LevelChangeStart()
{
	GPtr = this;
	FieldPlayer::GPtr = PlayerPtr.get();

	CreateActor<Fader>()->Init(float4{ 0.f, 0.f, 0.f, 1.0f });
}



void FieldLevelBase::Update(float _DeltaTime)
{
	CamCtrl.Update(_DeltaTime);
}





