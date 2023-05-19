#pragma once
#include <list>
#include <memory>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"


//-----------------Collision--------------

enum class ColType
{
	POINT2D, 
	SPHERE2D,
	AABBBOX2D,
	OBBBOX2D,

	POINT3D,
	SPHERE3D,
	AABBBOX3D,
	OBBBOX3D,

	MAX,
};


class CollisionData
{
public:
	union
	{
		DirectX::BoundingSphere SPHERE;
		DirectX::BoundingBox AABB;
		DirectX::BoundingOrientedBox OBB;
	};

	void ScaleABS()
	{
		OBB.Extents.x = abs(OBB.Extents.x);
		OBB.Extents.y = abs(OBB.Extents.y);
		OBB.Extents.z = abs(OBB.Extents.z);
	}

	CollisionData()
	{

	}
};


class CollisionParameter
{
public:
	class GameEngineTransform* _OtherTrans = nullptr;
	ColType ThisType = ColType::SPHERE3D;
	ColType OtherType = ColType::SPHERE3D;
};




//-----------------Transform--------------

struct TransformData
{
	// ����
	float4 Scale;
	float4 Rotation;
	float4 Quaternion;
	float4 Position;

	//���� (Get �Լ���)
	float4 LocalScale;
	float4 LocalRotation;
	float4 LocalQuaternion;
	float4 LocalPosition;

	//���� (Get �Լ���)
	float4 WorldScale;
	float4 WorldRotation;
	float4 WorldQuaternion;
	float4 WorldPosition;

	//���� ũ���� ���
	float4x4 ScaleMatrix;
	float4x4 RotationMatrix;
	float4x4 PositionMatrix;

	//�������(ũ����)
	float4x4 LocalWorldMatrix;

	//�������(ũ����)
	float4x4 WorldMatrix;

	//�����
	float4x4 View;

	//�������
	float4x4 Projection;

	//����Ʈ ���
	float4x4 ViewPort;

	//ī�޶�� ����ɶ� ����ϴ� ����*��*��������*����Ʈ���
	float4x4 WorldViewProjectionMatrix;

public:
	TransformData()
	{
		Scale = float4::One;
		Rotation = float4::Null;
		Quaternion = float4::Null;
		Position = float4::Zero;
	}
};


class GameEngineObject;
class GameEngineTransform : public GameEngineObjectBase
{
	friend class GameEngineObject;
	friend class GameEngineLevel;

public:
	GameEngineTransform();
	~GameEngineTransform() override;

	GameEngineTransform(const GameEngineTransform& _Other) = delete;
	GameEngineTransform(GameEngineTransform&& _Other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _Other) = delete;
	GameEngineTransform& operator=(GameEngineTransform&& _Other) noexcept = delete;

	void SetLocalPositiveScaleX()
	{
		TransData.Scale.x = abs(TransData.Scale.x);
		SetLocalScale(TransData.Scale);
	}

	void SetLocalNegativeScaleX()
	{
		TransData.Scale.x = -abs(TransData.Scale.x);
		SetLocalScale(TransData.Scale);
	}

	void SetWorldScale(const float4& _Value)
	{
		AbsoluteScale = true;
		TransData.Scale = _Value;

		//���� ��������Ƿ� ���� �������, ���� ��������� �ٽ� ���
		TransformUpdate();
		//�ڽ��� �ִٸ� �ڽĵ��� ����/��������� ����
		CalChild();
	}


	void SetWorldRotation(const float4& _Value)
	{
		AbsoluteRotation = true;
		TransData.Rotation = _Value;

		//���� ��������Ƿ� ���� �������, ���� ��������� �ٽ� ���
		TransformUpdate();
		//�ڽ��� �ִٸ� �ڽĵ��� ����/��������� ����
		CalChild();
	}


	void SetWorldPosition(const float4& _Value)
	{
		AbsolutePosition = true;
		TransData.Position = _Value;

		//���� ��������Ƿ� ���� �������, ���� ��������� �ٽ� ���
		TransformUpdate();
		//�ڽ��� �ִٸ� �ڽĵ��� ����/��������� ����
		CalChild();
	}


	void SetLocalScale(const float4& _Value)
	{
		AbsoluteScale = false;
		TransData.Scale = _Value;

		//���� ��������Ƿ� ���� �������, ���� ��������� �ٽ� ���
		TransformUpdate();
		//�ڽ��� �ִٸ� �ڽĵ��� ����/��������� ����
		CalChild();
	}


