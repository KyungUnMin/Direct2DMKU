#include "PrecompileHeader.h"
#include "GameEngineCamera.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>

#include "GameEngineDevice.h"
#include "GameEngineRenderer.h"
#include "GameEngineRenderTarget.h"

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
		GameEngineInput::CreateKey("CamMoveUp", 'E');
		GameEngineInput::CreateKey("CamMoveDown", 'Q');
		GameEngineInput::CreateKey("CamMoveForward", 'W');
		GameEngineInput::CreateKey("CamMoveBack", 'S');

		GameEngineInput::CreateKey("CamRot", VK_RBUTTON);
		GameEngineInput::CreateKey("SpeedBoost", VK_LSHIFT);
		GameEngineInput::CreateKey("FreeCameraSwitch", 'P');
		GameEngineInput::CreateKey("ProjectionModeChange", 'O');
	}

	//레스터라이저를 위한 뷰포트행렬 정보 세팅
	ViewPortData.TopLeftX = 0;
	ViewPortData.TopLeftY = 0;
	ViewPortData.Width = GameEngineWindow::GetScreenSize().x;
	ViewPortData.Height= GameEngineWindow::GetScreenSize().y;
	ViewPortData.MinDepth = 0.0f;
	ViewPortData.MaxDepth = 1.0f;

	Width = ViewPortData.Width;
	Height = ViewPortData.Height;


	//카메라의 렌더타겟 배경색은 투명색이여야 한다,
	//(색상 혼합의 원리를 생각하면 알 수 있다)
	CamTarget = GameEngineRenderTarget::Create(
		DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 
		GameEngineWindow::GetScreenSize(), float4::Null);
	CamTarget->CreateDepthTexture();
}



