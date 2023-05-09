#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"
#include "GameEngineTransform.h"
#include "GameEngineNameObject.h"

/*
	std::enable_shared_from_this<T>
		일반적인 shared_ptr을 사용할때 RefCount를
		따로 세주는 자료구조도 같이 동적할당된다.
		이런 RefCount 동적할당을 조금이라도
		적게 하기 위한 방법이 침습형 shared_ptr이다.
		std::enable_shared_from_this<T>를 상속시키면
		std::enable_shared_from_this<T>의 멤버 변수 안에서 RefCount를 카운트 하게 된다
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
		일반적인 포인터는 RefCount에 영향을 주지 못한다
		때문에 RefCount에 영향을 주는 Shader_ptr을 만들어서 사용해야 한다
	*/
	//일반적인 포인터를 캐스팅된 Shared_ptr로 변환시키는 것
	template <typename PtrType>
	std::shared_ptr<PtrType> Shared_This_dynamic_pointer()
	{
		//std::dynamic_pointer_cast<T>를 사용할때 꼭 가상함수 테이블을 만들어야 한다
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

	//모두 Transform의 All~ 계열 함수에서 호출됨
	virtual void Update(float _DeltaTime) {}
	virtual void Render(float _DeltaTime) {}
	virtual void Release();

	//protected지만 함수로 사용하지 않기 바란다(GameEngineActor의 Component를 위한 것)
	void PushChild(std::shared_ptr<GameEngineObject> _Child)
	{
		Childs.push_back(_Child);
	}

private:
	float LiveTime = 0.0f;
	GameEngineTransform Transform;

	//컴포넌트 생성과 부모 설정시(레벨 리스트->부모의 리스트 이동시)
	//Shared_ptr의 Ref카운트를 유지시키기 위해 Transform의 Child와는 
	//별도로 갖는 Object값
	std::list<std::shared_ptr<GameEngineObject>> Childs;
};

