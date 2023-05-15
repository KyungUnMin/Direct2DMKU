#include "PrecompileHeader.h"
#include "GameEngineCollision.h"
#include "GameEngineLevel.h"

GameEngineCollision::GameEngineCollision()
{

}

GameEngineCollision::~GameEngineCollision()
{

}



std::shared_ptr<GameEngineCollision> GameEngineCollision::Collision(int _TargetGroup, ColType _ThisColType, ColType _OtherColtype)
{
	std::list<std::shared_ptr<GameEngineCollision>>& Group = GetLevel()->Collisions[_TargetGroup];

	for (std::shared_ptr<GameEngineCollision>& _OtherCol : Group)
	{
		//업데이트 물체만
		if (false == _OtherCol->IsUpdate())
		{
			continue;
		}

		//충돌했다면 충돌한 상대방 리턴
		if (GetTransform()->Collision({ _OtherCol->GetTransform(),_ThisColType, _OtherColtype }))
		{
			return _OtherCol;
		}
	}

	return nullptr;
}

void GameEngineCollision::SetOrder(int _Order)
{
	std::shared_ptr<GameEngineCollision> ConThis = DynamicThis<GameEngineCollision>();

	//이미 그룹이 지정됐었다면 그 그룹에서 지운다(지정 안 됐었으면 아무 일도 일어나지 않음)
	std::list<std::shared_ptr<GameEngineCollision>>& Group = GetLevel()->Collisions[GetOrder()];
	Group.remove(ConThis);

	//오더 지정
	GameEngineObjectBase::SetOrder(_Order);

	// 새로운 그룹에 나를 추가한다.
	GetLevel()->PushCollision(ConThis);
}


bool GameEngineCollision::CollisionAll(int _TargetGroup, ColType _ThisColType, ColType _OtherColtype, std::vector<std::shared_ptr<GameEngineCollision>>& _Col)
{
	_Col.clear();

	std::list<std::shared_ptr<GameEngineCollision>>& Group = GetLevel()->Collisions[_TargetGroup];

	for (std::shared_ptr<GameEngineCollision>& _OtherCol : Group)
	{
		//활성화 되어있는 충돌체만
		if (false == _OtherCol->IsUpdate())
		{
			continue;
		}

		//벡터에 저장
		if (GetTransform()->Collision({ _OtherCol->GetTransform(),_ThisColType, _OtherColtype }))
		{
			_Col.push_back(_OtherCol);
		}
	}

	//충돌 여부
	return _Col.size() != 0;
}


