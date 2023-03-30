#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform()
{

}

GameEngineTransform::~GameEngineTransform()
{

}

void GameEngineTransform::TransformUpdate()
{
	//���� Transform�� �����ϴ� ���� ��� ����� �ȴ�
	//�ݴ�� �� �����̸� ��� �ȵȴ�

	LocalScaleMatrix.Scale(LocalScale);
	LocalRotationMatrix.RotationDeg(LocalRotation);
	LocalPositionMatrix.Pos(LocalPosition);

	LocalWorldMatrix = LocalScaleMatrix * LocalRotationMatrix * LocalPositionMatrix;
	WorldMatrix = LocalWorldMatrix;
}