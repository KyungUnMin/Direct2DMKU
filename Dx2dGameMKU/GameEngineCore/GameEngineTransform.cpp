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
	Quaternion = Rotation.EulerDegToQuaternion();
	LocalWorldMatrix.Compose(Scale, Quaternion, Position);
}


void TransformData::WorldCalculation(const TransformData& _Parent, bool AbsoluteScale, bool AbsoluteRotation, bool AbsolutePosition)
{
	//�ϴ� �θ��� ���� ����� ���� �ڽ��� ���� ��� �����
	const float4x4& ParentMatrix = _Parent.WorldMatrix;
	WorldMatrix = WorldMatrix * ParentMatrix;

	//�ϳ��� ����� �������� ���
	if (true == AbsoluteScale || true == AbsoluteRotation || true == AbsolutePosition)
	{
		float4 WScale, WRotation, WPosition;
		float4 LScale, LRotation, LPosition;

		//�ڽ��� ���� ��Ŀ��� ũ���̸� ����
		WorldMatrix.Decompose(WScale, WRotation, WPosition);



		//---------ũ��---------------

		LScale = Scale;

		//ũ�⸦ ����� ������ �� ���
		if (true == AbsoluteScale)
		{
			WScale = Scale;
			//������ �θ��� ���� �������� ���Ѵ�(����� �������ְ� GetLocalScale�� ��� �� �ֱ� ������ ���⼭ ����)
			LScale *= float4::GetSafeScaleReciprocal(_Parent.WorldScale, 0.00001f);
		}
		



		//---------ȸ��---------------

		//ȸ������ -> ���ʹϾ�
		Quaternion = Rotation.EulerDegToQuaternion();

		//ȸ���� ����� �������� ���
		if (true == AbsoluteRotation)
		{
			//���ʹϿ���(���� �ƴ�)
			WRotation = Rotation.EulerDegToQuaternion();
			//�ڽ��� ���ʹϾ�� �θ��� ���ʹϾ��� ���� ���ؼ� �θ� ���� �ޱ� �� ���ʹϾ��� �����
			Quaternion = DirectX::XMQuaternionMultiply(Quaternion, DirectX::XMQuaternionInverse(_Parent.WorldQuaternion));
		}



		//---------�̵�---------------

		LPosition = Position;

		//�̵��� ����� ������ ���
		if (true == AbsolutePosition)
		{
			//���� �������� ������ ���������� ����
			WPosition = Position;

			//�θ��� ���� ����İ� ��������ġ�� ���ؼ� ������ġ�� ���Ѵ�
			float4x4 InverseMat = _Parent.WorldMatrix.InverseReturn();
			LPosition *= InverseMat;
		}

		// ���� ����
		float4x4 MatScale, MatRot, MatPos;
		WorldMatrix.Compose(WScale, WRotation, WPosition);

		// ���� ����
		ScaleMatrix.Scale(LScale);
		RotationMatrix = Quaternion.QuaternionToRotationMatrix();
		PositionMatrix.Pos(LPosition);

		LocalWorldMatrix.Compose(LScale, Quaternion, LPosition);
	}

}

void TransformData::SetViewAndProjection(const float4x4& _View, const float4x4& _Projection)
{
	//������� �̿��� ī�޶��� ��Ŀ� ����
		// ��� ��ü���� �̵� �� ������Ű��
		//���� ����� �̿��� 3���� ��ü�� 2������ ������Ŵ
		//�̶� ����Ʈ ��ȯ�� �ػ� ������ ���ϰ� �ϱ� ����
		//-1 ~ 1���� ������ ����� ����ȭ �۾��� ����

	View = _View;
	Projection = _Projection;
	WorldViewProjectionMatrix = WorldMatrix * View * Projection;
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
	//�θ��� ���
	float4x4 ParentWorldMatrix = Parent->GetWorldMatrixRef();
	TransData.WorldCalculation(Parent->TransData, AbsoluteScale, AbsoluteRotation, AbsolutePosition);
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

	//�浹�� ���� �� ����
	ColData.OBB.Center = TransData.WorldPosition.DirectFloat3;
	ColData.OBB.Extents = (TransData.WorldScale * 0.5f).DirectFloat3;
	ColData.OBB.Orientation = TransData.WorldQuaternion.DirectFloat4;
	ColData.ScaleABS();
}




