#include "PrecompileHeader.h"
#include "GameEngineCamera.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineDevice.h"

GameEngineCamera::GameEngineCamera()
{

}

GameEngineCamera::~GameEngineCamera()
{

}


void GameEngineCamera::Start()
{
	if (false == GameEngineInput::IsKey("CamMoveLeft"))
	{
		GameEngineInput::CreateKey("CamMoveLeft", 'A');
		GameEngineInput::CreateKey("CamMoveRight", 'D');
		GameEngineInput::CreateKey("CamMoveUp", 'Q');
		GameEngineInput::CreateKey("CamMoveDown", 'E');
		GameEngineInput::CreateKey("CamMoveForward", 'W');
		GameEngineInput::CreateKey("CamMoveBack", 'S');

		GameEngineInput::CreateKey("RotY+", 'L');
		GameEngineInput::CreateKey("RotY-", 'J');
		GameEngineInput::CreateKey("RotZ+", 'O');
		GameEngineInput::CreateKey("RotZ-", 'U');
		GameEngineInput::CreateKey("RotX+", 'I');
		GameEngineInput::CreateKey("RotX-", 'K');

		GameEngineInput::CreateKey("SpeedBoost", VK_LSHIFT);
		GameEngineInput::CreateKey("FreeCameraSwitch", 'P');
	}

	//�����Ͷ������� ���� ����Ʈ��� ���� ����
	ViewPortData.TopLeftX = 0;
	ViewPortData.TopLeftY = 0;
	ViewPortData.Width = GameEngineWindow::GetScreenSize().x;
	ViewPortData.Height= GameEngineWindow::GetScreenSize().y;
	ViewPortData.MinDepth = 0.0f;
	ViewPortData.MaxDepth = 1.0f;
}

void GameEngineCamera::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("FreeCameraSwitch"))
	{
		FreeCamera = !FreeCamera;
	}

	if (true == FreeCamera)
	{
		float Speed = 200.0f;
		float RotSpeed = 180.f;

		if (true == GameEngineInput::IsPress("SpeedBoost"))
		{
			Speed = 500.0f;
		}

		if (true == GameEngineInput::IsPress("CamMoveLeft"))
		{
			GetTransform()->AddLocalPosition(float4::Left * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("CamMoveRight"))
		{
			GetTransform()->AddLocalPosition(float4::Right * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("CamMoveUp"))
		{
			GetTransform()->AddLocalPosition(float4::Up * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("CamMoveDown"))
		{
			GetTransform()->AddLocalPosition(float4::Down * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("CamMoveForward"))
		{
			GetTransform()->AddLocalPosition(float4::Forward * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("CamMoveBack"))
		{
			GetTransform()->AddLocalPosition(float4::Back * Speed * _DeltaTime);
		}

		if (true == GameEngineInput::IsPress("RotY+"))
		{
			GetTransform()->AddLocalRotation({ 0.0f, RotSpeed * _DeltaTime, 0.0f });
		}
		if (true == GameEngineInput::IsPress("RotY-"))
		{
			GetTransform()->AddLocalRotation({ 0.0f, -RotSpeed * _DeltaTime, 0.0f });
		}
		if (true == GameEngineInput::IsPress("RotZ+"))
		{
			GetTransform()->AddLocalRotation({ 0.0f, 0.0f, RotSpeed * _DeltaTime });
		}
		if (true == GameEngineInput::IsPress("RotZ-"))
		{
			GetTransform()->AddLocalRotation({ 0.0f, 0.0f, -RotSpeed * _DeltaTime });
		}
		if (true == GameEngineInput::IsPress("RotX+"))
		{
			GetTransform()->AddLocalRotation({ RotSpeed * _DeltaTime, 0.0f, 0.0f });
		}
		if (true == GameEngineInput::IsPress("RotX-"))
		{
			GetTransform()->AddLocalRotation({ -RotSpeed * _DeltaTime, 0.0f, 0.0f });
		}

	}

	//���� ī�޶��� �� �� ���
	float4 EyeDir = GetTransform()->GetLocalForwardVector();
	float4 EyeUp = GetTransform()->GetLocalUpVector();
	float4 EyePos = GetTransform()->GetLocalPosition();

	//����� �����
	View.LookToLH(EyePos, EyeDir, EyeUp);

	//������� �����
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	Projection.PersperctiveFovLH(60.f, (ScreenSize.x / ScreenSize.y), Near, Far);

	//����Ʈ��� �����
	ViewPort.ViewPort(ScreenSize.x, ScreenSize.y, 0.f, 0.f);
}


void GameEngineCamera::Setting()
{
	//������ �������� �� ������ �Ѱ��� ����
	GameEngineDevice::GetContext()->RSSetViewports(1, &ViewPortData);
}
