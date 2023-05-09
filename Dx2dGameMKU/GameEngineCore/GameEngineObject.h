#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"
#include "GameEngineTransform.h"
#include "GameEngineNameObject.h"

/*
	std::enable_shared_from_this<T>
		�Ϲ����� shared_ptr�� ����Ҷ� RefCount��
		���� ���ִ� �ڷᱸ���� ���� �����Ҵ�ȴ�.
		�̷� RefCount �����Ҵ��� �����̶�
		���� �ϱ� ���� ����� ħ���� shared_ptr�̴�.
		std::enable_shared_from_this<T>�� ��ӽ�Ű��
		std::enable_shared_from_this<T>�� ��� ���� �ȿ��� RefCount�� ī��Ʈ �ϰ� �ȴ�
*/

class GameEngineObject : 
	public GameEngineObjectBase, 
	public GameEngineNameObject,
	public std::enable_shared_from_this<GameEngineObject>
{
	friend class GameEngineLevel;
	friend class GameEngineTransform;

public:
	GameEngineObject();
	virtual ~GameEngineObject() = 0;

	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(const GameEngineObject&& _Other) noexcept = delete;
	
	GameEngineTransform* GetTransform()
	{
		return &Transform;
	}


	/*
		�Ϲ����� �����ʹ� RefCount�� ������ ���� ���Ѵ�
		������ RefCount�� ������ �ִ� Shader_ptr�� ���� ����ؾ� �Ѵ�
	*/
	//�Ϲ����� �����͸� ĳ���õ� Shared_ptr�� ��ȯ��Ű�� ��
	template <typename PtrType>
	std::shared_ptr<PtrType> Shared_This_dynamic_pointer()
	{
		//std::dynamic_pointer_cast<T>�� ����Ҷ� �� �����Լ� ���̺��� ������ �Ѵ�
		return std::dynamic_pointer_cast<PtrType>(std::enable_shared_from_this<GameEngineObject>::shared_from_this());
	}


	virtual void AccLiveTime(float _DeltaTime)
	{
		LiveTime += _DeltaTime;
	}

	void ResetLiveTime()
	{
		LiveTime = 0.f;
	}

	float GetLiveTime()
	{
		return LiveTime;
	}

protected:
	virtual void Start() {}

	//��� Transform�� All~ �迭 �Լ����� ȣ���
	virtual void Update(float _DeltaTime) {}
	virtual void Render(float _DeltaTime) {}
	virtual void Release();

	//protected���� �Լ��� ������� �ʱ� �ٶ���(GameEngineActor�� Component�� ���� ��)
	void PushChild(std::shared_ptr<GameEngineObject> _Child)
	{
		Childs.push_back(_Child);
	}

private:
	float LiveTime = 0.0f;
	GameEngineTransform Transform;

	//������Ʈ ������ �θ� ������(���� ����Ʈ->�θ��� ����Ʈ �̵���)
	//Shared_ptr�� Refī��Ʈ�� ������Ű�� ���� Transform�� Child�ʹ� 
	//������ ���� Object��
	std::list<std::shared_ptr<GameEngineObject>> Childs;
};