	void SetLocalRotation(const float4& _Value)
	{
		AbsoluteRotation = false;
		TransData.Rotation = _Value;

		//���� ��������Ƿ� ���� �������, ���� ��������� �ٽ� ���
		TransformUpdate();
		//�ڽ��� �ִٸ� �ڽĵ��� ����/��������� ����
		CalChild();
	}


	void SetLocalPosition(const float4& _Value)
	{
		AbsolutePosition = false;
		TransData.Position = _Value;

		//���� ��������Ƿ� ���� �������, ���� ��������� �ٽ� ���
		TransformUpdate();
		//�ڽ��� �ִٸ� �ڽĵ��� ����/��������� ����
		CalChild();
	}



	void AddLocalScale(const float4& _Value)
	{
		SetLocalScale(TransData.Scale + _Value);
	}

	void AddLocalRotation(const float4& _Value)
	{
		SetLocalRotation(TransData.Rotation + _Value);
	}

	void AddLocalPosition(const float4& _Value)
	{
		SetLocalPosition(TransData.Position + _Value);
	}

	void AddWorldScale(const float4& _Value)
	{
		SetWorldScale(TransData.Scale + _Value);
	}

	void AddWorldRotation(const float4& _Value)
	{
		SetWorldRotation(TransData.Rotation + _Value);
	}

	void AddWorldPosition(const float4& _Value)
	{
		SetWorldPosition(TransData.Position + _Value);
	}



	//���� ��ǥ���� +Z ��ȯ
	float4 GetWorldForwardVector()
	{
		return TransData.WorldMatrix.ArrVector[2].NormalizeReturn();
	}

	//���� ��ǥ���� +Y ��ȯ
	float4 GetWorldUpVector()
	{
		return TransData.WorldMatrix.ArrVector[1].NormalizeReturn();
	}

	//���� ��ǥ���� +X ��ȯ
	float4 GetWorldRightVector()
	{
		return TransData.WorldMatrix.ArrVector[0].NormalizeReturn();
	}

	float4 GetWorldBackVector()
	{
		return -GetWorldForwardVector();
	}

	float4 GetWorldDownVector()
	{
		return -GetWorldUpVector();
	}

	float4 GetWorldLeftVector()
	{
		return -GetWorldRightVector();
	}


	
	//���� ��ǥ���� +Z ��ȯ
	float4 GetLocalForwardVector()
	{
		//����� 2���� Return���ش�
		//Forward(Z��)�� ���� 2���� ������
		//����� ������ �Ͼ�� z�� ������� ����Ǵ��� �����ϸ� �� �� �ִ�.
		return TransData.LocalWorldMatrix.ArrVector[2].NormalizeReturn();
	}

	//���� ��ǥ���� +Y ��ȯ
	float4 GetLocalUpVector()
	{
		//����� 1���� Return���ش�
		//Up(Y��)�� ���� 1���� ������
		//����� ������ �Ͼ�� y�� ������� ����Ǵ��� �����ϸ� �� �� �ִ�.
		return TransData.LocalWorldMatrix.ArrVector[1].NormalizeReturn();
	}

	//���� ��ǥ���� +X ��ȯ
	float4 GetLocalRightVector()
	{
		//����� 0���� Return���ش�
		//Right(x��)�� ���� 0���� ������
		//����� ������ �Ͼ�� x�� ������� ����Ǵ��� �����ϸ� �� �� �ִ�.
		return TransData.LocalWorldMatrix.ArrVector[0].NormalizeReturn();
	}

	

	float4 GetLocalPosition();
	float4 GetLocalScale();
	float4 GetLocalRotation();
	float4 GetLocalQuaternion();
	float4 GetWorldPosition();
	float4 GetWorldScale();
	float4 GetWorldRotation();
	float4 GetWorldQuaternion();


	float4x4 GetLocalWorldMatrix()
	{
		return TransData.LocalWorldMatrix;
	}

	const float4x4& GetLocalWorldMatrixRef()
	{
		return TransData.LocalWorldMatrix;
	}

	const float4x4 GetWorldMatrix()
	{
		return TransData.WorldMatrix;
	}

	const float4x4& GetWorldMatrixRef()
	{
		return TransData.WorldMatrix;
	}

	const float4x4 GetWorldViewProjectionMatrix()
	{
		return TransData.WorldViewProjectionMatrix;
	}

	const float4x4& GetWorldViewProjectionMatrixRef()
	{
		return TransData.WorldViewProjectionMatrix;
	}

