#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"
#include "GameEngineTransform.h"
#include "GameEngineNameObject.h"

class GameEngineObject : public GameEngineObjectBase, public GameEngineNameObject
{
	friend class GameEngineLevel;

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

protected:

private:

private:
	GameEngineTransform Transform;
};