void GameEngineCamera::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("ProjectionModeChange"))
	{
		switch (ProjectionType)
		{
		case CameraType::None:
			break;
		case CameraType::Perspective:
			ProjectionType = CameraType::Orthogonal;
			break;
		case CameraType::Orthogonal:
			ProjectionType = CameraType::Perspective;
			break;
		default:
			break;
		}
	}


	if (true == GameEngineInput::IsDown("FreeCameraSwitch"))
	{
		FreeCamera = !FreeCamera;

		if (true == FreeCamera)
		{
			OldData = GetTransform()->GetTransDataRef();
		}
		else
		{
			GetTransform()->SetTransformData(OldData);
		}
	}



	if (true == FreeCamera)
	{
		float Speed = 200.0f;
		float RotSpeed = 180.f;

		if (true == GameEngineInput::IsPress("SpeedBoost"))
		{
			Speed = 1000.0f;
		}

		if (true == GameEngineInput::IsPress("CamMoveLeft"))
		{
			GetTransform()->AddLocalPosition(GetTransform()->GetWorldLeftVector() * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("CamMoveRight"))
		{
			GetTransform()->AddLocalPosition(GetTransform()->GetWorldRightVector() * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("CamMoveUp"))
		{
			GetTransform()->AddLocalPosition(GetTransform()->GetWorldUpVector() * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("CamMoveDown"))
		{
			GetTransform()->AddLocalPosition(GetTransform()->GetWorldDownVector() * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("CamMoveForward"))
		{
			GetTransform()->AddLocalPosition(GetTransform()->GetWorldForwardVector() * Speed * _DeltaTime);
		}
		if (true == GameEngineInput::IsPress("CamMoveBack"))
		{
			GetTransform()->AddLocalPosition(GetTransform()->GetWorldBackVector() * Speed * _DeltaTime);
		}

		if (true == GameEngineInput::IsPress("CamRot"))
		{
			float4 Dir = GameEngineInput::GetMouseDirectionNormal();

			float4 RotMouseDir;
			//마우스를 상하로 흔들면 x축을 중심으로 회전한다
			RotMouseDir.x = Dir.y;
			//마우스를 좌우로 흔들면 y축을 중심으로 회전한다
			RotMouseDir.y = Dir.x;

			GetTransform()->AddWorldRotation(RotMouseDir);
		}

	}

	
}


void GameEngineCamera::Setting()
{
	//여러개 세팅해줄 수 있지만 한개만 세팅
	GameEngineDevice::GetContext()->RSSetViewports(1, &ViewPortData);


	//렌더타겟뷰 설정(그림 그릴 도화지 설정) 및 청소
	CamTarget->Clear();
	CamTarget->Setting();
}

void GameEngineCamera::Render(float _DeltaTime)
{
	std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>>::iterator RenderGroupStartIter = Renderers.begin();
	std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>>::iterator RenderGroupEndIter = Renderers.end();

	//이 카메라에 등록된 렌더러들을 순회
	for (; RenderGroupStartIter != RenderGroupEndIter; ++RenderGroupStartIter)
	{
		std::list<std::shared_ptr<GameEngineRenderer>>& RenderGroup = RenderGroupStartIter->second;


		//현재 Render의 Order
		int Order = RenderGroupStartIter->first;
		std::map<int, SortType>::iterator SortIter = SortValues.find(Order);

		//소팅을 하는 그룹인 경우
		if (SortIter != SortValues.end() && SortIter->second != SortType::None)
		{
			//Z소팅인 경우
			if (SortIter->second == SortType::ZSort)
			{
				//Z소팅을 하기 전에 카메라 기준 Z값을 계산한다
				for (std::shared_ptr<GameEngineRenderer>& Render : RenderGroup)
				{
					Render->CalSortZ(this);
				}

				//Z값 기준 정렬
				RenderGroup.sort([](std::shared_ptr<GameEngineRenderer>& _Left, std::shared_ptr<GameEngineRenderer>& _Right)
				{
					return _Right->CalZ < _Left->CalZ;
				});
			}

			//나머지는 나중에
			else
			{
				//TODO
			}
		}



		std::list<std::shared_ptr<GameEngineRenderer>>::iterator StartRenderer = RenderGroup.begin();
		std::list<std::shared_ptr<GameEngineRenderer>>::iterator EndRenderer = RenderGroup.end();

		//해당 Render그룹의 타임스케일을 받아온다
		float ScaleTime = _DeltaTime * GameEngineTime::GlobalTime.GetRenderOrderTimeScale(RenderGroupStartIter->first);

		for (; StartRenderer != EndRenderer; ++StartRenderer)
		{
			std::shared_ptr<GameEngineRenderer>& Render = *StartRenderer;

			//활성화 되어있는 렌더러만
			if (false == Render->IsUpdate())
			{
				continue;
			}

			//카메라 컬링
			if (true == Render->IsCameraCulling && false == IsView(Render->GetTransform()->GetTransDataRef()))
			{
				continue;
			}

			//이 카메라의 뷰행렬과 투영행렬을 바탕으로 렌더러의 행렬을 계산
			Render->RenderTransformUpdate(this);
			//이 카메라에 렌더러를 그리기
			Render->Render(ScaleTime);
		}
	}
}


void GameEngineCamera::CameraTransformUpdate()
{
	//현재 카메라의 각 축 계산
	float4 EyeDir = GetTransform()->GetLocalForwardVector();
	float4 EyeUp = GetTransform()->GetLocalUpVector();
	float4 EyePos = GetTransform()->GetLocalPosition();

	//뷰행렬 만들기
	View.LookToLH(EyePos, EyeDir, EyeUp);


	//투영행렬 만들기
	switch (ProjectionType)
	{
	case CameraType::None:
	{
		MsgAssert("카메라 투영이 설정되지 않았습니다.");
		break;
	}
	case CameraType::Perspective:
		Projection.PersperctiveFovLH(FOV, (Width / Height), Near, Far);
		break;
	case CameraType::Orthogonal:
		Projection.OrthographicLH(Width * ZoomRatio, Height * ZoomRatio, Near, Far);
		break;
	default:
		break;
	}

	//뷰포트행렬 만들기
	float4 ScreenSize = GameEngineWindow::GetScreenSize();
	ViewPort.ViewPort(ScreenSize.x, ScreenSize.y, 0.f, 0.f);

	//카메라 시야 영역 계산
	float4 WorldPos = GetTransform()->GetWorldPosition();
	float4 Dir = GetTransform()->GetLocalForwardVector();
	Box.Center = (WorldPos + (Dir * Far * 0.5f)).DirectFloat3;
	Box.Extents.z = Far * 0.6f;
	Box.Extents.x = Width * 0.6f;
	Box.Extents.y = Height * 0.6f;
	Box.Orientation = GetTransform()->GetWorldQuaternion().DirectFloat4;
}


void GameEngineCamera::PushRenderer(std::shared_ptr<GameEngineRenderer> _Render)
{
	if (nullptr == _Render)
	{
		MsgAssert("랜더러가 nullptr 입니다");
		return;
	}

	_Render->RenderCamera = this;

	Renderers[_Render->GetOrder()].push_back(_Render);
}




bool GameEngineCamera::IsView(const TransformData& _TransData)
{
	if (true == IsFreeCamera())
	{
		return true;
	}


	switch (ProjectionType)
	{
	case CameraType::None:
	{
		MsgAssert("카메라 투영이 설정되지 않았습니다.");
		break;
	}
	case CameraType::Perspective:
		// DirectX::BoundingFrustum Box;
		break;
	case CameraType::Orthogonal:
	{
		//상대 물체는 항상 원으로 판단
		DirectX::BoundingSphere Sphere;
		Sphere.Center = _TransData.WorldPosition.DirectFloat3;
		Sphere.Radius = _TransData.WorldScale.MaxFloat() * 0.5f;

		bool IsCal = Box.Intersects(Sphere);
		return IsCal;
	}
	default:
		break;
	}

	return false;
}


void GameEngineCamera::Release()
{
	std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>>::iterator RenderGroupStartIter = Renderers.begin();
	std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>>::iterator RenderGroupEndIter = Renderers.end();

	for (; RenderGroupStartIter != RenderGroupEndIter; ++RenderGroupStartIter)
	{
		std::list<std::shared_ptr<GameEngineRenderer>>& RenderGroup = RenderGroupStartIter->second;

		std::list<std::shared_ptr<GameEngineRenderer>>::iterator StartRenderer = RenderGroup.begin();
		std::list<std::shared_ptr<GameEngineRenderer>>::iterator EndRenderer = RenderGroup.end();

		for (; StartRenderer != EndRenderer;)
		{
			std::shared_ptr<GameEngineRenderer>& Render = *StartRenderer;

			if (false == Render->IsDeath())
			{
				++StartRenderer;
				continue;
			}

			StartRenderer = RenderGroup.erase(StartRenderer);

		}
	}
}