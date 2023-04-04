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

	LocalRotation.w = 0.f;

	//LocalRotationMatrix.RotationDeg(LocalRotation);
	LocalRotationMatrix.RotationDegToXYZ(LocalRotation);
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


void GameEngineTransform::SetParent(GameEngineTransform* _Parent)
{
	//�θ� ����
	Parent = _Parent;

	//�θ��� �ڽĸ���Ʈ�� �ڱ� �ڽ��� ���
	Parent->Child.push_back(this);
}

