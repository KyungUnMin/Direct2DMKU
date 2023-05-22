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
	//���� ī�޶� 0��
	MainCamera = CreateActor<GameEngineCamera>();
	Cameras.insert(std::make_pair(0, MainCamera));

	//UI ī�޶� 100��
	std::shared_ptr<GameEngineCamera> UICamera = CreateActor<GameEngineCamera>();
	UICamera->SetProjectionType(CameraType::Orthogonal);
	Cameras.insert(std::make_pair(100, UICamera));
}

GameEngineLevel::~GameEngineLevel()
{

}


void GameEngineLevel::ActorUpdate(float _DeltaTime)
{
	//���� ī�޶� ����϶� ī�޶� �����ϰ� ������Ʈ ����X
	if (true == MainCamera->IsFreeCamera())
	{
		MainCamera->Update(_DeltaTime);
		return;
	}


	//��� ���͵��� ������Ʈ �Լ��� ȣ��Ǵ� �κ�
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
	//�� ������ �����ϴ� ī�޶� ��ȸ
	for (std::pair<int, std::shared_ptr<GameEngineCamera>> Pair : Cameras)
	{
		//�� ī�޶� ��ϵ� �������� ī�޶� ����Ÿ�ٿ� �׸���
		std::shared_ptr<GameEngineCamera> Cam = Pair.second;
		Cam->Setting();
		Cam->CameraTransformUpdate();
		Cam->Render(_DeltaTime);
	}
	
	//�� ������ �����ϴ� ī�޶� ��ȸ
	for (std::pair<int, std::shared_ptr<GameEngineCamera>> Pair : Cameras)
	{
		std::shared_ptr<GameEngineCamera> Camera = Pair.second;
		std::shared_ptr<GameEngineRenderTarget> Target = Camera->GetCamTarget();

		//���� ����ۿ� ī�޶���� �̹������� �����
		GameEngineDevice::GetBackBufferTarget()->Merge(Target);
	}
	
	//imgui ����
	GameEngineGUI::Render(GetSharedThis(), _DeltaTime);
}

void GameEngineLevel::ActorRelease()
{
	//������ ������
	for (std::pair<int, std::shared_ptr<GameEngineCamera>> Pair : Cameras)
	{
		std::shared_ptr<GameEngineCamera> Cam = Pair.second;
		Cam->Release();
	}

	//�ݸ��� Release
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


	//���� Release
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

				//���ŵ��� �ʴ� ������ ���
				if (nullptr != ReleaseActor && false == ReleaseActor->IsDeath())
				{
					ReleaseActor->AllRelease();

					//�ڽĵ� Death�� ����Ǿ� �ִ��� Ȯ���ϰ� �������� �Ѿ
					/*GameEngineTransform* Transform = ReleaseActor->GetTransform();
					Transform->AllRelease();*/
					++ActorStart;
					continue;
				}

				//�ڽĵ� Death�� ����Ǿ� �ִ��� Ȯ���ϰ� �׷쿡�� ����
				ReleaseActor->Release();
				//(�ڽĵ��� ��쿣 �θ� �Ҹ��ϸ鼭 Child list�� �������
				//RefCount�� �����ϸ鼭 �ڿ������� �������)
				//(������ �ٸ� shared_ptr�̱� ������ �ٸ� ��ü�� shared_ptr�� ����Ű�� �־��ٸ�
				//�޸𸮴� �Ҹ����� �ʴ� ���� ��������)
				ActorStart = ActorList.erase(ActorStart);
			}
		}
	}

	

}



//������ ���� �ʱ�ȭ
void GameEngineLevel::ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Level)
{
	_Actor->Level = this;
	
	//SetOrder ���ο��� ������ Actors�� ����
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
		MsgAssert("�������� �ʴ� ī�޶� �������� �������� �����ϴ�.");
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