void GameEngineTransform::SetParent(GameEngineTransform* _Parent, bool _IsParentWorld /*= true*/)
{
	//���� �ڽ��� �и���ų�� �и���Ű�� ����� Component���� �˻�
	if ((nullptr == Parent) && (nullptr == Master))
	{
		if (nullptr == dynamic_cast<GameEngineActor*>(Master))
		{
			MsgAssert("���͸��� ��Ʈ ����Ʈ�� �߰��ɼ� �ֽ��ϴ�.");
			return;
		}
	}


	//�� ��ü�� �̹� �ֻ��� �θ��ε� �ֻ��� �θ�� �ű���� �ൿ
	if (nullptr == Parent && nullptr == _Parent)
		return;


	//������ �θ� ������ �־��ٸ�
	if (nullptr != Parent)
	{
		//�θ��� Transform �ڽ� �׷쿡�� �ڱ��ڽ��� ����
		Parent->Child.remove(this);
		
		//�θ��� Object
		GameEngineObject* ParentMaster = Parent->Master;
		if (nullptr == ParentMaster)
		{
			MsgAssert("�����Ҽ� ���� ��Ȳ�Դϴ� Master�� nullptr�Դϴ�");
			return;
		}

		//�θ��� Object �ڽ� �׷쿡�� �ڽ��� Object�� ������ ��
		//RefCount�� 0�� �Ǽ� �Ҹ�� ���� �ִ�, ������ ���⼭ �޾Ƴ��� RefCount�� ������Ų��
		std::shared_ptr<GameEngineObject> MasterPtr = Master->shared_from_this();

		ParentMaster->Childs.remove(MasterPtr);
		Parent = nullptr;
	}


	//�θ� ����
	Parent = _Parent;


	//�θ� ����ų� �ٲ�ٸ�
	if (nullptr != Parent)
	{
		//�θ��� ������ǥ�� ���� ����
		if (true == _IsParentWorld)
		{
			//�ڽ��� ���� ��Ŀ� �θ��� ���� ����� ������� ���Ѵ�
			TransData.LocalWorldMatrix = TransData.WorldMatrix * Parent->TransData.LocalWorldMatrix.InverseReturn();
		}
		
		//���� ��ķκ��� ũ���� ����
		LocalDecompose();

		//TransformUpdate�� ���� �� ����
		TransData.Position = TransData.LocalPosition;
		TransData.Rotation = TransData.LocalRotation;
		TransData.Scale = TransData.LocalScale;

		//���� ��ġ ���
		TransformUpdate();

		AbsoluteReset();


		//������ ���� �׷쿡�� �ڱ��ڽ��� ����
		GameEngineLevel* Level = Master->GetLevel();
		//Ref �����ϱ� ���� ���⼭ �޾Ƴ��´�
		std::shared_ptr<GameEngineObject> MasterPtr = Master->shared_from_this();
		//������ ��쿡�� ���� ����Ʈ���� ����
		if (nullptr != dynamic_cast<GameEngineActor*>(Master))
		{
			Level->Actors[MasterPtr->GetOrder()].remove(std::dynamic_pointer_cast<GameEngineActor>(MasterPtr));
		}

		//�θ��� Transform �ڽĸ���Ʈ�� �ڱ� �ڽ��� ���
		Parent->Child.push_back(this);

		//�θ��� Object �ڽĸ���Ʈ�� �ڱ� �ڽ��� ���
		Parent->Master->Childs.push_back(Master->shared_from_this());
	}


	//�θ� ������ٸ�
	else
	{
		//�ڽ��� ������ĸ� �������� ũ���� ���� ����
		WorldDecompose();

		//TransformUpdate�� ���� �� ����
		TransData.Position = TransData.WorldPosition;
		TransData.Rotation = TransData.WorldRotation;
		TransData.Scale = TransData.WorldScale;

		//�� ����
		TransformUpdate();
		AbsoluteReset();

		//������ �־��� ������ ���ư���
		GameEngineLevel* Level = Master->GetLevel();
		std::shared_ptr<GameEngineObject> MasterPtr = Master->shared_from_this();

		//�� ��ü�� ������ ��쿡��
		if (nullptr != dynamic_cast<GameEngineActor*>(Master))
		{
			Level->Actors[MasterPtr->GetOrder()].push_back(std::dynamic_pointer_cast<GameEngineActor>(MasterPtr));
		}
		else
		{
			MsgAssert("���͸��� ������ ��Ʈ ������Ʈ�� ������ �� �ֽ��ϴ�.");
		}
	}
	
}




void GameEngineTransform::CalChild()
{
	//�ڽĵ� ��ȸ
	for (GameEngineTransform* ChildTrans : Child)
	{
		ChildTrans->TransformUpdate();
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
			MsgAssert("Transform�� Master�� �������� ������ �����ϴ�.");
			return;
		}

		//�ڽĵ� �߿��� ���� ������ ������Ʈ�� �ƴ϶�� continue
		if (false == Trans->Master->IsDeath())
		{
			++ReleaseStartIter;
			continue;
		}

		//�ڽĵ� �߿��� ���� ������ ������Ʈ�� ��� ����Ʈ���� ����
		ReleaseStartIter = Child.erase(ReleaseStartIter);
	}
}


bool GameEngineTransform::Collision(const CollisionParameter& Data)
{
	if (nullptr == Data._OtherTrans)
	{
		MsgAssert("nullptr�� Ʈ���� ������ �浹�� �Ҽ��� �����ϴ�.");
	}

	return ArrColFunction[static_cast<int>(Data.ThisType)][static_cast<int>(Data.OtherType)](this->GetCollisionData(), Data._OtherTrans->GetCollisionData());
}



//���� Transform�� �����ϴ� ���� ��� ����� �ȴ�
//�ݴ�� �� �����̸� ��� �ȵȴ�
void GameEngineTransform::TransformUpdate()
{
	//���� ��� ���
	TransData.LocalCalculation();
	TransData.WorldMatrix = TransData.LocalWorldMatrix;


	//�θ� �ִ� ���
	if (nullptr != Parent)
	{
		WorldCalculation();
	}


	//�ڽ��� ���� ��Ŀ��� ���� ũ���� ����
	WorldDecompose();

	//�ڽ��� ���� ��Ŀ��� ���� ũ���� ����
	LocalDecompose();
}
