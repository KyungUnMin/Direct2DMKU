#include "PrecompileHeader.h"
#include "GameEngineTransform.h"
#include "GameEngineObject.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"

//--------------------------Collision-------------------------

std::function<bool(const CollisionData&, const CollisionData&)> GameEngineTransform::ArrColFunction[static_cast<int>(ColType::MAX)][static_cast<int>(ColType::MAX)];

class InitColFunction
{
public:
	InitColFunction()
	{
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::SPHERE3D)][static_cast<int>(ColType::SPHERE3D)] = &GameEngineTransform::SphereToSpehre;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::SPHERE3D)][static_cast<int>(ColType::AABBBOX3D)] = &GameEngineTransform::SphereToAABB;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::SPHERE3D)][static_cast<int>(ColType::OBBBOX3D)] = &GameEngineTransform::SphereToOBB;

		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::AABBBOX3D)][static_cast<int>(ColType::SPHERE3D)] = &GameEngineTransform::AABBToSpehre;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::AABBBOX3D)][static_cast<int>(ColType::AABBBOX3D)] = &GameEngineTransform::AABBToAABB;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::AABBBOX3D)][static_cast<int>(ColType::OBBBOX3D)] = &GameEngineTransform::AABBToOBB;

		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::OBBBOX3D)][static_cast<int>(ColType::SPHERE3D)] = &GameEngineTransform::OBBToSpehre;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::OBBBOX3D)][static_cast<int>(ColType::AABBBOX3D)] = &GameEngineTransform::OBBToAABB;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::OBBBOX3D)][static_cast<int>(ColType::OBBBOX3D)] = &GameEngineTransform::OBBToOBB;

		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::SPHERE2D)][static_cast<int>(ColType::SPHERE2D)] = &GameEngineTransform::Sphere2DToSpehre2D;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::SPHERE2D)][static_cast<int>(ColType::AABBBOX2D)] = &GameEngineTransform::Sphere2DToAABB2D;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::SPHERE2D)][static_cast<int>(ColType::OBBBOX2D)] = &GameEngineTransform::Sphere2DToOBB2D;

		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::AABBBOX2D)][static_cast<int>(ColType::SPHERE2D)] = &GameEngineTransform::AABB2DToSpehre2D;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::AABBBOX2D)][static_cast<int>(ColType::AABBBOX2D)] = &GameEngineTransform::AABB2DToAABB2D;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::AABBBOX2D)][static_cast<int>(ColType::OBBBOX2D)] = &GameEngineTransform::AABB2DToOBB2D;

		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::OBBBOX2D)][static_cast<int>(ColType::SPHERE2D)] = &GameEngineTransform::OBB2DToSpehre2D;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::OBBBOX2D)][static_cast<int>(ColType::AABBBOX2D)] = &GameEngineTransform::OBB2DToAABB2D;
		GameEngineTransform::ArrColFunction[static_cast<int>(ColType::OBBBOX2D)][static_cast<int>(ColType::OBBBOX2D)] = &GameEngineTransform::OBB2DToOBB2D;

	}
};

InitColFunction InitFunction;

bool GameEngineTransform::SphereToSpehre(const CollisionData& _Left, const CollisionData& _Right)
{
	return _Left.SPHERE.Intersects(_Right.SPHERE);
}

bool GameEngineTransform::SphereToAABB(const CollisionData& _Left, const CollisionData& _Right)
{
	return _Left.SPHERE.Intersects(_Right.AABB);
}

bool GameEngineTransform::SphereToOBB(const CollisionData& _Left, const CollisionData& _Right)
{
	return _Left.SPHERE.Intersects(_Right.OBB);
}

bool GameEngineTransform::AABBToSpehre(const CollisionData& _Left, const CollisionData& _Right)
{
	return _Left.AABB.Intersects(_Right.SPHERE);
}

bool GameEngineTransform::AABBToAABB(const CollisionData& _Left, const CollisionData& _Right)
{
	return _Left.AABB.Intersects(_Right.AABB);
}

bool GameEngineTransform::AABBToOBB(const CollisionData& _Left, const CollisionData& _Right)
{
	return _Left.AABB.Intersects(_Right.OBB);
}

bool GameEngineTransform::OBBToSpehre(const CollisionData& _Left, const CollisionData& _Right)
{
	return _Left.OBB.Intersects(_Right.SPHERE);
}

bool GameEngineTransform::OBBToAABB(const CollisionData& _Left, const CollisionData& _Right)
{
	return _Left.OBB.Intersects(_Right.AABB);
}

