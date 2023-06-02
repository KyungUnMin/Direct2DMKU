#include "PrecompileHeader.h"
#include "BossVersusState_Corner.h"


#include "BossVersus.h"
#include "SelfRenderer.h"


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



std::shared_ptr<SelfRenderer> BossVersusState_Corner::CreateCornerRenders()
{
	BossVersus* VersusUI = BossVersus::GetPtr();

	std::shared_ptr<SelfRenderer> CornerBlack = nullptr;
	std::shared_ptr<SelfRenderer> CornerPink = nullptr;

	CornerBlack  = VersusUI->CreataEngineUIRender(CornerBlack_FileName, BossVersusUIRenderOrder::Corner_Black);
	GameEngineTransform* BlackTrans = CornerBlack->GetTransform();
	
	CornerPink = VersusUI->CreataEngineUIRender(CornerPink_FileName, BossVersusUIRenderOrder::Corner_Pink);
	GameEngineTransform* PinkTrans = CornerPink->GetTransform();
	
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
		GetFSM()->ChangeState(BossVersusStateType::Spark);
		return;
	}

	float4 NowOffsetScale = ScaleOffset * sinf(LiveTime * 10.f);

	float4 LeftOffest = OriginScale + NowOffsetScale;
	LeftCorner->GetTransform()->SetLocalScale(LeftOffest);

	float4 RightOffset = float4{ -OriginScale.x, OriginScale.y } + float4{ -NowOffsetScale.x, NowOffsetScale.y };
	RightCorner->GetTransform()->SetLocalScale(RightOffset);
}
