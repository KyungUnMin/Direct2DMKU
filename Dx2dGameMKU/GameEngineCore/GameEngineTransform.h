#pragma once
#include <list>
#include <memory>
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

	//���� �����Ͽ� ���� ���� �Է��ϰ� ���� �������� ����ķ� ����Ѵ�
	void SetWorldScale(const float4& _Value)
	{
		WorldScale = _Value;

		//���� �ֻ��� �θ��� ���
		if (nullptr == Parent)
		{
			LocalScale = WorldScale;

			//���ð��� ����Ǿ����Ƿ� �� ���
			TransformUpdate();
			CalChild();
			return;
		}

		//���彺���� * �θ��� �����
		LocalScale = WorldScale * Parent->GetWorldMatrixRef().InverseReturn();
	}

	
	void SetWorldRotation(const float4& _Value)
	{
		WorldRotation = _Value;

		if (nullptr == Parent)
		{
			LocalRotation = WorldRotation;
		}

		TransformUpdate();
	}

	//���� �����ǿ� ���� ���� �Է��ϰ� ���� �������� ����ķ� ����Ѵ�
	void SetWorldPosition(const float4& _Value)
	{
		WorldPosition = _Value;
		TransformUpdate();
	}


	//���ð��� �����Ҷ����� �� ����Ѵ�
	void SetLocalScale(const float4& _Value)
	{
		LocalScale = _Value;
		TransformUpdate();
	}

	//���ð��� �����Ҷ����� �� ����Ѵ�
	void SetLocalRotation(const float4& _Value)
	{
		LocalRotation = _Value;
		TransformUpdate();
	}

	//���ð��� �����Ҷ����� �� ����Ѵ�
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

	//����İ� ��������� ���� ����
	inline const void SetCameraMatrix(const float4x4& _View, const float4x4& _Projection)
	{
		//������� �̿��� ī�޶��� ��Ŀ� ����
		// ��� ��ü���� �̵� �� ������Ű��
		//���� ����� �̿��� 3���� ��ü�� 2������ ������Ŵ
		//�̶� ����Ʈ ��ȯ�� �ػ� ������ ���ϰ� �ϱ� ����
		//-1 ~ 1���� ������ ����� ����ȭ �۾��� ����

		View = _View;
		Projection = _Projection;
		WorldMatrix = WorldMatrix * View * Projection;
	}

	//����Ʈ ��ȯ
	inline const void SetViewPort(const float4x4& _ViewPort)
	{
		//ȭ�� �ػ󵵸� �����Ŵ
		ViewPort = _ViewPort;
		WorldMatrix *= ViewPort;
	}

	void CalChild()
	{

	}

protected:

private:
	void TransformUpdate();

	//(�θ� ��������)������ǥ
	float4 LocalScale = float4::One;
	float4 LocalRotation = float4::Zero;
	float4 LocalPosition = float4::Zero;

	//������ǥ��
	float4 WorldScale = float4::One;
	float4 WorldRotation = float4::Zero;
	float4 WorldPosition = float4::Zero;


	float4x4 LocalScaleMatrix;
	float4x4 LocalRotationMatrix;
	float4x4 LocalPositionMatrix;


	//�������(ũ����)
	float4x4 LocalWorldMatrix;

	//�������
	float4x4 WorldMatrix;

	//�����
	float4x4 View;

	//�������
	float4x4 Projection;

	//����Ʈ ���
	float4x4 ViewPort;


	//�θ� �ڽ� ����
	GameEngineTransform* Parent = nullptr;
	std::list<GameEngineTransform*> Child;
};

