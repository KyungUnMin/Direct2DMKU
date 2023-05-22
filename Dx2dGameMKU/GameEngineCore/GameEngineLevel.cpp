#include "PrecompileHeader.h"
#include "GameEngineLevel.h"

#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineGUI.h"
#include "GameEngineCollision.h"
#include "GameEngineDevice.h"
#include "GameEngineRenderTarget.h"

GameEngineLevel::GameEngineLevel()
{
	//메인 카메라 0번
	MainCamera = CreateActor<GameEngineCamera>();
	Cameras.insert(std::make_pair(0, MainCamera));

	//UI 카메라 100번
	std::shared_ptr<GameEngineCamera> UICamera = CreateActor<GameEngineCamera>();
	UICamera->SetProjectionType(CameraType::Orthogonal);
	Cameras.insert(std::make_pair(100, UICamera));
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

			for (; ActorStart != ActorEnd; ++ActorStart)
			{
				std::shared_ptr<GameEngineActor>& Actor = *ActorStart;

				Actor->AllAccTime(_DeltaTime);
				Actor->AllUpdate(_DeltaTime);

				/*if (false == Actor->IsUpdate())
					continue;

				GameEngineTransform* Transform = Actor->GetTransform();
				Transform->AllAccTime(_DeltaTime);
				Transform->AllUpdate(_DeltaTime);*/
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
	}
	
	//이 레벨에 존재하는 카메라 순회
	for (std::pair<int, std::shared_ptr<GameEngineCamera>> Pair : Cameras)
	{
		std::shared_ptr<GameEngineCamera> Camera = Pair.second;
		std::shared_ptr<GameEngineRenderTarget> Target = Camera->GetCamTarget();

		//메인 백버퍼에 카메라들의 이미지들을 덮어쓴다
		GameEngineDevice::GetBackBufferTarget()->Merge(Target);
	}
	
	//imgui 렌더
	GameEngineGUI::Render(GetSharedThis(), _DeltaTime);
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