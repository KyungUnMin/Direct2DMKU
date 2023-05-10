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