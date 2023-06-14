#include "PrecompileHeader.h"
#include "YamadaEnergyBallCtrl.h"

#include <GameEngineCore/GameEngineLevel.h>

#include "RCGEnums.h"

#include "YamadaEnergyBall.h"

YamadaEnergyBallCtrl::YamadaEnergyBallCtrl()
{

}

YamadaEnergyBallCtrl::~YamadaEnergyBallCtrl()
{

}


void YamadaEnergyBallCtrl::Start()
{
	GameEngineActor::Start();

	Balls.resize(4);
	for (size_t i = 0; i < Balls.size(); ++i)
	{
		Balls[i].first = GetLevel()->CreateActor<YamadaEnergyBall>(UpdateOrder::Effect);
		GameEngineTransform* BallTrans = Balls[i].first->GetTransform();
		BallTrans->SetParent(GetTransform());

		float StartRot = GameEngineMath::PIE * 0.5f * static_cast<float>(i);
		Balls[i].second = StartRot;

		float4 Pos = float4::Zero;
		Pos.x = cosf(StartRot) * XRadius;
		Pos.y = sinf(StartRot) * YRadius;
		Pos.z = Pos.y;

		BallTrans->SetLocalPosition(Pos);
	}
}


void YamadaEnergyBallCtrl::Update(float _DeltaTime)
{
	GameEngineActor::Update(_DeltaTime);

	if (Duration < 0.f)
	{
		MsgAssert("Init함수를 호출해주지 않았습니다");
		return;
	}

	if (true == Balls.back().first->IsWait())
		return;

	if (GetLiveTime() <= Duration)
	{
		Update_Rotation(_DeltaTime);
		Update_RadiusRange(_DeltaTime);
		return;
	}

	Clear();
}

void YamadaEnergyBallCtrl::Clear()
{
	for (size_t i = 0; i < Balls.size(); ++i)
	{
		Balls[i].first->GetTransform()->SetParent(nullptr);
		Balls[i].first->DestroyBall();
	}

	Balls.clear();

	Death();
}


void YamadaEnergyBallCtrl::Update_Rotation(float _DeltaTime)
{
	for (size_t i = 0; i < Balls.size(); ++i)
	{
		Balls[i].second += GameEngineMath::PIE2 * _DeltaTime;
		float NowRot = Balls[i].second;

		static float4 Pos = float4::Zero;
		Pos.x = cosf(NowRot) * XRadius;
		Pos.y = sinf(NowRot) * YRadius;
		Pos.z = Pos.y;

		Balls[i].first->GetTransform()->SetLocalPosition(Pos);
	}
}


void YamadaEnergyBallCtrl::Update_RadiusRange(float _DeltaTime)
{
	RadiusTimer += _DeltaTime;

	float Ratio = std::clamp(RadiusTimer / Duration, 0.f ,1.f);
	float SinValue = sinf(GameEngineMath::PIE * Ratio);

	float AddRadiusX = RadiusOffsetX * SinValue;
	float AddRadiusY = RadiusOffsetY * SinValue;

	XRadius = OriginXRadius + AddRadiusX;
	YRadius = OriginYRadius + AddRadiusY;
}