bool GameEngineTransform::OBBToOBB(const CollisionData& _Left, const CollisionData& _Right)
{
	return _Left.OBB.Intersects(_Right.OBB);
}



bool GameEngineTransform::Sphere2DToSpehre2D(const CollisionData& _Left, const CollisionData& _Right)
{
	CollisionData LeftData = _Left;
	LeftData.OBB.Center.z = 0.0f;
	CollisionData RightData = _Right;
	RightData.OBB.Center.z = 0.0f;

	return LeftData.SPHERE.Intersects(RightData.SPHERE);
}

bool GameEngineTransform::Sphere2DToAABB2D(const CollisionData& _Left, const CollisionData& _Right)
{
	CollisionData LeftData = _Left;
	LeftData.OBB.Center.z = 0.0f;
	CollisionData RightData = _Right;
	RightData.OBB.Center.z = 0.0f;

	return LeftData.SPHERE.Intersects(RightData.AABB);
}

bool GameEngineTransform::Sphere2DToOBB2D(const CollisionData& _Left, const CollisionData& _Right)
{
	CollisionData LeftData = _Left;
	LeftData.OBB.Center.z = 0.0f;
	CollisionData RightData = _Right;
	RightData.OBB.Center.z = 0.0f;

	return LeftData.SPHERE.Intersects(RightData.OBB);
}

bool GameEngineTransform::AABB2DToSpehre2D(const CollisionData& _Left, const CollisionData& _Right)
{
	CollisionData LeftData = _Left;
	LeftData.OBB.Center.z = 0.0f;
	CollisionData RightData = _Right;
	RightData.OBB.Center.z = 0.0f;

	return LeftData.AABB.Intersects(RightData.SPHERE);
}

bool GameEngineTransform::AABB2DToAABB2D(const CollisionData& _Left, const CollisionData& _Right)
{
	CollisionData LeftData = _Left;
	LeftData.OBB.Center.z = 0.0f;
	CollisionData RightData = _Right;
	RightData.OBB.Center.z = 0.0f;

	return LeftData.AABB.Intersects(RightData.AABB);
}

bool GameEngineTransform::AABB2DToOBB2D(const CollisionData& _Left, const CollisionData& _Right)
{
	CollisionData LeftData = _Left;
	LeftData.OBB.Center.z = 0.0f;
	CollisionData RightData = _Right;
	RightData.OBB.Center.z = 0.0f;

	return LeftData.AABB.Intersects(RightData.OBB);
}

bool GameEngineTransform::OBB2DToSpehre2D(const CollisionData& _Left, const CollisionData& _Right)
{
	CollisionData LeftData = _Left;
	LeftData.OBB.Center.z = 0.0f;
	CollisionData RightData = _Right;
	RightData.OBB.Center.z = 0.0f;

	return LeftData.OBB.Intersects(RightData.SPHERE);
}

bool GameEngineTransform::OBB2DToAABB2D(const CollisionData& _Left, const CollisionData& _Right)
{
	CollisionData LeftData = _Left;
	LeftData.OBB.Center.z = 0.0f;
	CollisionData RightData = _Right;
	RightData.OBB.Center.z = 0.0f;

	return LeftData.OBB.Intersects(RightData.AABB);
}

bool GameEngineTransform::OBB2DToOBB2D(const CollisionData& _Left, const CollisionData& _Right)
{
	CollisionData LeftData = _Left;
	LeftData.OBB.Center.z = 0.0f;
	CollisionData RightData = _Right;
	RightData.OBB.Center.z = 0.0f;

	return LeftData.OBB.Intersects(RightData.OBB);
}




//--------------------------TransData-------------------------


void TransformData::LocalCalculation()
{
	//크기행렬 만들기
	ScaleMatrix.Scale(Scale);


	//회전행렬 만들기
	Rotation.w = 0.0f;
	//로테이션 -> 쿼터니언
	Quaternion = Rotation.EulerDegToQuaternion();
	//쿼터니언 -> 로테이션 행렬
	RotationMatrix = Quaternion.QuaternionToRotationMatrix();


	//이동행렬 만들기
	PositionMatrix.Pos(Position);


	//크자이 순으로 로컬 행렬 계산
	LocalWorldMatrix = ScaleMatrix * RotationMatrix * PositionMatrix;
}


