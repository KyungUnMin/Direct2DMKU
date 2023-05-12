#include "PrecompileHeader.h"
#include "GameEngineTransform.h"
#include "GameEngineObject.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"

GameEngineTransform::GameEngineTransform()
{
	TransformUpdate();
}

GameEngineTransform::~GameEngineTransform()
{
}



//���� Transform�� �����ϴ� ���� ��� ����� �ȴ�
//�ݴ�� �� �����̸� ��� �ȵȴ�
void GameEngineTransform::TransformUpdate()
{
	//ũ����� �����
	TransData.ScaleMatrix.Scale(TransData.Scale);

	//ȸ����� �����
	TransData.Rotation.w = 0.0f;

	//�����̼� -> ���ʹϾ�
	TransData.Quaternion = TransData.Rotation.EulerDegToQuaternion();
	//���ʹϾ� -> �����̼� ���
	TransData.RotationMatrix = TransData.Quaternion.QuaternionToRotationMatrix();

	//�̵���� �����
	TransData.PositionMatrix.Pos(TransData.Position);

	//ũ���� ������ ���� ��� ���
	TransData.LocalWorldMatrix = TransData.ScaleMatrix * TransData.RotationMatrix * TransData.PositionMatrix;



	//�θ� ���� ���
	if (nullptr == Parent)
	{
		TransData.WorldMatrix = TransData.LocalWorldMatrix;
	}

	//�θ� �ִ� ���
	else 
	{
		WorldCalculation();
	}


	//�ڽ��� ���� ��Ŀ��� ���� ũ���� ����
	WorldDecompose();
	
	//�ڽ��� ���� ��Ŀ��� ���� ũ���� ����
	LocalDecompose();
}


void GameEngineTransform::WorldCalculation()
{
	//�θ��� ���� ����� ���� ũ���̷� �����Ѵ�
	float4x4 ParentWorldMatrix = Parent->GetWorldMatrixRef();
	float4 PScale, PRoatation, PPosition;
	ParentWorldMatrix.Decompose(PScale, PRoatation, PPosition);

	//�ٵ� ���� ���� ũ�⸦ ������̶�� �θ��� ũ��� ����
	if (true == AbsoluteScale)
	{
		PScale = float4::One;
	}

	//�ٵ� ���� ���� ȸ���� ������̶�� �θ��� ȸ���� ����
	if (true == AbsoluteRotation)
	{
		PRoatation = float4::Zero;
		//xyz 0�� ���ʹϾ� ����
		PRoatation.EulerDegToQuaternion();
	}

	//�ٵ� ���� ���� �̵��� ������̶�� �θ��� �̵��� ����
	if (true == AbsolutePosition)
	{
		PPosition = float4::Zero;
	}


	//������ ���� ���� �������� ��� �����
	float4x4 MatScale, MatRot, MatPos;
	MatScale.Scale(PScale);
	MatRot = PRoatation.QuaternionToRotationMatrix();
	MatPos.Pos(PPosition);


	//�ڽ��� ���� ��� = �ڽ��� ������Ŀ� �θ��� ���� ��� ���ϱ�
	TransData.WorldMatrix = TransData.LocalWorldMatrix * (MatScale * MatRot * MatPos);
}


void GameEngineTransform::LocalDecompose()
{
	TransData.LocalWorldMatrix.Decompose(TransData.LocalScale, TransData.LocalQuaternion, TransData.LocalPosition);
	TransData.LocalRotation = TransData.LocalQuaternion.QuaternionToEulerDeg();
}


void GameEngineTransform::WorldDecompose()
{
	TransData.WorldMatrix.Decompose(TransData.WorldScale, TransData.WorldQuaternion, TransData.WorldPosition);
	TransData.WorldRotation = TransData.WorldQuaternion.QuaternionToEulerDeg();
}




