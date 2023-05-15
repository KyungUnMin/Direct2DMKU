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
		//������Ʈ ��ü��
		if (false == _OtherCol->IsUpdate())
		{
			continue;
		}

		//�浹�ߴٸ� �浹�� ���� ����
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

	//�̹� �׷��� �����ƾ��ٸ� �� �׷쿡�� �����(���� �� �ƾ����� �ƹ� �ϵ� �Ͼ�� ����)
	std::list<std::shared_ptr<GameEngineCollision>>& Group = GetLevel()->Collisions[GetOrder()];
	Group.remove(ConThis);

	//���� ����
	GameEngineObjectBase::SetOrder(_Order);

	// ���ο� �׷쿡 ���� �߰��Ѵ�.
	GetLevel()->PushCollision(ConThis);
}


bool GameEngineCollision::CollisionAll(int _TargetGroup, ColType _ThisColType, ColType _OtherColtype, std::vector<std::shared_ptr<GameEngineCollision>>& _Col)
{
	_Col.clear();

	std::list<std::shared_ptr<GameEngineCollision>>& Group = GetLevel()->Collisions[_TargetGroup];

	for (std::shared_ptr<GameEngineCollision>& _OtherCol : Group)
	{
		//Ȱ��ȭ �Ǿ��ִ� �浹ü��
		if (false == _OtherCol->IsUpdate())
		{
			continue;
		}

		//���Ϳ� ����
		if (GetTransform()->Collision({ _OtherCol->GetTransform(),_ThisColType, _OtherColtype }))
		{
			_Col.push_back(_OtherCol);
		}
	}

	//�浹 ����
	return _Col.size() != 0;
}


