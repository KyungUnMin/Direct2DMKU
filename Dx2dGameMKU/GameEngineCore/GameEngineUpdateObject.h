#pragma once
#include "GameEngineObject.h"

class GameEngineUpdateObject : public GameEngineObject
{
	friend class GameEngineLevel;

public:
	GameEngineUpdateObject();
	~GameEngineUpdateObject() override;

	GameEngineUpdateObject(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject(GameEngineUpdateObject&& _Other) noexcept = delete;
	GameEngineUpdateObject& operator=(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject& operator=(const GameEngineUpdateObject&& _Other) noexcept = delete;

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
	virtual void Start(){}
	virtual void Update(float _DeltaTime){}
	virtual void Render(float _DeltaTime){}
	virtual void Release(){}

private:
	float LiveTime = 0.0f;
};