	//����İ� ��������� ���� ����
	inline const void SetCameraMatrix(const float4x4& _View, const float4x4& _Projection)
	{
		//������� �̿��� ī�޶��� ��Ŀ� ����
		// ��� ��ü���� �̵� �� ������Ű��
		//���� ����� �̿��� 3���� ��ü�� 2������ ������Ŵ
		//�̶� ����Ʈ ��ȯ�� �ػ� ������ ���ϰ� �ϱ� ����
		//-1 ~ 1���� ������ ����� ����ȭ �۾��� ����

		TransData.View = _View;
		TransData.Projection = _Projection;
		TransData.WorldViewProjectionMatrix = TransData.WorldMatrix * TransData.View * TransData.Projection;
	}

	//����Ʈ ��ȯ
	inline const void SetViewPort(const float4x4& _ViewPort)
	{
		//ȭ�� �ػ󵵸� �����Ŵ
		TransData.ViewPort = _ViewPort;
		TransData.WorldViewProjectionMatrix *= TransData.ViewPort;
	}

	void CalChild();

	void SetParent(GameEngineTransform* _Parent, bool _IsParentWorld = true);

	inline GameEngineTransform* GetParent() const
	{
		return Parent;
	}

	const TransformData& GetTransDataRef()
	{
		return TransData;
	}

	void SetTransformData(const TransformData& _Data)
	{
		TransData = _Data;
	}

protected:

private:
	TransformData TransData;

	//���� ��ǥ�� ����ġ
	bool AbsoluteScale = false;
	bool AbsoluteRotation = false;
	bool AbsolutePosition = false;

	//�θ� �ڽ� ����
	GameEngineTransform* Parent = nullptr;
	std::list<GameEngineTransform*> Child;

	
	
	//�ڽ��� ���� ��Ŀ��� ���� ũ���� ����
	void LocalDecompose();

	//�ڽ��� ���� ��Ŀ��� ���� ũ���� ����
	void WorldDecompose();

	//�θ� �ִ� ��� �θ��� ���� ����� �������� �ڽ��� ���� ����� ����Ѵ�
	void WorldCalculation();

	//��� Absolute bool���� local�� ����
	void AbsoluteReset();


	void TransformUpdate();


	//��������
private:
	//�ڽŰ� �ڽ��� LiveŸ���� ��������� ������Ų��
	void AllAccTime(float _DeltaTime);

	//�ڽŰ� �ڽ��� Update�� ��������� ȣ���Ѵ�
	void AllUpdate(float _DeltaTime);

	//�ڽŰ� �ڽ��� Render�� ��������� ȣ���Ѵ�
	void AllRender(float _DeltaTime);

	//�ڽŰ� �ڽ��� Release�� ��������� ȣ���Ѵ�
	void AllRelease();

	//�ڽĵ� �߿��� Deathó���� ������Ʈ�� ����Ʈ���� ���ܽ�Ų��
	void ChildRelease();

	inline void SetMaster(GameEngineObject* _Master)
	{
		Master = _Master;
	}

	inline GameEngineObject* GetMaster() const
	{
		return Master;
	}

	GameEngineObject* Master = nullptr;




	//---------------Collision-----------



public:
	bool Collision(const CollisionParameter& Data);

private:
	friend class InitColFunction;

	CollisionData ColData;

	static std::function<bool(GameEngineTransform*, GameEngineTransform*)> ArrColFunction[static_cast<int>(ColType::MAX)][static_cast<int>(ColType::MAX)];

	static bool SphereToSpehre(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool SphereToAABB(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool SphereToOBB(GameEngineTransform* _Left, GameEngineTransform* _Right);

	static bool AABBToSpehre(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool AABBToAABB(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool AABBToOBB(GameEngineTransform* _Left, GameEngineTransform* _Right);

	static bool OBBToSpehre(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool OBBToAABB(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool OBBToOBB(GameEngineTransform* _Left, GameEngineTransform* _Right);

	static bool Sphere2DToSpehre2D(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool Sphere2DToAABB2D(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool Sphere2DToOBB2D(GameEngineTransform* _Left, GameEngineTransform* _Right);

	static bool AABB2DToSpehre2D(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool AABB2DToAABB2D(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool AABB2DToOBB2D(GameEngineTransform* _Left, GameEngineTransform* _Right);

	static bool OBB2DToSpehre2D(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool OBB2DToAABB2D(GameEngineTransform* _Left, GameEngineTransform* _Right);
	static bool OBB2DToOBB2D(GameEngineTransform* _Left, GameEngineTransform* _Right);
};

