#include "PrecompileHeader.h"
#include "PlayerStateBase.h"

#include "FieldPlayer.h"



PlayerStateBase::PlayerStateBase()
{

}

PlayerStateBase::~PlayerStateBase()
{
	
}




void PlayerStateBase::Start()
{
	StateBase::Start();

	Renderer = FieldPlayer::GetPtr()->GetRenderer();
}





void PlayerStateBase::Update(float _DeltaTime)
{
	StateBase::Update(_DeltaTime);

	SettingHeightRender();
	SettingDirectionRender();
}


void PlayerStateBase::SettingHeightRender()
{
	float NowHeight = FieldPlayer::GetPtr()->GetHeight();
	Renderer->GetTransform()->SetLocalPosition(float4::Up * NowHeight);
}



void PlayerStateBase::SettingDirectionRender()
{
	if (false == DirChangeSwitch)
		return;

	std::shared_ptr<FieldPlayer> PlayerPtr = FieldPlayer::GetPtr();
	GameEngineTransform* PlayerTrans = PlayerPtr->GetTransform();

	if (true == FieldPlayer::GetPtr()->IsRightDir())
	{
		PlayerTrans->SetLocalPositiveScaleX();
	}
	else
	{
		PlayerTrans->SetLocalNegativeScaleX();
	}
}
