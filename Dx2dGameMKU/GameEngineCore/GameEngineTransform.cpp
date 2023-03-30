#include "GameEngineTransform.h"

GameEngineTransform::GameEngineTransform()
{

}

GameEngineTransform::~GameEngineTransform()
{

}

void GameEngineTransform::TransformUpdate()
{
	//실제 Transform을 변경하는 순간 행렬 계산이 된다
	//반대로 안 움직이면 계산 안된다

	LocalScaleMatrix.Scale(LocalScale);
	LocalRotationMatrix.RotationDeg(LocalRotation);
	LocalPositionMatrix.Pos(LocalPosition);

	LocalWorldMatrix = LocalScaleMatrix * LocalRotationMatrix * LocalPositionMatrix;
	WorldMatrix = LocalWorldMatrix;
}