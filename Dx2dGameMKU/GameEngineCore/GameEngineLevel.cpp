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
	//���� ī�޶� 0��
	MainCamera = CreateActor<GameEngineCamera>();
	Cameras.insert(std::make_pair(0, MainCamera));

	//UI ī�޶� 100��
	std::shared_ptr<GameEngineCamera> UICamera = CreateActor<GameEngineCamera>();
	UICamera->SetProjectionType(CameraType::Orthogonal);
	Cameras.insert(std::make_pair(100, UICamera));

	//��� ī�޶��� �̹����� ���յ� ��ȭ�� ����(����Ʈ ���μ��̶� ȿ���� �ֱ� ����)
	LastTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::Null);
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

			//�ش� �׷��� Ÿ�� ������
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
	//�� ������ �����ϴ� ī�޶� ��ȸ
	for (std::pair<int, std::shared_ptr<GameEngineCamera>> Pair : Cameras)
	{
		//�� ī�޶� ��ϵ� �������� ī�޶� ����Ÿ�ٿ� �׸���
		std::shared_ptr<GameEngineCamera> Cam = Pair.second;
		Cam->Setting();
		Cam->CameraTransformUpdate();
		Cam->Render(_DeltaTime);


		//�� ī�޶� ���� ����Ʈ ���μ��� ����
		Cam->CamTarget->Effect(_DeltaTime);

		//�ݸ��� ����� ����� On��������
		if (false == IsDebugRender)
			continue;

		GameEngineDebug::DebugRender(Cam.get(), _DeltaTime);
	}
	
	LastTarget->Clear();

	//�� ������ �����ϴ� ī�޶� ��ȸ
	for (std::pair<int, std::shared_ptr<GameEngineCamera>> Pair : Cameras)
	{
		std::shared_ptr<GameEngineCamera> Camera = Pair.second;
		std::shared_ptr<GameEngineRenderTarget> Target = Camera->GetCamTarget();

		//ī�޶��� �׸����� LastTarget�� �����Ѵ�
		LastTarget->Merge(Target);
	}

	//��ü ȭ�鿡 ���� ����Ʈ ���μ���
	LastTarget->Effect(_DeltaTime);


	//TODO
	//LastTarget->Setting();

	
	//���� ����ۿ� LastTarget�� �̹����� �����
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


	//imgui ����
	if (true == GUIRender)
	{
		GameEngineGUI::Render(GetSharedThis(), _DeltaTime);
	}

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

std::shared_ptr<GameEngineCamera> GameEngineLevel::CreateCamera(int _CameraNum, CameraType _ProjectionType)
{
	if (Cameras.end() != Cameras.find(_CameraNum))
	{
		std::string CamNum = GameEngineString::ToString(_CameraNum);
		MsgAssert("�̹� �����ϴ� ī�޶� �� ������� �߽��ϴ� : " + CamNum);
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