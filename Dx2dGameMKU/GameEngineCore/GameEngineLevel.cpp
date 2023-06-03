#include "PrecompileHeader.h"
#include "GameEngineLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>

#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineGUI.h"
#include "GameEngineCollision.h"
#include "GameEngineDevice.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineDebug3D.h"

bool GameEngineLevel::IsDebugRender = false;

GameEngineLevel::GameEngineLevel()
{
	//메인 카메라 0번
	MainCamera = CreateActor<GameEngineCamera>();
	Cameras.insert(std::make_pair(0, MainCamera));

	//UI 카메라 100번
	std::shared_ptr<GameEngineCamera> UICamera = CreateActor<GameEngineCamera>();
	UICamera->SetProjectionType(CameraType::Orthogonal);
	Cameras.insert(std::make_pair(100, UICamera));

	//모든 카메라의 이미지가 종합된 도화지 생성(포스트 프로세싱때 효과를 주기 위함)
	LastTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::Null);
}

GameEngineLevel::~GameEngineLevel()
{

}


void GameEngineLevel::ActorUpdate(float _DeltaTime)
{
	//프리 카메라 모드일땐 카메라 제외하고 업데이트 실행X
	if (true == MainCamera->IsFreeCamera())
	{
		MainCamera->Update(_DeltaTime);
		return;
	}


	//모든 엑터들의 업데이트 함수가 호출되는 부분
	{
		std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<std::shared_ptr<GameEngineActor>>& ActorList = GroupStartIter->second;

			std::list<std::shared_ptr<GameEngineActor>>::iterator ActorStart = ActorList.begin();
			std::list<std::shared_ptr<GameEngineActor>>::iterator ActorEnd = ActorList.end();

			//해당 그룹의 타임 스케일
			float ScaleTime = _DeltaTime * GameEngineTime::GlobalTime.GetUpdateOrderTimeScale(GroupStartIter->first);

			for (; ActorStart != ActorEnd; ++ActorStart)
			{
				std::shared_ptr<GameEngineActor>& Actor = *ActorStart;

				Actor->AllAccTime(ScaleTime);
				Actor->AllUpdate(ScaleTime);
			}
		}

	}
}




void GameEngineLevel::ActorLevelChangeStart()
{
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupStartIter = Actors.begin();
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupEndIter = Actors.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = GroupStartIter->second;

		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorStart = ActorList.begin();
		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorEnd = ActorList.end();

		for (; ActorStart != ActorEnd; ++ActorStart)
		{
			std::shared_ptr<GameEngineActor>& Actor = *ActorStart;
			Actor->AllLevelChangeStart();
		}
	}
}



void GameEngineLevel::ActorLevelChangeEnd()
{
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupStartIter = Actors.begin();
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupEndIter = Actors.end();

	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = GroupStartIter->second;

		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorStart = ActorList.begin();
		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorEnd = ActorList.end();

		for (; ActorStart != ActorEnd; ++ActorStart)
		{
			std::shared_ptr<GameEngineActor>& Actor = *ActorStart;
			Actor->AllLevelChangeEnd();
		}
	}
}







void GameEngineLevel::ActorRender(float _DeltaTime)
{
	//이 레벨에 존재하는 카메라 순회
	for (std::pair<int, std::shared_ptr<GameEngineCamera>> Pair : Cameras)
	{
		//이 카메라에 등록된 렌더들을 카메라 렌더타겟에 그린다
		std::shared_ptr<GameEngineCamera> Cam = Pair.second;
		Cam->Setting();
		Cam->CameraTransformUpdate();
		Cam->Render(_DeltaTime);


		//이 카메라에 대한 포스트 프로세싱 적용
		Cam->CamTarget->Effect(_DeltaTime);

		//콜리전 디버깅 기능이 On됐을때만
		if (false == IsDebugRender)
			continue;

		GameEngineDebug::DebugRender(Cam.get(), _DeltaTime);
	}
	
	LastTarget->Clear();

	//이 레벨에 존재하는 카메라 순회
	for (std::pair<int, std::shared_ptr<GameEngineCamera>> Pair : Cameras)
	{
		std::shared_ptr<GameEngineCamera> Camera = Pair.second;
		std::shared_ptr<GameEngineRenderTarget> Target = Camera->GetCamTarget();

		//카메라의 그림들을 LastTarget에 종합한다
		LastTarget->Merge(Target);
	}

	//전체 화면에 대한 포스트 프로세싱
	LastTarget->Effect(_DeltaTime);


	//TODO
	//LastTarget->Setting();

	
	//메인 백버퍼에 LastTarget의 이미지를 덮어쓴다
	GameEngineDevice::GetBackBufferTarget()->Merge(LastTarget);



	static bool GUIRender = true;
	if (true == GameEngineInput::IsDown("GUISwitch"))
	{
		GUIRender = !GUIRender;

		if (false == GUIRender)
		{
			GameEngineGUI::Release();
		}
		else
		{
			GameEngineGUI::Initialize();
		}
	}


	//imgui 렌더
	if (true == GUIRender)
	{
		GameEngineGUI::Render(GetSharedThis(), _DeltaTime);
	}

}

