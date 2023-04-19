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
	//ũ��
	TransData.LocalScaleMatrix.Scale(TransData.LocalScale);

	//ȸ��
	TransData.LocalRotation.w = 0.f;

	//���� �����̼� -> �������ʹϾ�
	TransData.LocalQuaternion = TransData.LocalRotation.EulerDegToQuaternion();
	//���� ���ʹϾ� -> �����̼� �������
	TransData.LocalRotationMatrix = TransData.LocalQuaternion.QuaternionToRotationMatrix();

	//�̵�
	TransData.LocalPositionMatrix.Pos(TransData.LocalPosition);

	//ũ���� ������ ���� ��� ���
	TransData.LocalWorldMatrix = TransData.LocalScaleMatrix * TransData.LocalRotationMatrix * TransData.LocalPositionMatrix;

	//�θ� ���� ���
	if (nullptr == Parent)
	{
		TransData.WorldMatrix = TransData.LocalWorldMatrix;
	}

	//�θ� �ִ� ��쿣 �θ� ��ġ�� ������� ������ World��ǥ�� ����ȴ�
	else
	{
		TransData.WorldMatrix = TransData.LocalWorldMatrix * Parent->GetWorldMatrixRef();
	}
}


void GameEngineTransform::SetParent(GameEngineTransform* _Parent)
{
	//�θ� ����
	Parent = _Parent;

	//�θ��� �ڽĸ���Ʈ�� �ڱ� �ڽ��� ���
	Parent->Child.push_back(this);

	TransformUpdate();
}

