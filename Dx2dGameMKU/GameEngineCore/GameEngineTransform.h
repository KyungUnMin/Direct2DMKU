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

	//���� �����Ͽ� ���� ���� �Է��ϰ� ���� �������� ����ķ� ����Ѵ�
	void SetWorldScale(const float4& _Value)
	{
		WorldScale = _Value;

		//���� �ֻ��� �θ��� ���
		if (nullptr == Parent)
		{
			LocalScale = WorldScale;
		}
		else
		{
			//���彺���� * �θ��� �����
			LocalScale = WorldScale * Parent->GetWorldMatrixRef().InverseReturn();
		}

		//���� ��������Ƿ� ���� �������, ���� ��������� �ٽ� ���
		TransformUpdate();
		//�ڽ��� �ִٸ� �ڽĵ��� ����/��������� ����
		CalChild();
	}

	
	void SetWorldRotation(const float4& _Value)
	{
		WorldRotation = _Value;

		//���� �ֻ��� �θ��� ���
		if (nullptr == Parent)
		{
			LocalRotation = WorldRotation;
		}
		else
		{
			float4 Rot = Parent->GetWorldRotation();

			//ȸ���� ������
			//���� ����(0,0,0)ȸ���̰�
			//�θ� ����(10, 0, 0)ȸ���̸�
			//��������� �� ����ȸ���� (-10, 0, 0)�� �ȴ�
			LocalRotation = WorldRotation - Parent->GetWorldRotation();
		}

		//���� ��������Ƿ� ���� �������, ���� ��������� �ٽ� ���
		TransformUpdate();
		//�ڽ��� �ִٸ� �ڽĵ��� ����/��������� ����
		CalChild();
	}

	//���� �����ǿ� ���� ���� �Է��ϰ� ���� �������� ����ķ� ����Ѵ�
	void SetWorldPosition(const float4& _Value)
	{
		WorldPosition = _Value;

		//���� �ֻ��� �θ��� ���
		if (nullptr == Parent)
		{
			LocalPosition = WorldPosition;
		}
		else
		{
			LocalPosition = WorldPosition * Parent->GetWorldMatrixRef().InverseReturn();
		}

		//���� ��������Ƿ� ���� �������, ���� ��������� �ٽ� ���
		TransformUpdate();
		//�ڽ��� �ִٸ� �ڽĵ��� ����/��������� ����
		CalChild();
	}


	void SetLocalScale(const float4& _Value)
	{
		LocalScale = _Value;

		//���� �ֻ��� �θ��� ���
		if (nullptr == Parent)
		{
			WorldScale = LocalScale;
		}
		else
		{
			WorldScale = LocalScale * Parent->GetWorldMatrixRef();
		}

		//���� ��������Ƿ� ���� �������, ���� ��������� �ٽ� ���
		TransformUpdate();
		//�ڽ��� �ִٸ� �ڽĵ��� ����/��������� ����
		CalChild();
	}

	//���ð��� �����Ҷ����� �� ����Ѵ�
	void SetLocalRotation(const float4& _Value)
	{
		LocalRotation = _Value;

		//�ֻ��� �θ��� ���
		if (nullptr == Parent)
		{
			WorldRotation = LocalRotation;
		}
		else
		{
			//ȸ���� ������
			//���� ����(10,0,0)ȸ���̰�
			//�θ� ����(10, 0, 0)ȸ���̸�
			//��������� �� ����ȸ���� (20, 0, 0)�� �ȴ�
			WorldRotation = LocalRotation + Parent->GetWorldRotation();
		}

		//���� ��������Ƿ� ���� �������, ���� ��������� �ٽ� ���
		TransformUpdate();
		//�ڽ��� �ִٸ� �ڽĵ��� ����/��������� ����
		CalChild();
	}

	//���ð��� �����Ҷ����� �� ����Ѵ�
	void SetLocalPosition(const float4& _Value)
	{
		LocalPosition = _Value;

		//�ֻ��� �θ��� ���
		if (nullptr == Parent)
		{
			WorldPosition = LocalPosition;
		}
		else
		{
			//ȸ���� ������
			//���� ����(10,0,0)ȸ���̰�
			//�θ� ����(10, 0, 0)ȸ���̸�
			//��������� �� ����ȸ���� (20, 0, 0)�� �ȴ�
			WorldPosition = LocalPosition * Parent->GetWorldMatrixRef();
		}

		//���� ��������Ƿ� ���� �������, ���� ��������� �ٽ� ���
		TransformUpdate();
		//�ڽ��� �ִٸ� �ڽĵ��� ����/��������� ����
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



	//���� ��ǥ���� +Z ��ȯ
	float4 GetWorldForwardVector()
	{
		return WorldMatrix.ArrVector[2].NormalizeReturn();
	}

	//���� ��ǥ���� +Y ��ȯ
	float4 GetWorldUpVector()
	{
		return WorldMatrix.ArrVector[1].NormalizeReturn();
	}

	//���� ��ǥ���� +X ��ȯ
	float4 GetWorldRightVector()
	{
		return WorldMatrix.ArrVector[0].NormalizeReturn();
	}


	//���� ��ǥ���� +Z ��ȯ
	float4 GetLocalForwardVector()
	{
		//����� 2���� Return���ش�
		//Forward(Z��)�� ���� 2���� ������
		//����� ������ �Ͼ�� z�� ������� ����Ǵ��� �����ϸ� �� �� �ִ�.
		return LocalWorldMatrix.ArrVector[2].NormalizeReturn();
	}

	//���� ��ǥ���� +Y ��ȯ
	float4 GetLocalUpVector()
	{
		//����� 1���� Return���ش�
		//Up(Y��)�� ���� 1���� ������
		//����� ������ �Ͼ�� y�� ������� ����Ǵ��� �����ϸ� �� �� �ִ�.
		return LocalWorldMatrix.ArrVector[1].NormalizeReturn();
	}

	//���� ��ǥ���� +X ��ȯ
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
		WorldViewProjectionMatrix = WorldMatrix * View * Projection;
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
		//���� �ڽ��� �ִٸ� �ڽ��� ����/���� ��� ����
		//(SetLocal�ȿ��� ���� ��ĵ� �� ����Ѵ�)
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

	//(�θ� ��������)������ǥ
	float4 LocalScale = float4::One;
	float4 LocalRotation = float4::Null;
	float4 LocalPosition = float4::Zero;

	//������ǥ��
	float4 WorldScale = float4::One;
	float4 WorldRotation = float4::Null;
	float4 WorldPosition = float4::Zero;


	float4x4 LocalScaleMatrix;
	float4x4 LocalRotationMatrix;
	float4x4 LocalPositionMatrix;


	//�������(ũ����)
	float4x4 LocalWorldMatrix;

	//�������
	float4x4 WorldMatrix;

	//ī�޶�� ����ɶ� ����ϴ� ����*��*��������*����Ʈ���
	float4x4 WorldViewProjectionMatrix;

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

