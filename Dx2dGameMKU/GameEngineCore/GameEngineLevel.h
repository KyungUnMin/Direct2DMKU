#pragma once
#include <GameEngineBase/GameEngineTimeEvent.h>
#include "GameEngineObject.h"

/*
GameEngineObject는 껏다켰다, 삭제, 자식 가지기의 기능인데
왜 레벨이 오브젝트를 상속받을까?
*/

class GameEngineLevel : public GameEngineObject
{
	friend class GameEngineCore;

public:
	GameEngineTimeEvent TimeEvent;

	GameEngineLevel();
	virtual ~GameEngineLevel();

	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(const GameEngineLevel&& _Other) noexcept = delete;

protected:
	virtual void Loading() = 0;

private:

};