void TransformData::WorldCalculation(const float4x4& _Parent, bool AbsoluteScale, bool AbsoluteRotation, bool AbsolutePosition)
{
	//부모의 월드 행렬을 각각 크자이로 분해한다
	float4 PScale, PRotation, PPosition;
	_Parent.Decompose(PScale, PRotation, PPosition);


	//근데 내가 월드 크기를 사용중이라면 부모의 크기는 무시
	if (true == AbsoluteScale)
	{
		PScale = float4::One;
	}

	//근데 내가 월드 회전를 사용중이라면 부모의 회전은 무시
	if (true == AbsoluteRotation)
	{
		// 부모의 회전 
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
	MatPos.Pos(PPosition);


	//자신의 월드 행렬 = 자신의 로컬행렬에 부모의 월드 행렬 곱하기
	WorldMatrix = LocalWorldMatrix * (MatScale * MatRot * MatPos);
}

void TransformData::SetViewAndProjection(const float4x4& _View, const float4x4& _Projection)
{
	//뷰행렬을 이용해 카메라의 행렬에 따라
		// 모든 물체들을 이동 및 공전시키고
		//투영 행렬을 이용해 3차원 물체를 2차원에 투영시킴
		//이때 뷰포트 변환시 해상도 적용을 편하게 하기 위해
		//-1 ~ 1사이 값으로 만드는 정규화 작업이 들어간다

	View = _View;
	Projection = _Projection;
	WorldViewProjectionMatrix = WorldMatrix * View * Projection;
}

//실제 Transform을 변경하는 순간 행렬 계산이 된다
//반대로 안 움직이면 계산 안된다
void GameEngineTransform::TransformUpdate()
{
	//로컬 행렬 계산
	TransData.LocalCalculation();


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


//--------------------------Transform-------------------------


GameEngineTransform::GameEngineTransform()
{
	TransformUpdate();
}

GameEngineTransform::~GameEngineTransform()
{
}



void GameEngineTransform::WorldCalculation()
{
	//부모의 행렬
	float4x4 ParentWorldMatrix = Parent->GetWorldMatrixRef();
	TransData.WorldCalculation(ParentWorldMatrix, AbsoluteScale, AbsoluteRotation, AbsolutePosition);
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

	//충돌을 위한 값 세팅
	ColData.OBB.Center = TransData.WorldPosition.DirectFloat3;
	ColData.OBB.Extents = (TransData.WorldScale * 0.5f).DirectFloat3;
	ColData.OBB.Orientation = TransData.WorldQuaternion.DirectFloat4;
	ColData.ScaleABS();
}




void GameEngineTransform::SetParent(GameEngineTransform* _Parent, bool _IsParentWorld /*= true*/)
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
		//부모의 월드좌표를 따를 때만
		if (true == _IsParentWorld)
		{
			//자식의 로컬 행렬에 부모의 월드 행렬의 역행렬을 곱한다
			TransData.LocalWorldMatrix = TransData.WorldMatrix * Parent->TransData.LocalWorldMatrix.InverseReturn();
		}
		
		//로컬 행렬로부터 크자이 추출
		LocalDecompose();

		//TransformUpdate를 위해 값 대입
		TransData.Position = TransData.LocalPosition;
		TransData.Rotation = TransData.LocalRotation;
		TransData.Scale = TransData.LocalScale;

		//실제 위치 계산
		TransformUpdate();

		AbsoluteReset();


		//기존의 레벨 그룹에서 자기자신을 제거
		GameEngineLevel* Level = Master->GetLevel();
		//Ref 유지하기 위해 여기서 받아놓는다
		std::shared_ptr<GameEngineObject> MasterPtr = Master->shared_from_this();
		//엑터인 경우에만 레벨 리스트에서 제거
		if (nullptr != dynamic_cast<GameEngineActor*>(Master))
		{
			Level->Actors[MasterPtr->GetOrder()].remove(std::dynamic_pointer_cast<GameEngineActor>(MasterPtr));
		}

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

float4 GameEngineTransform::GetLocalQuaternion()
{
	return TransData.LocalQuaternion;
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

float4 GameEngineTransform::GetWorldQuaternion()
{
	return TransData.WorldQuaternion;
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


bool GameEngineTransform::Collision(const CollisionParameter& Data)
{
	if (nullptr == Data._OtherTrans)
	{
		MsgAssert("nullptr인 트랜스 폼과는 충돌을 할수가 없습니다.");
	}

	return ArrColFunction[static_cast<int>(Data.ThisType)][static_cast<int>(Data.OtherType)](this->GetCollisionData(), Data._OtherTrans->GetCollisionData());
}