#include "GameEngineTransform.h"
#include "GameEngineObject.h"

GameEngineTransform::GameEngineTransform()
{

}

GameEngineTransform::~GameEngineTransform()
{

}


//���� Transform�� �����ϴ� ���� ��� ����� �ȴ�
//�ݴ�� �� �����̸� ��� �ȵȴ�
void GameEngineTransform::TransformUpdate()
{
	LocalScaleMatrix.Scale(LocalScale);
	LocalRotationMatrix.RotationDeg(LocalRotation);
	LocalPositionMatrix.Pos(LocalPosition);

	//ũ���� ������ ���� ��� ���
	LocalWorldMatrix = LocalScaleMatrix * LocalRotationMatrix * LocalPositionMatrix;

	//�θ� ���� ���
	if (nullptr == Parent)
	{
		WorldMatrix = LocalWorldMatrix;
	}

	//�θ� �ִ� ��쿣 �θ� ��ġ�� ������� ������ World��ǥ�� ����ȴ�
	else
	{
		WorldMatrix = LocalWorldMatrix * Parent->GetWorldMatrixRef();
	}
}