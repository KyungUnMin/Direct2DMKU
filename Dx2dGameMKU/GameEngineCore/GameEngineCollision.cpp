#include "PrecompileHeader.h"
#include "GameEngineCollision.h"
#include "GameEngineLevel.h"
#include "GameEngineCamera.h"

GameEngineRenderUnit GameEngineCollision::DebugUnit;

GameEngineCollision::GameEngineCollision()
{

}

GameEngineCollision::~GameEngineCollision()
{

}

void GameEngineCollision::Start()
{
	SetDebugCamera(GetLevel()->GetCamera(0).get());
}

std::shared_ptr<GameEngineCollision> GameEngineCollision::Collision(int _TargetGroup, ColType _ThisColType, ColType _OtherColtype)
{
	if (false == this->IsUpdate())
	{
		return nullptr;
	}

	std::list<std::shared_ptr<GameEngineCollision>>& Group = GetLevel()->Collisions[_TargetGroup];

	//�Լ� ȣ��� �ڽ��� �浹 Ÿ���� �������� �ʾҴٸ� �ڽ��� ColType����
	if (_ThisColType == ColType::MAX)
	{
		_ThisColType = Type;
	}

	for (std::shared_ptr<GameEngineCollision>& _OtherCol : Group)
	{
		//������Ʈ ��ü��
		if (false == _OtherCol->IsUpdate())
		{
			continue;
		}

		//�Լ� ȣ��� ������ �浹 Ÿ���� �������� �ʾҴٸ� ������ ColType����
		if (_OtherColtype == ColType::MAX)
		{
			_OtherColtype = _OtherCol->Type;
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


bool GameEngineCollision::CollisionAll(int _TargetGroup, std::vector<std::shared_ptr<GameEngineCollision>>& _Col, ColType _ThisColType, ColType _OtherColtype)
{
	_Col.clear();

	if (false == this->IsUpdate())
	{
		return false;
	}

	//�Լ� ȣ��� �ڽ��� �浹 Ÿ���� �������� �ʾҴٸ� �ڽ��� ColType����
	if (Type == ColType::MAX)
	{
		_ThisColType = Type;
	}

	std::list<std::shared_ptr<GameEngineCollision>>& Group = GetLevel()->Collisions[_TargetGroup];

	//�ش� �׷��� ����ִ� ���
	if (true == Group.empty())
		return false;


	for (std::shared_ptr<GameEngineCollision>& _OtherCol : Group)
	{
		//Ȱ��ȭ �Ǿ��ִ� �浹ü��
		if (false == _OtherCol->IsUpdate())
		{
			continue;
		}

		//�Լ� ȣ��� ������ �浹 Ÿ���� �������� �ʾҴٸ� ������ ColType����
		if (_OtherColtype == ColType::MAX)
		{
			_OtherColtype = _OtherCol->Type;
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




void GameEngineCollision::DebugRender(float _DeltaTime)
{
	DebugUnit.Render(_DeltaTime);

	//TODO
}

