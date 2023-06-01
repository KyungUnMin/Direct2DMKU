#include "PrecompileHeader.h"
#include "GameEngineButton.h"
#include "GameEngineUIRenderer.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "GameEngineLevel.h"
#include "GameEngineCamera.h"

GameEngineButton::GameEngineButton()
{
}

GameEngineButton::~GameEngineButton()
{
}

void GameEngineButton::Start()
{
	Render = CreateComponent<GameEngineUIRenderer>();
}

void GameEngineButton::Update(float _Delta)
{
	float4 Scale = Render->GetTransform()->GetWorldScale();
	float4 Pos = Render->GetTransform()->GetWorldPosition();

	/*
		마우스는 윈도우 좌표계다
		UI는 월드 좌표계다
			모든 물체는
			월드좌표(크자이공부) -> 뷰 -> 프로젝션 -> 뷰포트 과정을 통해
			윈도우 좌표계로 변환된다.
	*/

	//마우스의 윈도우 좌표를 이 카메라의 월드좌표로 바꾸기 위해 뷰포트, 프로젝션, 뷰 행렬을 가져온다
	// (이 방식은 직교 투영일때만 가능하다.)
	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	float4x4 ViewPort = Camera->GetViewPort();
	float4x4 Proj = Camera->GetProjection();
	float4x4 View = Camera->GetView();
	//이렇게 좌표를 바꾸는 과정은 나중에 그림자를 만들대도 사용한다

	float4 Mouse = GameEngineInput::GetMousePosition();
	Mouse *= ViewPort.InverseReturn();
	Mouse *= Proj.InverseReturn();
	Mouse *= View.InverseReturn();


	CollisionData MouseData;
	MouseData.SPHERE.Center = Mouse.DirectFloat3;
	MouseData.SPHERE.Radius = 0.0f;

	//충돌 체크
	if (true == GameEngineTransform::AABB2DToSpehre2D(Render->GetTransform()->GetCollisionData(), MouseData))
	{
		//마우스버튼이 눌린  순간
		if (true == GameEngineInput::IsUp("EngineMouseLeft"))
		{
			//콜백 호출
			if (nullptr != Click)
			{
				Click();
			}
		}
	}

}


