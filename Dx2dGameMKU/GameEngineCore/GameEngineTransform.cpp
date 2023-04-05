#include "GameEngineTransform.h"
#include "GameEngineObject.h"

GameEngineTransform::GameEngineTransform()
{

}

GameEngineTransform::~GameEngineTransform()
{

}



//실제 Transform을 변경하는 순간 행렬 계산이 된다
//반대로 안 움직이면 계산 안된다
void GameEngineTransform::TransformUpdate()
{
	//크기
	LocalScaleMatrix.Scale(LocalScale);

	//회전
	LocalRotation.w = 0.f;

	//로컬 로테이션 -> 로컬쿼터니언
	LocalQuaternion = LocalRotation.EulerDegToQuaternion();
	//로컬 쿼터니언 -> 로테이션 로컬행렬
	LocalRotationMatrix = LocalQuaternion.QuaternionToRotationMatrix();

	//이동
	LocalPositionMatrix.Pos(LocalPosition);

	//크자이 순으로 로컬 행렬 계산
	LocalWorldMatrix = LocalScaleMatrix * LocalRotationMatrix * LocalPositionMatrix;

	//부모가 없는 경우
	if (nullptr == Parent)
	{
		WorldMatrix = LocalWorldMatrix;
	}

	//부모가 있는 경우엔 부모 위치에 상대적인 값으로 World좌표가 변경된다
	else
	{
		WorldMatrix = LocalWorldMatrix * Parent->GetWorldMatrixRef();
	}
}


void GameEngineTransform::SetParent(GameEngineTransform* _Parent)
{
	//부모 설정
	Parent = _Parent;

	//부모의 자식리스트에 자기 자신을 등록
	Parent->Child.push_back(this);
}

