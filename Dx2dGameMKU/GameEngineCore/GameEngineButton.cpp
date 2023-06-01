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
		���콺�� ������ ��ǥ���
		UI�� ���� ��ǥ���
			��� ��ü��
			������ǥ(ũ���̰���) -> �� -> �������� -> ����Ʈ ������ ����
			������ ��ǥ��� ��ȯ�ȴ�.
	*/

	//���콺�� ������ ��ǥ�� �� ī�޶��� ������ǥ�� �ٲٱ� ���� ����Ʈ, ��������, �� ����� �����´�
	// (�� ����� ���� �����϶��� �����ϴ�.)
	std::shared_ptr<GameEngineCamera> Camera = GetLevel()->GetCamera(100);
	float4x4 ViewPort = Camera->GetViewPort();
	float4x4 Proj = Camera->GetProjection();
	float4x4 View = Camera->GetView();
	//�̷��� ��ǥ�� �ٲٴ� ������ ���߿� �׸��ڸ� ����뵵 ����Ѵ�

	float4 Mouse = GameEngineInput::GetMousePosition();
	Mouse *= ViewPort.InverseReturn();
	Mouse *= Proj.InverseReturn();
	Mouse *= View.InverseReturn();


	CollisionData MouseData;
	MouseData.SPHERE.Center = Mouse.DirectFloat3;
	MouseData.SPHERE.Radius = 0.0f;

	//�浹 üũ
	if (true == GameEngineTransform::AABB2DToSpehre2D(Render->GetTransform()->GetCollisionData(), MouseData))
	{
		//���콺��ư�� ����  ����
		if (true == GameEngineInput::IsUp("EngineMouseLeft"))
		{
			//�ݹ� ȣ��
			if (nullptr != Click)
			{
				Click();
			}
		}
	}

}


