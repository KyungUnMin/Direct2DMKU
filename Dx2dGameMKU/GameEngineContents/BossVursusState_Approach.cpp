#include "PrecompileHeader.h"
#include "BossVursusState_Approach.h"

#include <GameEngineCore/GameEngineRenderer.h>

#include "RCGEnums.h"

#include "BossVursus.h"


BossVursusState_Approach::BossVursusState_Approach()
{

}

BossVursusState_Approach::~BossVursusState_Approach()
{

}



void BossVursusState_Approach::Init(BossVursus* _VursusUI)
{
	std::shared_ptr<GameEngineRenderer> PlayerPortrait =  _VursusUI->GetPlayerPortrait();
	std::shared_ptr<GameEngineRenderer> BossPortrait = _VursusUI->GetBossPortrait();
	PlayerPortrait->GetShaderResHelper().SetConstantBufferLink(BossVursus::PortraitCBufferName, PortraitRenderData);
	BossPortrait->GetShaderResHelper().SetConstantBufferLink(BossVursus::PortraitCBufferName, PortraitRenderData);

	PlayerPortTrans = PlayerPortrait->GetTransform();
	BossPortTrans = BossPortrait->GetTransform();


}


void BossVursusState_Approach::Update(float _DeltaTime)
{
	StateBase::Update(_DeltaTime);


}
