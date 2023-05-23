#include "PrecompileHeader.h"
#include "BossVersusState_Corner.h"

#include <GameEngineCore/GameEngineUIRenderer.h>

#include "BossVersus.h"


const std::string_view BossVersusState_Corner::CornerBlack_FileName	= "VersusPortrait_CornerBlack.png";
const std::string_view BossVersusState_Corner::CornerPink_FileName		= "VersusPortrait_CornerPink.png";

BossVersusState_Corner::BossVersusState_Corner()
{

}

BossVersusState_Corner::~BossVersusState_Corner()
{

}

void BossVersusState_Corner::Start()
{
	StateBase::Start();

	LeftCorner = CreateCornerRenders();
	OriginScale = LeftCorner->GetTransform()->GetLocalScale();
	RightCorner = CreateCornerRenders();
	RightCorner->GetTransform()->SetLocalNegativeScaleX();

	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	DestPos = ScreenSize.half();
}



std::shared_ptr<GameEngineSpriteRenderer>  BossVersusState_Corner::CreateCornerRenders()
{
	BossVersus* VersusUI = BossVersus::GetPtr();

	std::shared_ptr<GameEngineUIRenderer> CornerBlack = nullptr;
	std::shared_ptr<GameEngineUIRenderer> CornerPink = nullptr;

	CornerBlack = VersusUI->CreateComponent<GameEngineUIRenderer>();
	CornerBlack->SetScaleToTexture(CornerBlack_FileName);
	GameEngineTransform* BlackTrans = CornerBlack->GetTransform();
	
	CornerPink = VersusUI->CreateComponent<GameEngineUIRenderer>();
	CornerPink->SetTexture(CornerPink_FileName);
	GameEngineTransform* PinkTrans = CornerPink->GetTransform();
	

	//테스트 코드
	{
		BlackTrans->SetLocalScale(BlackTrans->GetLocalScale() * 0.8f);
	}
	
	PinkTrans->SetParent(BlackTrans);
	PinkTrans->SetLocalScale(float4::One * 0.9f);

	BlackTrans->SetLocalPosition(float4::Forward * 100.f);
	CornerBlack->Off();
	return CornerBlack;
}



void BossVersusState_Corner::EnterState()
{
	StateBase::EnterState();

	LeftCorner->On();
	RightCorner->On();
}


void BossVersusState_Corner::Update(float _DeltaTime)
{
	StateBase::Update(_DeltaTime);

	switch (CurState)
	{
	case BossVersusState_Corner::State::Position:
		Update_CornerPosition();
		break;
	case BossVersusState_Corner::State::Scale:
		Update_CornerScale();
		break;
	}
}


void BossVersusState_Corner::Update_CornerPosition()
{
	float Ratio = GetLiveTime() / PositionDuration;
	float4 NowOffset = float4::LerpClamp(DestPos + StartOffset, DestPos, Ratio);

	LeftCorner->GetTransform()->SetLocalPosition(-NowOffset);
	RightCorner->GetTransform()->SetLocalPosition(float4{ NowOffset.x, -NowOffset.y });

	if (Ratio < 1.f)
		return;

	CurState = State::Scale;
	StateBase::ResetLiveTime();
}

void BossVersusState_Corner::Update_CornerScale() 
{
	float LiveTime = GetLiveTime();
	if (ScaleDuration < LiveTime)
	{
		GetFSM()->ChangeState(BossVersusStateType::Fire);
		return;
	}

	float4 NowOffsetScale = ScaleOffset * sinf(LiveTime * 10.f);

	float4 LeftOffest = OriginScale + NowOffsetScale;
	LeftCorner->GetTransform()->SetLocalScale(LeftOffest);

	float4 RightOffset = float4{ -OriginScale.x, OriginScale.y } + float4{ -NowOffsetScale.x, NowOffsetScale.y };
	RightCorner->GetTransform()->SetLocalScale(RightOffset);
}
