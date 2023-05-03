#include "PrecompileHeader.h"
#include "FieldLevelBase.h"

#include <GameEngineCore/GameEngineCamera.h>

#include "RCGEnums.h"
#include "BackGround.h"
#include "FieldPlayer.h"
#include "Fader.h"
#include "HUD.h"

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
	GetMainCamera()->GetTransform()->SetWorldPosition(float4::Back * 500.f);

	PlayerPtr = CreateActor<FieldPlayer>(static_cast<int>(UpdateOrder::Player));
	BGPtr = CreateActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	CreateActor<HUD>(static_cast<int>(UpdateOrder::UI));

	FreeCamDebugMoveCtrl.Init(GetMainCamera());
}


void FieldLevelBase::InitLevelArea(const float4& _Scale, const TileInfoData& _TileData)
{
	BGPtr->InitLevelArea(_Scale, _TileData);
	CamCtrl.Init(GetMainCamera(), _Scale);
}


void FieldLevelBase::SetPlayerStartPosition(const float4& _StartPos)
{
	PlayerPtr->GetTransform()->SetLocalPosition(_StartPos);
}


void FieldLevelBase::LevelChangeStart()
{
	GPtr = this;
	FieldPlayer::GPtr = PlayerPtr.get();

	CreateActor<Fader>(static_cast<int>(UpdateOrder::UI))->Init(float4{ 0.f, 0.f, 0.f, 1.0f });
}



void FieldLevelBase::Update(float _DeltaTime)
{
	CamCtrl.Update(_DeltaTime);
	FreeCamDebugMoveCtrl.Update(_DeltaTime);
}
