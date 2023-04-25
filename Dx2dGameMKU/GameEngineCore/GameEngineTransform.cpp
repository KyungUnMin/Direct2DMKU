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



//실제 Transform을 변경하는 순간 행렬 계산이 된다
//반대로 안 움직이면 계산 안된다
void GameEngineTransform::TransformUpdate()
{
	//크기행렬 만들기
	TransData.ScaleMatrix.Scale(TransData.Scale);

	//회전행렬 만들기
	TransData.Rotation.w = 0.f;

	//로테이션 -> 쿼터니언
	TransData.Quaternion = TransData.Rotation.EulerDegToQuaternion();
	//쿼터니언 -> 로테이션 행렬
	TransData.RotationMatrix = TransData.Quaternion.QuaternionToRotationMatrix();

	//이동행렬 만들기
	TransData.PositionMatrix.Pos(TransData.Position);

	//크자이 순으로 로컬 행렬 계산
	TransData.LocalWorldMatrix = TransData.ScaleMatrix * TransData.RotationMatrix * TransData.PositionMatrix;


	//부모가 없는 경우
	if (nullptr == Parent)
	{
		TransData.WorldMatrix = TransData.LocalWorldMatrix;
	}

	//부모가 있는 경우
	else
	{
		//부모의 월드 행렬을 각각 크자이로 분해한다
		float4x4 ParentWorldMatrix = Parent->GetWorldMatrixRef();
		float4 PScale, PRotation, PPosition;
		ParentWorldMatrix.Decompose(PScale, PRotation, PPosition);


		//근데 내가 월드 크기를 사용중이라면 부모의 크기는 무시
		if (true == AbsoluteScale)
		{
			PScale = float4::One;
		}

		//근데 내가 월드 회전를 사용중이라면 부모의 회전은 무시
		if (true == AbsoluteRotation)
		{
			PRotation = float4::Zero;
			//xyz 0의 쿼터니언 생성
			PRotation.EulerDegToQuaternion();
		}

		//근데 내가 월드 이동를 사용중이라면 부모의 이동은 무시
		if (true == AbsolutePosition)
		{
			PPosition = float4::Zero;
		}


		//위에서 만든 값을 바탕으로 행렬 만들기
		float4x4 MatScale, MatRot, MatPos;
		MatScale.Scale(PScale);
		MatRot = PRotation.QuaternionToRotationMatrix();
		MatPos.Pos(PScale);

		//자신의 월드 행렬 = 자신의 로컬행렬에 부모의 월드 행렬 곱하기
		TransData.WorldMatrix = TransData.LocalWorldMatrix * (MatScale * MatRot * MatPos);
	}

	//자신의 로컬 행렬에서 로컬 크자이 추출
	TransData.LocalWorldMatrix.Decompose(TransData.LocalScale, TransData.LocalQuaternion, TransData.LocalPosition);
	TransData.LocalRotation = TransData.LocalQuaternion.QuaternionToEulerDeg();

	//자신의 월드 행렬에서 월드 크자이 추출
	TransData.WorldMatrix.Decompose(TransData.WorldScale, TransData.WorldQuaternion, TransData.WorldPosition);
	TransData.WorldRotation = TransData.WorldQuaternion.QuaternionToEulerDeg();
}




void GameEngineTransform::SetParent(GameEngineTransform* _Parent)
{
	//부모 설정
	Parent = _Parent;

	//부모의 자식리스트에 자기 자신을 등록
	Parent->Child.push_back(this);

	TransformUpdate();
}


void GameEngineTransform::CalChild()
{
	//자식들 순회
	for (GameEngineTransform* ChildTrans : Child)
	{
		//자식의 크기가 나에게 종속적이라면
		if (false == ChildTrans->AbsoluteScale)
		{
			//자신(부모)이 바뀌였으니, 그에 따라 자식도 재 계산
			ChildTrans->SetLocalScale(ChildTrans->GetLocalScale());
		}

		//자식의 회전이 나에게 종속적이라면
		if (false == ChildTrans->AbsoluteRotation)
		{
			//자신(부모)이 바뀌였으니, 그에 따라 자식도 재 계산
			ChildTrans->SetLocalRotation(ChildTrans->GetLocalRotation());
		}

		//자식의 위치가 나에게 종속적이라면
		if (false == ChildTrans->AbsolutePosition)
		{
			//자신(부모)이 바뀌였으니, 그에 따라 자식도 재 계산
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