void GameEngineLevel::ActorRelease()
{
	//렌더러 릴리즈
	for (std::pair<int, std::shared_ptr<GameEngineCamera>> Pair : Cameras)
	{
		std::shared_ptr<GameEngineCamera> Cam = Pair.second;
		Cam->Release();
	}

	//콜리전 Release
	{
		std::map<int, std::list<std::shared_ptr<GameEngineCollision>>>::iterator GroupStartIter = Collisions.begin();
		std::map<int, std::list<std::shared_ptr<GameEngineCollision>>>::iterator GroupEndIter = Collisions.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<std::shared_ptr<GameEngineCollision>>& ObjectList = GroupStartIter->second;

			std::list<std::shared_ptr<GameEngineCollision>>::iterator ObjectStart = ObjectList.begin();
			std::list<std::shared_ptr<GameEngineCollision>>::iterator ObjectEnd = ObjectList.end();

			for (; ObjectStart != ObjectEnd; )
			{
				std::shared_ptr<GameEngineCollision> RelaseObject = (*ObjectStart);

				if (nullptr != RelaseObject && false == RelaseObject->IsDeath())
				{
					++ObjectStart;
					continue;
				}

				ObjectStart = ObjectList.erase(ObjectStart);
			}
		}
	}


	//엑터 Release
	{
		std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupStartIter = Actors.begin();
		std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupEndIter = Actors.end();

		for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
		{
			std::list<std::shared_ptr<GameEngineActor>>& ActorList = GroupStartIter->second;

			std::list<std::shared_ptr<GameEngineActor>>::iterator ActorStart = ActorList.begin();
			std::list<std::shared_ptr<GameEngineActor>>::iterator ActorEnd = ActorList.end();

			for (; ActorStart != ActorEnd; )
			{
				std::shared_ptr<GameEngineActor> ReleaseActor = *ActorStart;

				//제거되지 않는 엑터의 경우
				if (nullptr != ReleaseActor && false == ReleaseActor->IsDeath())
				{
					ReleaseActor->AllRelease();

					//자식들 Death가 예약되어 있는지 확인하고 다음으로 넘어감
					/*GameEngineTransform* Transform = ReleaseActor->GetTransform();
					Transform->AllRelease();*/
					++ActorStart;
					continue;
				}

				//자식들 Death가 예약되어 있는지 확인하고 그룹에서 제거
				ReleaseActor->Release();
				//(자식들의 경우엔 부모가 소멸하면서 Child list가 사라지고
				//RefCount가 감소하면서 자연적으로 사라진다)
				//(하지만 다른 shared_ptr이기 때문에 다른 객체가 shared_ptr로 가르키고 있었다면
				//메모리는 소멸하지 않는 점을 주의하자)
				ActorStart = ActorList.erase(ActorStart);
			}
		}
	}

	

}



//생성한 엑터 초기화
void GameEngineLevel::ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Level)
{
	_Actor->Level = this;
	
	//SetOrder 내부에서 레벨의 Actors에 들어간다
	_Actor->SetOrder(_Order);
	_Actor->Start();
}




void GameEngineLevel::PushCollision(std::shared_ptr<GameEngineCollision> _Collision)
{
	Collisions[_Collision->GetOrder()].push_back(_Collision);
}




void GameEngineLevel::PushCameraRenderer(std::shared_ptr<GameEngineRenderer> _Renderer, int _CameraOrder)
{
	std::shared_ptr<GameEngineCamera> FindCamera = GetCamera(_CameraOrder);
	if (nullptr == FindCamera)
	{
		MsgAssert("존재하지 않는 카메라에 랜더러를 넣을수는 없습니다.");
		return;
	}

	FindCamera->PushRenderer(_Renderer);
}


std::shared_ptr<GameEngineCamera> GameEngineLevel::GetCamera(int _CameraOrder)
{
	std::map<int, std::shared_ptr<GameEngineCamera>>::iterator FindIter = Cameras.find(_CameraOrder);
	if (FindIter == Cameras.end())
		return nullptr;

	std::shared_ptr<GameEngineCamera> Camera = FindIter->second;
	return Camera;
}

std::shared_ptr<GameEngineCamera> GameEngineLevel::CreateCamera(int _CameraNum, CameraType _ProjectionType)
{
	if (Cameras.end() != Cameras.find(_CameraNum))
	{
		std::string CamNum = GameEngineString::ToString(_CameraNum);
		MsgAssert("이미 존재하는 카메라를 또 만들려고 했습니다 : " + CamNum);
		return nullptr;
	}

	std::shared_ptr<GameEngineCamera> NewCamera = CreateActor<GameEngineCamera>();
	NewCamera->SetProjectionType(_ProjectionType);
	Cameras.insert(std::make_pair(_CameraNum, NewCamera));
	return NewCamera;
}


//void GameEngineLevel::TextureUnLoad(GameEngineLevel* _NextLevel)
//{
//	for (const std::pair<std::string, std::string>& Pair : LoadEndPath)
//	{
//		if (nullptr != _NextLevel && true == _NextLevel->TexturePath.contains(Pair.first))
//		{
//			continue;
//		}
//
//		GameEngineTexture::UnLoad(Pair.first);
//		TexturePath.insert(std::make_pair(Pair.first, Pair.second));
//	}
//
//	LoadEndPath.clear();
//}
//
//void GameEngineLevel::TextureReLoad(GameEngineLevel* _PrevLevel)
//{
//
//	for (const std::pair<std::string, std::string>& Pair : TexturePath)
//	{
//		if (nullptr != _PrevLevel && true == _PrevLevel->TexturePath.contains(Pair.first))
//		{
//			continue;
//		}
//
//		GameEngineTexture::ReLoad(Pair.second, Pair.first);
//		LoadEndPath.insert(std::make_pair(Pair.first, Pair.second));
//	}
//
//	TexturePath.clear();
//}