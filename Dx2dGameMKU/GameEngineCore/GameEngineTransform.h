#pragma once
#include <list>
#include <memory>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"

struct TransformData
{
	//(�θ� ��������)������ǥ
	float4 LocalScale;
	float4 LocalRotation;
	Quaternion LocalQuaternion;
	float4 LocalPosition;

	//������ǥ��
	float4 WorldScale;
	float4 WorldRotation;
	Quaternion WorldQuaternion;
	float4 WorldPosition;


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

	//ī�޶�� ����ɶ� ����ϴ� ����*��*��������*����Ʈ���
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

	//���� �����Ͽ� ���� ���� �Է��ϰ� ���� �������� ����ķ� ����Ѵ�
	void SetWorldScale(const float4& _Value)
	{
		TransData.WorldScale = _Value;

		//���� �ֻ��� �θ��� ���
		if (nullptr == Parent)
		{
			TransData.LocalScale = TransData.WorldScale;
		}
		else
		{
			//���彺���� * �θ��� �����
			TransData.LocalScale = TransData.WorldScale * Parent->GetWorldMatrixRef().InverseReturn();
		}

		//���� ��������Ƿ� ���� �������, ���� ��������� �ٽ� ���
		TransformUpdate();
		//�ڽ��� �ִٸ� �ڽĵ��� ����/��������� ����
		CalChild();
	}

	
	void SetWorldRotation(const float4& _Value)
	{
		TransData.WorldRotation = _Value;

		//���� �ֻ��� �θ��� ���
		if (nullptr == Parent)
		{
			TransData.LocalRotation = TransData.WorldRotation;
		}
		else
		{
			//ȸ���� ������
			//���� ����(0,0,0)ȸ���̰�
			//�θ� ����(10, 0, 0)ȸ���̸�
			//��������� �� ����ȸ���� (-10, 0, 0)�� �ȴ�
			//�ٵ� �ȵȴ�, �ϴ��� ���߿� ��������
			TransData.LocalRotation = TransData.WorldRotation - Parent->GetWorldRotation();
		}

		//���� ��������Ƿ� ���� �������, ���� ��������� �ٽ� ���
		TransformUpdate();
		//�ڽ��� �ִٸ� �ڽĵ��� ����/��������� ����
		CalChild();
	}

	//���� �����ǿ� ���� ���� �Է��ϰ� ���� �������� ����ķ� ����Ѵ�
	void SetWorldPosition(const float4& _Value)
	{
		TransData.WorldPosition = _Value;

		//���� �ֻ��� �θ��� ���
		if (nullptr == Parent)
		{
			TransData.LocalPosition = TransData.WorldPosition;
		}
		else
		{
			TransData.LocalPosition = TransData.WorldPosition * Parent->GetWorldMatrixRef().InverseReturn();
		}

		//���� ��������Ƿ� ���� �������, ���� ��������� �ٽ� ���
		TransformUpdate();
		//�ڽ��� �ִٸ� �ڽĵ��� ����/��������� ����
		CalChild();
	}


	void SetLocalScale(const float4& _Value)
	{
		TransData.LocalScale = _Value;

		//���� �ֻ��� �θ��� ���
		if (nullptr == Parent)
		{
			TransData.WorldScale = TransData.LocalScale;
		}
		else
		{
			TransData.WorldScale = TransData.LocalScale * Parent->GetWorldMatrixRef();
		}

		//���� ��������Ƿ� ���� �������, ���� ��������� �ٽ� ���
		TransformUpdate();
		//�ڽ��� �ִٸ� �ڽĵ��� ����/��������� ����
		CalChild();
	}

	//���ð��� �����Ҷ����� �� ����Ѵ�
	void SetLocalRotation(const float4& _Value)
	{
		TransData.LocalRotation = _Value;

		//�ֻ��� �θ��� ���
		if (nullptr == Parent)
		{
			TransData.WorldRotation = TransData.LocalRotation;
		}
		else
		{
			//ȸ���� ������
			//���� ����(10,0,0)ȸ���̰�
			//�θ� ����(10, 0, 0)ȸ���̸�
			//��������� �� ����ȸ���� (20, 0, 0)�� �ȴ�
			TransData.WorldRotation = TransData.LocalRotation + Parent->GetWorldRotation();
		}

		//���� ��������Ƿ� ���� �������, ���� ��������� �ٽ� ���
		TransformUpdate();
		//�ڽ��� �ִٸ� �ڽĵ��� ����/��������� ����
		CalChild();
	}

	//���ð��� �����Ҷ����� �� ����Ѵ�
	void SetLocalPosition(const float4& _Value)
	{
		TransData.LocalPosition = _Value;

		//�ֻ��� �θ��� ���
		if (nullptr == Parent)
		{
			TransData.WorldPosition = TransData.LocalPosition;
		}
		else
		{
			//ȸ���� ������
			//���� ����(10,0,0)ȸ���̰�
			//�θ� ����(10, 0, 0)ȸ���̸�
			//��������� �� ����ȸ���� (20, 0, 0)�� �ȴ�
			TransData.WorldPosition = TransData.LocalPosition * Parent->GetWorldMatrixRef();
		}

		//���� ��������Ƿ� ���� �������, ���� ��������� �ٽ� ���
		TransformUpdate();
		//�ڽ��� �ִٸ� �ڽĵ��� ����/��������� ����
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
		TransData.WorldMatrix *= TransData.ViewPort;
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

	const TransformData& GetTransDataRef()
	{
		return TransData;
	}

	void SetTransformData(const TransformData& _Data)
	{
		TransData = _Data;
	}


	//LocalScale�� X�� ������Ī�̵�(�̹��� �¿� ������ ���)
	void SetLocalFlipScaleX()
	{
		TransData.LocalScale.x = -TransData.LocalScale.x;
		SetLocalScale(TransData.LocalScale);
	}

	//LocalScale�� X�� �׻� ����������(�̹��� ���� ������ ���)
	void SetLocalNegativeScaleX()
	{
		if (0 < TransData.LocalScale.x)
		{
			SetLocalFlipScaleX();
			return;
		}

		return;
	}

	//LocalScale�� X�� �׻� ���������(�̹��� ���� ������ ���)
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


	//�θ� �ڽ� ����
	GameEngineTransform* Parent = nullptr;
	std::list<GameEngineTransform*> Child;
};

