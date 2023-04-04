#pragma once
#include <list>
#include <memory>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"

class GameEngineTransform : public GameEngineObjectBase
{
public:
	GameEngineTransform();
	~GameEngineTransform() override;

	GameEngineTransform(const GameEngineTransform& _Other) = delete;
	GameEngineTransform(GameEngineTransform&& _Other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _Other) = delete;
	GameEngineTransform& operator=(const GameEngineTransform&& _Other) noexcept = delete;

	//월드 스케일에 값을 직접 입력하고 로컬 스케일을 역행렬로 계산한다
	void SetWorldScale(const float4& _Value)
	{
		WorldScale = _Value;

		//내가 최상위 부모인 경우
		if (nullptr == Parent)
		{
			LocalScale = WorldScale;
		}
		else
		{
			//월드스케일 * 부모의 역행렬
			LocalScale = WorldScale * Parent->GetWorldMatrixRef().InverseReturn();
		}

		//값이 변경됐으므로 최종 로컬행렬, 최종 월드행렬을 다시 계산
		TransformUpdate();
		//자식이 있다면 자식들의 월드/로컬행렬을 재계산
		CalChild();
	}

	
	void SetWorldRotation(const float4& _Value)
	{
		WorldRotation = _Value;

		//내가 최상위 부모인 경우
		if (nullptr == Parent)
		{
			LocalRotation = WorldRotation;
		}
		else
		{
			float4 Rot = Parent->GetWorldRotation();

			//회전만 봤을때
			//내가 월드(0,0,0)회전이고
			//부모가 월드(10, 0, 0)회전이면
			//결과적으로 내 로컬회전은 (-10, 0, 0)이 된다
			LocalRotation = WorldRotation - Parent->GetWorldRotation();
		}

		//값이 변경됐으므로 최종 로컬행렬, 최종 월드행렬을 다시 계산
		TransformUpdate();
		//자식이 있다면 자식들의 월드/로컬행렬을 재계산
		CalChild();
	}

	//월드 포지션에 값을 직접 입력하고 로컬 포지션을 역행렬로 계산한다
	void SetWorldPosition(const float4& _Value)
	{
		WorldPosition = _Value;

		//내가 최상위 부모인 경우
		if (nullptr == Parent)
		{
			LocalPosition = WorldPosition;
		}
		else
		{
			LocalPosition = WorldPosition * Parent->GetWorldMatrixRef().InverseReturn();
		}

		//값이 변경됐으므로 최종 로컬행렬, 최종 월드행렬을 다시 계산
		TransformUpdate();
		//자식이 있다면 자식들의 월드/로컬행렬을 재계산
		CalChild();
	}


	void SetLocalScale(const float4& _Value)
	{
		LocalScale = _Value;

		//내가 최상위 부모인 경우
		if (nullptr == Parent)
		{
			WorldScale = LocalScale;
		}
		else
		{
			WorldScale = LocalScale * Parent->GetWorldMatrixRef();
		}

		//값이 변경됐으므로 최종 로컬행렬, 최종 월드행렬을 다시 계산
		TransformUpdate();
		//자식이 있다면 자식들의 월드/로컬행렬을 재계산
		CalChild();
	}

	//로컬값을 변경할때마다 재 계산한다
	void SetLocalRotation(const float4& _Value)
	{
		LocalRotation = _Value;

		//최상위 부모인 경우
		if (nullptr == Parent)
		{
			WorldRotation = LocalRotation;
		}
		else
		{
			//회전만 봤을때
			//내가 로컬(10,0,0)회전이고
			//부모가 월드(10, 0, 0)회전이면
			//결과적으로 내 월드회전은 (20, 0, 0)이 된다
			WorldRotation = LocalRotation + Parent->GetWorldRotation();
		}

		//값이 변경됐으므로 최종 로컬행렬, 최종 월드행렬을 다시 계산
		TransformUpdate();
		//자식이 있다면 자식들의 월드/로컬행렬을 재계산
		CalChild();
	}

	//로컬값을 변경할때마다 재 계산한다
	void SetLocalPosition(const float4& _Value)
	{
		LocalPosition = _Value;

		//최상위 부모인 경우
		if (nullptr == Parent)
		{
			WorldPosition = LocalPosition;
		}
		else
		{
			//회전만 봤을때
			//내가 로컬(10,0,0)회전이고
			//부모가 월드(10, 0, 0)회전이면
			//결과적으로 내 월드회전은 (20, 0, 0)이 된다
			WorldPosition = LocalPosition * Parent->GetWorldMatrixRef();
		}

		//값이 변경됐으므로 최종 로컬행렬, 최종 월드행렬을 다시 계산
		TransformUpdate();
		//자식이 있다면 자식들의 월드/로컬행렬을 재계산
		CalChild();
	}



	void AddLocalScale(const float4& _Value)
	{
		SetLocalScale(LocalScale + _Value);
	}

	void AddLocalRotation(const float4& _Value)
	{
		SetLocalRotation(LocalRotation + _Value);
	}

