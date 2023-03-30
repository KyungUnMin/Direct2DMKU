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
		//����� 2���� Return���ش�
		//Forward(Z��)�� ���� 2���� ������
		//����� ������ �Ͼ�� z�� ������� ����Ǵ��� �����ϸ� �� �� �ִ�.
		return LocalWorldMatrix.ArrVector[2].NormalizeReturn();
	}

	float4 GetLocalUpVector()
	{
		//����� 1���� Return���ش�
		//Up(Y��)�� ���� 1���� ������
		//����� ������ �Ͼ�� y�� ������� ����Ǵ��� �����ϸ� �� �� �ִ�.
		return LocalWorldMatrix.ArrVector[1].NormalizeReturn();
	}

	float4 GetLocalRightVector()
	{
		//����� 0���� Return���ش�
		//Right(x��)�� ���� 0���� ������
		//����� ������ �Ͼ�� x�� ������� ����Ǵ��� �����ϸ� �� �� �ִ�.
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


	//ī�޶��� ������� �޾� �ٸ� Actor���� �� ����Ŀ� ������ �޴´�
	inline const void SetView(const float4x4& _View)
	{
		View = _View;
		WorldMatrix = WorldMatrix * View;
	}

protected:

private:
	void TransformUpdate();

	GameEngineTransform* Parent = nullptr;
	std::list<GameEngineTransform*> Child;

	//�������� �ʱⰪ�� 1�����̿��� ��
	float4 LocalScale = float4::One;
	float4 LocalRotation = float4::Zero;
	float4 LocalPosition = float4::Zero;

	float4x4 LocalScaleMatrix;
	float4x4 LocalRotationMatrix;
	float4x4 LocalPositionMatrix;

	//�������(ũ����)
	float4x4 LocalWorldMatrix;

	//�������
	float4x4 WorldMatrix;

	//�����
	float4x4 View;
};

