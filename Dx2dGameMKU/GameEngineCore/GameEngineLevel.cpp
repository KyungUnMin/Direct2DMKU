#include "PrecompileHeader.h"
#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCamera.h"
#include "GameEngineGUI.h"

GameEngineLevel::GameEngineLevel()
{
	MainCamera = CreateActor<GameEngineCamera>();
}

GameEngineLevel::~GameEngineLevel()
{

}


void GameEngineLevel::ActorUpdate(float _DeltaTime)
{
	//�θ� �ִ� ������Ʈ��� ������ List���� ���ܽ�Ű��
	//�θ����� ���� Update �� Render ���� �Լ��� ȣ��ްԲ� �Ѵ�
	//{
	//	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupStartIter = Actors.begin();
	//	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupEndIter = Actors.end();
	//	//���� ��ȸ
	//	for (; GroupStartIter != GroupEndIter;++GroupStartIter)
	//	{
	//		std::list<std::shared_ptr<GameEngineActor>>& ActorList = GroupStartIter->second;
	//		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorStart = ActorList.begin();
	//		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorEnd = ActorList.end();
	//		//���� ��ȸ
	//		for (; ActorStart != ActorEnd; )
	//		{
	//			std::shared_ptr<GameEngineActor> CheckActor = (*ActorStart);
	//			GameEngineTransform* ParentTransform = CheckActor->GetTransform()->Parent;
	//			//�θ� �ִ� �ֵ鸸 ����(�θ� ������ ����Ʈ���� ����)
	//			if (nullptr != ParentTransform)
	//			{
	//				GameEngineObject* Object = ParentTransform->GetMaster();
	//				if (nullptr == Object)
	//				{
	//					MsgAssert("�θ� ���� Ʈ�������� Level���� ����Ҽ��� �����ϴ�.");
	//				}
	//				// ������ ����Ʈ�� �� ������Ʈ�� ���°��� �ƴ϶�
	//				//�θ� �� ������Ʈ�� å������
	//				//(�ڽ����� �� Object�� Shared_ptr ref�� ������Ű�� ����
	//				//Transform�� Child �Ӹ� �ƴ϶� Object�� Childs���� �ڽ����� �����Ѵ�)
	//				Object->Childs.push_back(CheckActor);
	//				//�׷쿡�� ����
	//				ActorStart = ActorList.erase(ActorStart);
	//				continue;
	//			}
	//			++ActorStart;
	//		}
	//	}
	//}



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



void GameEngineLevel::ActorRender(float _DeltaTime)
{
	//���� �����Ͷ����� ������ ���� GPU�� �� ��� ���� ���
	GetMainCamera()->Setting();


	//��� ���͵�� ������Ʈ���� ���� ȣ��
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupStartIter = Actors.begin();
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupEndIter = Actors.end();

	//�׷��ȸ
	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = GroupStartIter->second;

		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorStart = ActorList.begin();
		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorEnd = ActorList.end();

		//���� ��ȸ
		for (; ActorStart != ActorEnd; ++ActorStart)
		{
			std::shared_ptr<GameEngineActor>& Actor = *ActorStart;

			Actor->AllRender(_DeltaTime);

			/*if (false == Actor->IsUpdate())
				continue;

			GameEngineTransform* Transform = Actor->GetTransform();
			Transform->AllRender(_DeltaTime);*/
		}
	}


	GameEngineGUI::Render(GetSharedThis(), _DeltaTime);
}

void GameEngineLevel::ActorRelease()
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


//������ ���� �ʱ�ȭ
void GameEngineLevel::ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Level)
{
	_Actor->Level = this;
	
	_Actor->SetOrder(_Order);
	_Actor->Start();

	Actors[_Order].push_back(_Actor);
}