	void AddLocalPosition(const float4& _Value)
	{
		SetLocalPosition(LocalPosition + _Value);
	}



	//월드 좌표계의 +Z 반환
	float4 GetWorldForwardVector()
	{
		return WorldMatrix.ArrVector[2].NormalizeReturn();
	}

	//월드 좌표계의 +Y 반환
	float4 GetWorldUpVector()
	{
		return WorldMatrix.ArrVector[1].NormalizeReturn();
	}

	//월드 좌표계의 +X 반환
	float4 GetWorldRightVector()
	{
		return WorldMatrix.ArrVector[0].NormalizeReturn();
	}


	//로컬 좌표계의 +Z 반환
	float4 GetLocalForwardVector()
	{
		//행렬의 2행을 Return해준다
		//Forward(Z축)의 값이 2행인 이유는
		//행렬의 곱셉이 일어날때 z가 몇행과만 연산되는지 생각하면 알 수 있다.
		return LocalWorldMatrix.ArrVector[2].NormalizeReturn();
	}

	//로컬 좌표계의 +Y 반환
	float4 GetLocalUpVector()
	{
		//행렬의 1행을 Return해준다
		//Up(Y축)의 값이 1행인 이유는
		//행렬의 곱셉이 일어날때 y가 몇행과만 연산되는지 생각하면 알 수 있다.
		return LocalWorldMatrix.ArrVector[1].NormalizeReturn();
	}

	//로컬 좌표계의 +X 반환
	float4 GetLocalRightVector()
	{
		//행렬의 0행을 Return해준다
		//Right(x축)의 값이 0행인 이유는
		//행렬의 곱셉이 일어날때 x가 몇행과만 연산되는지 생각하면 알 수 있다.
		return LocalWorldMatrix.ArrVector[0].NormalizeReturn();
	}




	float4 GetLocalPosition()
	{
		return LocalPosition;
	}

	float4 GetLocalScale()
	{
		return LocalScale;
	}

	float4 GetLocalRotation()
	{
		return LocalRotation;
	}



	float4 GetWorldPosition()
	{
		return WorldPosition;
	}

	float4 GetWorldScale()
	{
		return WorldScale;
	}

	float4 GetWorldRotation()
	{
		return WorldRotation;
	}




	float4x4 GetLocalWorldMatrix()
	{
		return LocalWorldMatrix;
	}

	const float4x4& GetLocalWorldMatrixRef()
	{
		return LocalWorldMatrix;
	}

	const float4x4 GetWorldMatrix()
	{
		return WorldMatrix;
	}

	const float4x4& GetWorldMatrixRef()
	{
		return WorldMatrix;
	}

	const float4x4 GetWorldViewProjectionMatrix()
	{
		return WorldViewProjectionMatrix;
	}

	const float4x4& GetWorldViewProjectionMatrixRef()
	{
		return WorldViewProjectionMatrix;
	}


	//뷰행렬과 투영행렬을 전부 곱함
	inline const void SetCameraMatrix(const float4x4& _View, const float4x4& _Projection)
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

	//뷰포트 변환
	inline const void SetViewPort(const float4x4& _ViewPort)
	{
		//화면 해상도를 적용시킴
		ViewPort = _ViewPort;
		WorldMatrix *= ViewPort;
	}

	void CalChild()
	{
		//만약 자식이 있다면 자식의 로컬/월드 행렬 재계산
		//(SetLocal안에서 월드 행렬도 재 계산한다)
		for (GameEngineTransform* ChildTrans : Child)
		{
			ChildTrans->SetLocalScale(ChildTrans->GetLocalScale());
			ChildTrans->SetLocalRotation(ChildTrans->GetLocalRotation());
			ChildTrans->SetLocalPosition(ChildTrans->GetLocalPosition());
		}
	}

	void SetParent(GameEngineTransform* _Parent);

protected:

private:
	void TransformUpdate();

	//(부모에 종속적인)로컬좌표
	float4 LocalScale = float4::One;
	float4 LocalRotation = float4::Null;
	float4 LocalPosition = float4::Zero;

	//월드좌표계
	float4 WorldScale = float4::One;
	float4 WorldRotation = float4::Null;
	float4 WorldPosition = float4::Zero;


	float4x4 LocalScaleMatrix;
	float4x4 LocalRotationMatrix;
	float4x4 LocalPositionMatrix;


	//로컬행렬(크자이)
	float4x4 LocalWorldMatrix;

	//월드행렬
	float4x4 WorldMatrix;

	//카메라와 연산될때 사용하는 월드*뷰*프로젝션*뷰포트행렬
	float4x4 WorldViewProjectionMatrix;

	//뷰행렬
	float4x4 View;

	//투영행렬
	float4x4 Projection;

	//뷰포트 행렬
	float4x4 ViewPort;


	//부모 자식 관계
	GameEngineTransform* Parent = nullptr;
	std::list<GameEngineTransform*> Child;
};