void GameEngineTransform::SetParent(GameEngineTransform* _Parent)
{
	//���� �ڽ��� �и���ų�� �и���Ű�� ����� Component���� �˻�
	if ((nullptr == Parent) && (nullptr == Master))
	{
		if (nullptr == dynamic_cast<GameEngineActor*>(Master))
		{
			MsgAssert("���͸��� ��Ʈ ����Ʈ�� �߰��ɼ� �ֽ��ϴ�.");
			return;
		}
	}


	//�� ��ü�� �̹� �ֻ��� �θ��ε� �ֻ��� �θ�� �ű���� �ൿ
	if (nullptr == Parent && nullptr == _Parent)
		return;


	//������ �θ� ������ �־��ٸ�
	if (nullptr != Parent)
	{
		//�θ��� Transform �ڽ� �׷쿡�� �ڱ��ڽ��� ����
		Parent->Child.remove(this);
		
		//�θ��� Object
		GameEngineObject* ParentMaster = Parent->Master;
		if (nullptr == ParentMaster)
		{
			MsgAssert("�����Ҽ� ���� ��Ȳ�Դϴ� Master�� nullptr�Դϴ�");
			return;
		}

		//�θ��� Object �ڽ� �׷쿡�� �ڽ��� Object�� ������ ��
		//RefCount�� 0�� �Ǽ� �Ҹ�� ���� �ִ�, ������ ���⼭ �޾Ƴ��� RefCount�� ������Ų��
		std::shared_ptr<GameEngineObject> MasterPtr = Master->shared_from_this();

		ParentMaster->Childs.remove(MasterPtr);
		Parent = nullptr;
	}


	//�θ� ����
	Parent = _Parent;


	//�θ� ����ų� �ٲ�ٸ�
	if (nullptr != Parent)
	{

		//�ڽ��� ���� ��Ŀ� �θ��� ���� ����� ������� ���Ѵ�
		TransData.LocalWorldMatrix = TransData.WorldMatrix * Parent->TransData.LocalWorldMatrix.InverseReturn();
		//���� ��ķκ��� ũ���� ����
		LocalDecompose();

		//TransformUpdate�� ���� �� ����
		TransData.Position = TransData.LocalPosition;
		TransData.Rotation = TransData.LocalRotation;
		TransData.Scale = TransData.LocalScale;

		//���� ��ġ ���
		TransformUpdate();

		AbsoluteReset();

		//�θ��� Transform �ڽĸ���Ʈ�� �ڱ� �ڽ��� ���
		Parent->Child.push_back(this);

		//�θ��� Object �ڽĸ���Ʈ�� �ڱ� �ڽ��� ���
		Parent->Master->Childs.push_back(Master->shared_from_this());
	}


	//�θ� ������ٸ�
	else
	{
		//�ڽ��� ������ĸ� �������� ũ���� ���� ����
		WorldDecompose();

		//TransformUpdate�� ���� �� ����
		TransData.Position = TransData.WorldPosition;
		TransData.Rotation = TransData.WorldRotation;
		TransData.Scale = TransData.WorldScale;

		//�� ����
		TransformUpdate();
		AbsoluteReset();

		//������ �־��� ������ ���ư���
		GameEngineLevel* Level = Master->GetLevel();
		std::shared_ptr<GameEngineObject> MasterPtr = Master->shared_from_this();

		//�� ��ü�� ������ ��쿡��
		if (nullptr != dynamic_cast<GameEngineActor*>(Master))
		{
			Level->Actors[MasterPtr->GetOrder()].push_back(std::dynamic_pointer_cast<GameEngineActor>(MasterPtr));
		}
		else
		{
			MsgAssert("���͸��� ������ ��Ʈ ������Ʈ�� ������ �� �ֽ��ϴ�.");
		}
	}
	
}




