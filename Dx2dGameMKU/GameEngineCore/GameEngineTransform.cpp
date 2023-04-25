#include "PrecompileHeader.h"
#include "GameEngineTransform.h"
#include "GameEngineObject.h"

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
	TransData.Rotation.w = 0.f;

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
		//�θ��� ���� ����� ���� ũ���̷� �����Ѵ�
		float4x4 ParentWorldMatrix = Parent->GetWorldMatrixRef();
		float4 PScale, PRotation, PPosition;
		ParentWorldMatrix.Decompose(PScale, PRotation, PPosition);


		//�ٵ� ���� ���� ũ�⸦ ������̶�� �θ��� ũ��� ����
		if (true == AbsoluteScale)
		{
			PScale = float4::One;
		}

		//�ٵ� ���� ���� ȸ���� ������̶�� �θ��� ȸ���� ����
		if (true == AbsoluteRotation)
		{
			PRotation = float4::Zero;
			//xyz 0�� ���ʹϾ� ����
			PRotation.EulerDegToQuaternion();
		}

		//�ٵ� ���� ���� �̵��� ������̶�� �θ��� �̵��� ����
		if (true == AbsolutePosition)
		{
			PPosition = float4::Zero;
		}


		//������ ���� ���� �������� ��� �����
		float4x4 MatScale, MatRot, MatPos;
		MatScale.Scale(PScale);
		MatRot = PRotation.QuaternionToRotationMatrix();
		MatPos.Pos(PScale);

		//�ڽ��� ���� ��� = �ڽ��� ������Ŀ� �θ��� ���� ��� ���ϱ�
		TransData.WorldMatrix = TransData.LocalWorldMatrix * (MatScale * MatRot * MatPos);
	}

	//�ڽ��� ���� ��Ŀ��� ���� ũ���� ����
	TransData.LocalWorldMatrix.Decompose(TransData.LocalScale, TransData.LocalQuaternion, TransData.LocalPosition);
	TransData.LocalRotation = TransData.LocalQuaternion.QuaternionToEulerDeg();

	//�ڽ��� ���� ��Ŀ��� ���� ũ���� ����
	TransData.WorldMatrix.Decompose(TransData.WorldScale, TransData.WorldQuaternion, TransData.WorldPosition);
	TransData.WorldRotation = TransData.WorldQuaternion.QuaternionToEulerDeg();
}




void GameEngineTransform::SetParent(GameEngineTransform* _Parent)
{
	//�θ� ����
	Parent = _Parent;

	//�θ��� �ڽĸ���Ʈ�� �ڱ� �ڽ��� ���
	Parent->Child.push_back(this);

	TransformUpdate();
}


void GameEngineTransform::CalChild()
{
	//�ڽĵ� ��ȸ
	for (GameEngineTransform* ChildTrans : Child)
	{
		//�ڽ��� ũ�Ⱑ ������ �������̶��
		if (false == ChildTrans->AbsoluteScale)
		{
			//�ڽ�(�θ�)�� �ٲ����, �׿� ���� �ڽĵ� �� ���
			ChildTrans->SetLocalScale(ChildTrans->GetLocalScale());
		}

		//�ڽ��� ȸ���� ������ �������̶��
		if (false == ChildTrans->AbsoluteRotation)
		{
			//�ڽ�(�θ�)�� �ٲ����, �׿� ���� �ڽĵ� �� ���
			ChildTrans->SetLocalRotation(ChildTrans->GetLocalRotation());
		}

		//�ڽ��� ��ġ�� ������ �������̶��
		if (false == ChildTrans->AbsolutePosition)
		{
			//�ڽ�(�θ�)�� �ٲ����, �׿� ���� �ڽĵ� �� ���
			ChildTrans->SetLocalPosition(ChildTrans->GetLocalPosition());
		}
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