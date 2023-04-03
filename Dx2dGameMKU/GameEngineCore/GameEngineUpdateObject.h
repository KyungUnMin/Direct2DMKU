#pragma once
#include "GameEngineObject.h"

class GameEngineUpdateObject : public GameEngineObject
{
public:
	GameEngineUpdateObject();
	~GameEngineUpdateObject() override;

	GameEngineUpdateObject(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject(GameEngineUpdateObject&& _Other) noexcept = delete;
	GameEngineUpdateObject& operator=(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject& operator=(const GameEngineUpdateObject&& _Other) noexcept = delete;

protected:
	virtual void Start(){}
	virtual void Update(float _DeltaTime){}
	virtual void Render(float _DeltaTime){}


private:

};