void GameEngineTransform::CalChild()
{
	//�ڽĵ� ��ȸ
	for (GameEngineTransform* ChildTrans : Child)
	{
		////�ڽ��� ũ�Ⱑ ������ �������̶��
		//if (false == ChildTrans->AbsoluteScale)
		//{
		//	//�ڽ�(�θ�)�� �ٲ����, �׿� ���� �ڽĵ� �� ���
		//	ChildTrans->SetLocalScale(ChildTrans->GetLocalScale());
		//}
		////�ڽ��� ȸ���� ������ �������̶��
		//if (false == ChildTrans->AbsoluteRotation)
		//{
		//	//�ڽ�(�θ�)�� �ٲ����, �׿� ���� �ڽĵ� �� ���
		//	ChildTrans->SetLocalRotation(ChildTrans->GetLocalRotation());
		//}
		////�ڽ��� ��ġ�� ������ �������̶��
		//if (false == ChildTrans->AbsolutePosition)
		//{
		//	//�ڽ�(�θ�)�� �ٲ����, �׿� ���� �ڽĵ� �� ���
		//	ChildTrans->SetLocalPosition(ChildTrans->GetLocalPosition());
		//}


		//�� ����� �������� �ڽĵ��� ���� ����� ����Ѵ�
		ChildTrans->WorldCalculation();
		//���� ũ���� ����
		ChildTrans->WorldDecompose();
		//���
		ChildTrans->CalChild();
	}

}



float4 GameEngineTransform::GetLocalPosition()
{
	return TransData.LocalPosition;
}

float4 GameEngineTransform::GetLocalScale()
{
	return TransData.LocalScale;
}

float4 GameEngineTransform::GetLocalRotation()
{
	return TransData.LocalRotation;
}

float4 GameEngineTransform::GetWorldPosition()
{
	return TransData.WorldPosition;
}

float4 GameEngineTransform::GetWorldScale()
{
	return TransData.WorldScale;
}

float4 GameEngineTransform::GetWorldRotation()
{
	return TransData.WorldRotation;
}



void GameEngineTransform::AbsoluteReset()
{
	AbsoluteScale = false;
	AbsoluteRotation = false;
	AbsolutePosition = false;
}


void GameEngineTransform::AllAccTime(float _DeltaTime)
{
	if (nullptr == Master)
		return;

	if (false == Master->IsUpdate())
		return;

	Master->AccLiveTime(_DeltaTime);

	for (GameEngineTransform* Trans : Child)
	{
		Trans->AllAccTime(_DeltaTime);
	}
}

void GameEngineTransform::AllUpdate(float _DeltaTime)
{
	if (nullptr == Master)
		return;

	if (false == Master->IsUpdate())
		return;

	Master->Update(_DeltaTime);

	for (GameEngineTransform* Trans : Child)
	{
		Trans->AllUpdate(_DeltaTime);
	}
}

void GameEngineTransform::AllRender(float _DeltaTime)
{
	if (nullptr == Master)
		return;

	if (false == Master->IsUpdate())
		return;

	Master->Render(_DeltaTime);

	for (GameEngineTransform* Trans : Child)
	{
		Trans->AllRender(_DeltaTime);
	}
}

void GameEngineTransform::AllRelease()
{
	if (nullptr == Master)
		return;

	if (false == Master->IsUpdate())
		return;

	Master->Release();

	for (GameEngineTransform* Trans : Child)
	{
		Trans->AllRelease();
	}
}

void GameEngineTransform::ChildRelease() 
{
	std::list<GameEngineTransform*>::iterator ReleaseStartIter = Child.begin();
	std::list<GameEngineTransform*>::iterator ReleaseEndIter = Child.end();

	for (; ReleaseStartIter != ReleaseEndIter;)
	{
		GameEngineTransform* Trans = *ReleaseStartIter;

		if (nullptr == Trans->Master)
		{
			MsgAssert("Transform�� Master�� �������� ������ �����ϴ�.");
			return;
		}

		//�ڽĵ� �߿��� ���� ������ ������Ʈ�� �ƴ϶�� continue
		if (false == Trans->Master->IsDeath())
		{
			++ReleaseStartIter;
			continue;
		}

		//�ڽĵ� �߿��� ���� ������ ������Ʈ�� ��� ����Ʈ���� ����
		ReleaseStartIter = Child.erase(ReleaseStartIter);
	}
}