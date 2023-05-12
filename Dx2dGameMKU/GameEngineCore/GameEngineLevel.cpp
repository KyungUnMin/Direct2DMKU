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
	//부모가 있는 오브젝트라면 레벨의 List에서 제외시키고
	//부모쪽을 통해 Update 및 Render 들의 함수를 호출받게끔 한다
	//{
	//	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupStartIter = Actors.begin();
	//	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupEndIter = Actors.end();
	//	//오더 순회
	//	for (; GroupStartIter != GroupEndIter;++GroupStartIter)
	//	{
	//		std::list<std::shared_ptr<GameEngineActor>>& ActorList = GroupStartIter->second;
	//		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorStart = ActorList.begin();
	//		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorEnd = ActorList.end();
	//		//엑터 순회
	//		for (; ActorStart != ActorEnd; )
	//		{
	//			std::shared_ptr<GameEngineActor> CheckActor = (*ActorStart);
	//			GameEngineTransform* ParentTransform = CheckActor->GetTransform()->Parent;
	//			//부모가 있는 애들만 검출(부모가 있으면 리스트에서 제외)
	//			if (nullptr != ParentTransform)
	//			{
	//				GameEngineObject* Object = ParentTransform->GetMaster();
	//				if (nullptr == Object)
	//				{
	//					MsgAssert("부모가 없는 트랜스폼을 Level에서 사용할수는 없습니다.");
	//				}
	//				// 레벨의 리스트가 이 오브젝트를 갖는것이 아니라
	//				//부모가 이 오브젝트를 책임진다
	//				//(자식으로 들어갈 Object의 Shared_ptr ref를 유지시키기 위해
	//				//Transform의 Child 뿐만 아니라 Object의 Childs에도 자식으로 보관한다)
	//				Object->Childs.push_back(CheckActor);
	//				//그룹에서 제거
	//				ActorStart = ActorList.erase(ActorStart);
	//				continue;
	//			}
	//			++ActorStart;
	//		}
	//	}
	//}



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



void GameEngineLevel::ActorRender(float _DeltaTime)
{
	//랜파 래스터라이저 과정을 위해 GPU에 뷰 행렬 정보 등록
	GetMainCamera()->Setting();


	//모든 엑터들과 컴포넌트들의 렌더 호출
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupStartIter = Actors.begin();
	std::map<int, std::list<std::shared_ptr<GameEngineActor>>>::iterator GroupEndIter = Actors.end();

	//그룹순회
	for (; GroupStartIter != GroupEndIter; ++GroupStartIter)
	{
		std::list<std::shared_ptr<GameEngineActor>>& ActorList = GroupStartIter->second;

		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorStart = ActorList.begin();
		std::list<std::shared_ptr<GameEngineActor>>::iterator ActorEnd = ActorList.end();

		//엑터 순회
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


//생성한 엑터 초기화
void GameEngineLevel::ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order, GameEngineLevel* _Level)
{
	_Actor->Level = this;
	
	_Actor->SetOrder(_Order);
	_Actor->Start();

	Actors[_Order].push_back(_Actor);
}

