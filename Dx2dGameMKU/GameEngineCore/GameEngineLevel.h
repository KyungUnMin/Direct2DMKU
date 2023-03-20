#pragma once
#include <GameEngineBase/GameEngineTimeEvent.h>
#include "GameEngineObject.h"

/*
GameEngineObject�� �����״�, ����, �ڽ� �������� ����ε�
�� ������ ������Ʈ�� ��ӹ�����?
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

