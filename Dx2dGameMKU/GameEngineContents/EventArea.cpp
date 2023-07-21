#include "PrecompileHeader.h"
#include "EventArea.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "RCGEnums.h"

#include "TutorialUI.h"

EventArea::EventArea()
{

}

EventArea::~EventArea()
{

}

void EventArea::Start()
{
	GameEngineActor::Start();

	Collider = CreateComponent<GameEngineCollision>(CollisionOrder::Event);
	Collider->GetTransform()->SetLocalScale(float4::One);
	Collider->SetColType(ColType::AABBBOX2D);
}

void EventArea::Update(float _DeltaTime) 
{
	GameEngineActor::Update(_DeltaTime);

	if (nullptr == Collider->Collision(CollisionOrder::PlayerMain, ColType::AABBBOX2D, ColType::SPHERE2D))
		return;

	if (nullptr != CallBack)
	{
		CallBack();
		CallBack = nullptr;
	}

	Death();
}

void EventArea::Init_Tutorial(
	const std::string_view& _TutoTitle,
	const std::string_view& _TutoDesc)
{
	CallBack = [=]()
	{
		TutorialUI::BindTurorial(_TutoTitle, _TutoDesc, []()
		{
			return true;
		});
	};
}