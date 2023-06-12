#include "PrecompileHeader.h"
#include "GameEngineObject.h"

GameEngineObject::GameEngineObject()
{
	Transform.SetMaster(this);
}

GameEngineObject::~GameEngineObject()
{

}

void GameEngineObject::Release()
{
	//자식들중에서 삭제예정인 오브젝트는 Transform::list에서 제외
	Transform.ChildRelease();

	//삭제 예정인 자식들을 Object의 Childs 에서도 제외
	std::list<std::shared_ptr<GameEngineObject>>::iterator ReleaseStartIter = Childs.begin();
	std::list<std::shared_ptr<GameEngineObject>>::iterator ReleaseEndIter = Childs.end();

	for (; ReleaseStartIter != ReleaseEndIter; )
	{
		std::shared_ptr<GameEngineObject>& Object = *ReleaseStartIter;

		if (false == Object->IsDeath())
		{
			++ReleaseStartIter;
			continue;
		}

		ReleaseStartIter = Childs.erase(ReleaseStartIter);
	}
}


void GameEngineObject::AllAccTime(float _DeltaTime)
{
	if (false == IsUpdate())
		return;

	//자신의 AccTime 증가
	AccLiveTime(_DeltaTime);

	//자식들 재귀
	for (std::shared_ptr<GameEngineObject> Object : Childs)
	{
		Object->AllAccTime(_DeltaTime);
	}
}

void GameEngineObject::AllUpdate(float _DeltaTime)
{
	if (false == IsUpdate())
		return;

	//자신의 업데이트 호출
	Update(_DeltaTime);

	//자식들 재귀
	for (std::shared_ptr<GameEngineObject> Object : Childs)
	{
		Object->AllUpdate(_DeltaTime);
	}
}

void GameEngineObject::AllRender(float _DeltaTime)
{
	if (false == IsUpdate())
		return;

	//자신의 Render호출
	Render(_DeltaTime);

	//자식들 재귀
	for (std::shared_ptr<GameEngineObject> Object : Childs)
	{
		Object->AllRender(_DeltaTime);
	}
}

void GameEngineObject::AllDestroy()
{
	//자신의 함수 호출
	Destroy();

	//자식의 함수 호출
	for (std::shared_ptr<GameEngineObject> Object : Childs)
	{
		Object->AllDestroy();
	}
}

void GameEngineObject::AllRelease()
{
	//부모(자신)이 죽은 경우는 이 함수로 들어오지 않는다(Level의 Release구조 보면 알 수 있다)
	if (true == IsDeath())
		return;

	//자식들 중 삭제 예정이면 제거
	Release();

	//자식들 재귀
	for (std::shared_ptr<GameEngineObject> Object : Childs)
	{
		Object->AllRelease();
	}
}



bool GameEngineObject::IsDeath()
{
	GameEngineTransform* Trans = Transform.GetParent();

	//부모가 있는 경우
	if (nullptr != Trans)
	{
		GameEngineObject* Master = Trans->GetMaster();

		//부모가 죽었거나 내가 죽었으면 IsDeath는 true
		return GameEngineObjectBase::IsDeath() || Master->IsDeath();
	}

	//부모가 없는 경우
	return GameEngineObjectBase::IsDeath();
}

bool GameEngineObject::IsUpdate()
{
	GameEngineTransform* Trans = Transform.GetParent();

	//부모가 있는 경우
	if (nullptr != Trans)
	{
		GameEngineObject* Master = Trans->GetMaster();

		//부모가 활성화되어 있고 나도 활성화되어있으면 IsUpdate는 true
		return GameEngineObjectBase::IsUpdate() && Master->IsUpdate();
	}

	//부모가 없는 경우
	return GameEngineObjectBase::IsUpdate();
}


void GameEngineObject::AllLevelChangeStart()
{
	LevelChangeStart();

	for (std::shared_ptr<GameEngineObject> Object : Childs)
	{
		Object->AllLevelChangeStart();
	}
}


void GameEngineObject::AllLevelChangeEnd()
{
	LevelChangeEnd();

	for (std::shared_ptr<GameEngineObject> Object : Childs)
	{
		Object->AllLevelChangeEnd();
	}
}