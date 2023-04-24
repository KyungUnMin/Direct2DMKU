#pragma once
#include <list>
#include <memory>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"

struct TransformData
{
	//(부모에 종속적인)로컬좌표
	float4 LocalScale;
	float4 LocalRotation;
	Quaternion LocalQuaternion;
	float4 LocalPosition;

	//월드좌표계
	float4 WorldScale;
	float4 WorldRotation;
	Quaternion WorldQuaternion;
	float4 WorldPosition;


	float4x4 LocalScaleMatrix;
	float4x4 LocalRotationMatrix;
	float4x4 LocalPositionMatrix;


	//로컬행렬(크자이)
	float4x4 LocalWorldMatrix;

	//월드행렬
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
		LocalScale = float4::One;
		LocalRotation = float4::Null;
		LocalQuaternion = DirectX::XMQuaternionIdentity();
		LocalPosition = float4::Zero;
		WorldScale = float4::One;
		WorldRotation = float4::Null;
		WorldQuaternion = DirectX::XMQuaternionIdentity();
		WorldPosition = float4::Zero;
	}
};



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
		TransData.WorldScale = _Value;

		//내가 최상위 부모인 경우
		if (nullptr == Parent)
		{
			TransData.LocalScale = TransData.WorldScale;
		}
		else
		{
			//월드스케일 * 부모의 역행렬
			TransData.LocalScale = TransData.WorldScale * Parent->GetWorldMatrixRef().InverseReturn();
		}

		//값이 변경됐으므로 최종 로컬행렬, 최종 월드행렬을 다시 계산
		TransformUpdate();
		//자식이 있다면 자식들의 월드/로컬행렬을 재계산
		CalChild();
	}

	
	void SetWorldRotation(const float4& _Value)
	{
		TransData.WorldRotation = _Value;

		//내가 최상위 부모인 경우
		if (nullptr == Parent)
		{
			TransData.LocalRotation = TransData.WorldRotation;
		}
		else
		{
			//회전만 봤을때
			//내가 월드(0,0,0)회전이고
			//부모가 월드(10, 0, 0)회전이면
			//결과적으로 내 로컬회전은 (-10, 0, 0)이 된다
			//근데 안된다, 일단은 나중에 생각하자
			TransData.LocalRotation = TransData.WorldRotation - Parent->GetWorldRotation();
		}

		//값이 변경됐으므로 최종 로컬행렬, 최종 월드행렬을 다시 계산
		TransformUpdate();
		//자식이 있다면 자식들의 월드/로컬행렬을 재계산
		CalChild();
	}

	//월드 포지션에 값을 직접 입력하고 로컬 포지션을 역행렬로 계산한다
	void SetWorldPosition(const float4& _Value)
	{
		TransData.WorldPosition = _Value;

		//내가 최상위 부모인 경우
		if (nullptr == Parent)
		{
			TransData.LocalPosition = TransData.WorldPosition;
		}
		else
		{
			TransData.LocalPosition = TransData.WorldPosition * Parent->GetWorldMatrixRef().InverseReturn();
		}

		//값이 변경됐으므로 최종 로컬행렬, 최종 월드행렬을 다시 계산
		TransformUpdate();
		//자식이 있다면 자식들의 월드/로컬행렬을 재계산
		CalChild();
	}


	void SetLocalScale(const float4& _Value)
	{
		TransData.LocalScale = _Value;

		//내가 최상위 부모인 경우
		if (nullptr == Parent)
		{
			TransData.WorldScale = TransData.LocalScale;
		}
		else
		{
			TransData.WorldScale = TransData.LocalScale * Parent->GetWorldMatrixRef();
		}

		//값이 변경됐으므로 최종 로컬행렬, 최종 월드행렬을 다시 계산
		TransformUpdate();
		//자식이 있다면 자식들의 월드/로컬행렬을 재계산
		CalChild();
	}

	//로컬값을 변경할때마다 재 계산한다
	void SetLocalRotation(const float4& _Value)
	{
		TransData.LocalRotation = _Value;

		//최상위 부모인 경우
		if (nullptr == Parent)
		{
			TransData.WorldRotation = TransData.LocalRotation;
		}
		else
		{
			//회전만 봤을때
			//내가 로컬(10,0,0)회전이고
			//부모가 월드(10, 0, 0)회전이면
			//결과적으로 내 월드회전은 (20, 0, 0)이 된다
			TransData.WorldRotation = TransData.LocalRotation + Parent->GetWorldRotation();
		}

		//값이 변경됐으므로 최종 로컬행렬, 최종 월드행렬을 다시 계산
		TransformUpdate();
		//자식이 있다면 자식들의 월드/로컬행렬을 재계산
		CalChild();
	}

	//로컬값을 변경할때마다 재 계산한다
	void SetLocalPosition(const float4& _Value)
	{
		TransData.LocalPosition = _Value;

		//최상위 부모인 경우
		if (nullptr == Parent)
		{
			TransData.WorldPosition = TransData.LocalPosition;
		}
		else
		{
			//회전만 봤을때
			//내가 로컬(10,0,0)회전이고
			//부모가 월드(10, 0, 0)회전이면
			//결과적으로 내 월드회전은 (20, 0, 0)이 된다
			TransData.WorldPosition = TransData.LocalPosition * Parent->GetWorldMatrixRef();
		}

		//값이 변경됐으므로 최종 로컬행렬, 최종 월드행렬을 다시 계산
		TransformUpdate();
		//자식이 있다면 자식들의 월드/로컬행렬을 재계산
		CalChild();
	}



	void AddLocalScale(const float4& _Value)
	{
		SetLocalScale(TransData.LocalScale + _Value);
	}

	void AddLocalRotation(const float4& _Value)
	{
		SetLocalRotation(TransData.LocalRotation + _Value);
	}

	void AddLocalPosition(const float4& _Value)
	{
		SetLocalPosition(TransData.LocalPosition + _Value);
	}

	void AddWorldScale(const float4& _Value)
	{
		SetWorldScale(TransData.WorldScale + _Value);
	}

	void AddWorldRotation(const float4& _Value)
	{
		SetWorldRotation(TransData.WorldRotation + _Value);
	}

	void AddWorldPosition(const float4& _Value)
	{
		SetWorldPosition(TransData.WorldPosition + _Value);
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




	float4 GetLocalPosition()
	{
		return TransData.LocalPosition;
	}

	float4 GetLocalScale()
	{
		return TransData.LocalScale;
	}

	float4 GetLocalRotation()
	{
		return TransData.LocalRotation;
	}



	float4 GetWorldPosition()
	{
		return TransData.WorldPosition;
	}

	float4 GetWorldScale()
	{
		return TransData.WorldScale;
	}

	float4 GetWorldRotation()
	{
		return TransData.WorldRotation;
	}




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
		TransData.WorldMatrix *= TransData.ViewPort;
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

	const TransformData& GetTransDataRef()
	{
		return TransData;
	}

	void SetTransformData(const TransformData& _Data)
	{
		TransData = _Data;
	}


	//LocalScale의 X를 원점대칭이동(이미지 좌우 반전시 사용)
	void SetLocalFlipScaleX()
	{
		TransData.LocalScale.x = -TransData.LocalScale.x;
		SetLocalScale(TransData.LocalScale);
	}

	//LocalScale의 X를 항상 음수값으로(이미지 방향 설정시 사용)
	void SetLocalNegativeScaleX()
	{
		if (0 < TransData.LocalScale.x)
		{
			SetLocalFlipScaleX();
			return;
		}

		return;
	}

	//LocalScale의 X를 항상 양수값으로(이미지 방향 설정시 사용)
	void SetLocalPositiveScaleX()
	{
		if (0 > TransData.LocalScale.x)
		{
			SetLocalFlipScaleX();
			return;
		}

		return;
	}

protected:

private:
	void TransformUpdate();

	TransformData TransData;


	//부모 자식 관계
	GameEngineTransform* Parent = nullptr;
	std::list<GameEngineTransform*> Child;
};

