#pragma once
#include <list>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineTransform
{
public:
	GameEngineTransform();
	~GameEngineTransform();

	GameEngineTransform(const GameEngineTransform& _Other) = delete;
	GameEngineTransform(GameEngineTransform&& _Other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _Other) = delete;
	GameEngineTransform& operator=(const GameEngineTransform&& _Other) noexcept = delete;

	void SetLocalScale(const float4& _Value)
	{
		LocalScale = _Value;
		TransformUpdate();
	}

	void SetLocalRotation(const float4& _Value)
	{
		LocalRotation = _Value;
		TransformUpdate();
	}

	void SetLocalPosition(const float4& _Value)
	{
		LocalPosition = _Value;
		TransformUpdate();
	}

	void AddLocalScale(const float4& _Value)
	{
		LocalScale += _Value;
		TransformUpdate();
	}

	void AddLocalRotation(const float4& _Value)
	{
		LocalRotation += _Value;
		TransformUpdate();
	}

	void AddLocalPosition(const float4& _Value)
	{
		LocalPosition += _Value;
		TransformUpdate();
	}


	float4 GetLocalForwardVector()
	{
		//행렬의 2행을 Return해준다
		//Forward(Z축)의 값이 2행인 이유는
		//행렬의 곱셉이 일어날때 z가 몇행과만 연산되는지 생각하면 알 수 있다.
		return LocalWorldMatrix.ArrVector[2].NormalizeReturn();
	}

	float4 GetLocalUpVector()
	{
		//행렬의 1행을 Return해준다
		//Up(Y축)의 값이 1행인 이유는
		//행렬의 곱셉이 일어날때 y가 몇행과만 연산되는지 생각하면 알 수 있다.
		return LocalWorldMatrix.ArrVector[1].NormalizeReturn();
	}

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
		WorldMatrix = WorldMatrix * View * Projection;
	}

	//뷰포트 변환
	inline const void SetViewPort(const float4x4& _ViewPort)
	{
		//화면 해상도를 적용시킴
		ViewPort = _ViewPort;
		WorldMatrix *= ViewPort;
	}

protected:

private:
	void TransformUpdate();

	GameEngineTransform* Parent = nullptr;
	std::list<GameEngineTransform*> Child;

	//스케일은 초기값이 1벡터이여야 함
	float4 LocalScale = float4::One;
	float4 LocalRotation = float4::Zero;
	float4 LocalPosition = float4::Zero;

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
};

