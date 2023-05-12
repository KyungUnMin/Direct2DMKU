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



//실제 Transform을 변경하는 순간 행렬 계산이 된다
//반대로 안 움직이면 계산 안된다
void GameEngineTransform::TransformUpdate()
{
	//크기행렬 만들기
	TransData.ScaleMatrix.Scale(TransData.Scale);

	//회전행렬 만들기
	TransData.Rotation.w = 0.0f;

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
		WorldCalculation();
	}


	//자신의 월드 행렬에서 월드 크자이 추출
	WorldDecompose();
	
	//자신의 로컬 행렬에서 로컬 크자이 추출
	LocalDecompose();
}


void GameEngineTransform::WorldCalculation()
{
	//부모의 월드 행렬을 각각 크자이로 분해한다
	float4x4 ParentWorldMatrix = Parent->GetWorldMatrixRef();
	float4 PScale, PRoatation, PPosition;
	ParentWorldMatrix.Decompose(PScale, PRoatation, PPosition);

	//근데 내가 월드 크기를 사용중이라면 부모의 크기는 무시
	if (true == AbsoluteScale)
	{
		PScale = float4::One;
	}

	//근데 내가 월드 회전를 사용중이라면 부모의 회전은 무시
	if (true == AbsoluteRotation)
	{
		PRoatation = float4::Zero;
		//xyz 0의 쿼터니언 생성
		PRoatation.EulerDegToQuaternion();
	}

	//근데 내가 월드 이동를 사용중이라면 부모의 이동은 무시
	if (true == AbsolutePosition)
	{
		PPosition = float4::Zero;
	}


	//위에서 만든 값을 바탕으로 행렬 만들기
	float4x4 MatScale, MatRot, MatPos;
	MatScale.Scale(PScale);
	MatRot = PRoatation.QuaternionToRotationMatrix();
	MatPos.Pos(PPosition);


	//자신의 월드 행렬 = 자신의 로컬행렬에 부모의 월드 행렬 곱하기
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
	//만약 자식을 분리시킬때 분리시키는 대상이 Component인지 검사
	if ((nullptr == Parent) && (nullptr == Master))
	{
		if (nullptr == dynamic_cast<GameEngineActor*>(Master))
		{
			MsgAssert("액터만이 루트 리스트에 추가될수 있습니다.");
			return;
		}
	}


	//이 객체가 이미 최상위 부모인데 최상위 부모로 옮기려는 행동
	if (nullptr == Parent && nullptr == _Parent)
		return;


	//기존에 부모를 가지고 있었다면
	if (nullptr != Parent)
	{
		//부모의 Transform 자식 그룹에서 자기자신을 제거
		Parent->Child.remove(this);
		
		//부모의 Object
		GameEngineObject* ParentMaster = Parent->Master;
		if (nullptr == ParentMaster)
		{
			MsgAssert("존재할수 없는 상황입니다 Master가 nullptr입니다");
			return;
		}

		//부모의 Object 자식 그룹에서 자신의 Object을 제거할 때
		//RefCount가 0이 되서 소멸될 수가 있다, 때문에 여기서 받아놓고 RefCount를 유지시킨다
		std::shared_ptr<GameEngineObject> MasterPtr = Master->shared_from_this();

		ParentMaster->Childs.remove(MasterPtr);
		Parent = nullptr;
	}


	//부모 설정
	Parent = _Parent;


	//부모가 생겼거나 바뀌였다면
	if (nullptr != Parent)
	{

		//자식의 로컬 행렬에 부모의 월드 행렬의 역행렬을 곱한다
		TransData.LocalWorldMatrix = TransData.WorldMatrix * Parent->TransData.LocalWorldMatrix.InverseReturn();
		//로컬 행렬로부터 크자이 추출
		LocalDecompose();

		//TransformUpdate를 위해 값 대입
		TransData.Position = TransData.LocalPosition;
		TransData.Rotation = TransData.LocalRotation;
		TransData.Scale = TransData.LocalScale;

		//실제 위치 계산
		TransformUpdate();

		AbsoluteReset();

		//부모의 Transform 자식리스트에 자기 자신을 등록
		Parent->Child.push_back(this);

		//부모의 Object 자식리스트에 자기 자신을 등록
		Parent->Master->Childs.push_back(Master->shared_from_this());
	}


	//부모가 사라졌다면
	else
	{
		//자신의 월드행렬를 바탕으로 크자이 값들 추출
		WorldDecompose();

		//TransformUpdate를 위해 값 대입
		TransData.Position = TransData.WorldPosition;
		TransData.Rotation = TransData.WorldRotation;
		TransData.Scale = TransData.WorldScale;

		//값 재계산
		TransformUpdate();
		AbsoluteReset();

		//기존에 있었던 레벨로 돌아간다
		GameEngineLevel* Level = Master->GetLevel();
		std::shared_ptr<GameEngineObject> MasterPtr = Master->shared_from_this();

		//이 객체가 엑터인 경우에만
		if (nullptr != dynamic_cast<GameEngineActor*>(Master))
		{
			Level->Actors[MasterPtr->GetOrder()].push_back(std::dynamic_pointer_cast<GameEngineActor>(MasterPtr));
		}
		else
		{
			MsgAssert("액터만이 레벨의 루트 오브젝트로 지정될 수 있습니다.");
		}
	}
	
}




void GameEngineTransform::CalChild()
{
	//자식들 순회
	for (GameEngineTransform* ChildTrans : Child)
	{
		////자식의 크기가 나에게 종속적이라면
		//if (false == ChildTrans->AbsoluteScale)
		//{
		//	//자신(부모)이 바뀌였으니, 그에 따라 자식도 재 계산
		//	ChildTrans->SetLocalScale(ChildTrans->GetLocalScale());
		//}
		////자식의 회전이 나에게 종속적이라면
		//if (false == ChildTrans->AbsoluteRotation)
		//{
		//	//자신(부모)이 바뀌였으니, 그에 따라 자식도 재 계산
		//	ChildTrans->SetLocalRotation(ChildTrans->GetLocalRotation());
		//}
		////자식의 위치가 나에게 종속적이라면
		//if (false == ChildTrans->AbsolutePosition)
		//{
		//	//자신(부모)이 바뀌였으니, 그에 따라 자식도 재 계산
		//	ChildTrans->SetLocalPosition(ChildTrans->GetLocalPosition());
		//}


		//내 행렬을 바탕으로 자식들의 월드 행렬을 계산한다
		ChildTrans->WorldCalculation();
		//월드 크자이 추출
		ChildTrans->WorldDecompose();
		//재귀
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
			MsgAssert("Transform의 Master가 존재하지 않을수 없습니다.");
			return;
		}

		//자식들 중에서 삭제 예정인 오브젝트가 아니라면 continue
		if (false == Trans->Master->IsDeath())
		{
			++ReleaseStartIter;
			continue;
		}

		//자식들 중에서 삭제 예정인 오브젝트인 경우 리스트에서 제외
		ReleaseStartIter = Child.erase(ReleaseStartIter);
	}
}