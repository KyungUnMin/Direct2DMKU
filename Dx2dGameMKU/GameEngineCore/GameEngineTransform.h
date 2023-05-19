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
	// 계산용
	float4 Scale;
	float4 Rotation;
	float4 Quaternion;
	float4 Position;

	//로컬 (Get 함수용)
	float4 LocalScale;
	float4 LocalRotation;
	float4 LocalQuaternion;
	float4 LocalPosition;

	//월드 (Get 함수용)
	float4 WorldScale;
	float4 WorldRotation;
	float4 WorldQuaternion;
	float4 WorldPosition;

	//계산용 크자이 행렬
	float4x4 ScaleMatrix;
	float4x4 RotationMatrix;
	float4x4 PositionMatrix;

	//로컬행렬(크자이)
	float4x4 LocalWorldMatrix;

	//월드행렬(크자이)
	float4x4 WorldMatrix;

	//뷰행렬
	float4x4 View;

	//투영행렬
	float4x4 Projection;

	//뷰포트 행렬
	float4x4 ViewPort;

	//카메라와 연산될때 사용하는 월드*뷰*프로젝션*뷰포트행렬
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

		//값이 변경됐으므로 최종 로컬행렬, 최종 월드행렬을 다시 계산
		TransformUpdate();
		//자식이 있다면 자식들의 월드/로컬행렬을 재계산
		CalChild();
	}


	void SetWorldRotation(const float4& _Value)
	{
		AbsoluteRotation = true;
		TransData.Rotation = _Value;

		//값이 변경됐으므로 최종 로컬행렬, 최종 월드행렬을 다시 계산
		TransformUpdate();
		//자식이 있다면 자식들의 월드/로컬행렬을 재계산
		CalChild();
	}


	void SetWorldPosition(const float4& _Value)
	{
		AbsolutePosition = true;
		TransData.Position = _Value;

		//값이 변경됐으므로 최종 로컬행렬, 최종 월드행렬을 다시 계산
		TransformUpdate();
		//자식이 있다면 자식들의 월드/로컬행렬을 재계산
		CalChild();
	}


	void SetLocalScale(const float4& _Value)
	{
		AbsoluteScale = false;
		TransData.Scale = _Value;

		//값이 변경됐으므로 최종 로컬행렬, 최종 월드행렬을 다시 계산
		TransformUpdate();
		//자식이 있다면 자식들의 월드/로컬행렬을 재계산
		CalChild();
	}


	void SetLocalRotation(const float4& _Value)
	{
		AbsoluteRotation = false;
		TransData.Rotation = _Value;

		//값이 변경됐으므로 최종 로컬행렬, 최종 월드행렬을 다시 계산
		TransformUpdate();
		//자식이 있다면 자식들의 월드/로컬행렬을 재계산
		CalChild();
	}


	void SetLocalPosition(const float4& _Value)
	{
		AbsolutePosition = false;
		TransData.Position = _Value;

		//값이 변경됐으므로 최종 로컬행렬, 최종 월드행렬을 다시 계산
		TransformUpdate();
		//자식이 있다면 자식들의 월드/로컬행렬을 재계산
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



	//월드 좌표계의 +Z 반환
	float4 GetWorldForwardVector()
	{
		return TransData.WorldMatrix.ArrVector[2].NormalizeReturn();
	}

	//월드 좌표계의 +Y 반환
	float4 GetWorldUpVector()
	{
		return TransData.WorldMatrix.ArrVector[1].NormalizeReturn();
	}

	//월드 좌표계의 +X 반환
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


	
	//로컬 좌표계의 +Z 반환
	float4 GetLocalForwardVector()
	{
		//행렬의 2행을 Return해준다
		//Forward(Z축)의 값이 2행인 이유는
		//행렬의 곱셉이 일어날때 z가 몇행과만 연산되는지 생각하면 알 수 있다.
		return TransData.LocalWorldMatrix.ArrVector[2].NormalizeReturn();
	}

	//로컬 좌표계의 +Y 반환
	float4 GetLocalUpVector()
	{
		//행렬의 1행을 Return해준다
		//Up(Y축)의 값이 1행인 이유는
		//행렬의 곱셉이 일어날때 y가 몇행과만 연산되는지 생각하면 알 수 있다.
		return TransData.LocalWorldMatrix.ArrVector[1].NormalizeReturn();
	}

	//로컬 좌표계의 +X 반환
	float4 GetLocalRightVector()
	{
		//행렬의 0행을 Return해준다
		//Right(x축)의 값이 0행인 이유는
		//행렬의 곱셉이 일어날때 x가 몇행과만 연산되는지 생각하면 알 수 있다.
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

	//뷰행렬과 투영행렬을 전부 곱함
	inline const void SetCameraMatrix(const float4x4& _View, const float4x4& _Projection)
	{
		//뷰행렬을 이용해 카메라의 행렬에 따라
		// 모든 물체들을 이동 및 공전시키고
		//투영 행렬을 이용해 3차원 물체를 2차원에 투영시킴
		//이때 뷰포트 변환시 해상도 적용을 편하게 하기 위해
		//-1 ~ 1사이 값으로 만드는 정규화 작업이 들어간다

		TransData.View = _View;
		TransData.Projection = _Projection;
		TransData.WorldViewProjectionMatrix = TransData.WorldMatrix * TransData.View * TransData.Projection;
	}

	//뷰포트 변환
	inline const void SetViewPort(const float4x4& _ViewPort)
	{
		//화면 해상도를 적용시킴
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

	//월드 좌표계 스위치
	bool AbsoluteScale = false;
	bool AbsoluteRotation = false;
	bool AbsolutePosition = false;

	//부모 자식 관계
	GameEngineTransform* Parent = nullptr;
	std::list<GameEngineTransform*> Child;

	
	
	//자신의 로컬 행렬에서 로컬 크자이 추출
	void LocalDecompose();

	//자신의 월드 행렬에서 월드 크자이 추출
	void WorldDecompose();

	//부모가 있는 경우 부모의 월드 행렬을 바탕으로 자신의 월드 행렬을 계산한다
	void WorldCalculation();

	//모든 Absolute bool값을 local로 변경
	void AbsoluteReset();


	void TransformUpdate();


	//계층구조
private:
	//자신과 자식의 Live타임을 재귀적으로 증가시킨다
	void AllAccTime(float _DeltaTime);

	//자신과 자식의 Update를 재귀적으로 호출한다
	void AllUpdate(float _DeltaTime);

	//자신과 자식의 Render를 재귀적으로 호출한다
	void AllRender(float _DeltaTime);

	//자신과 자식의 Release를 재귀적으로 호출한다
	void AllRelease();

	//자식들 중에서 Death처리된 오브젝트를 리스트에서 제외시킨다
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

