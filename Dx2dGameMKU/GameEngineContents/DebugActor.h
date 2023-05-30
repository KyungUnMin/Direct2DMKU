#pragma once
#include <GameEngineCore/GameEngineActor.h>

class DebugActor : public GameEngineActor
{
public:
	DebugActor();
	~DebugActor();

	DebugActor(const DebugActor& _Other) = delete;
	DebugActor(DebugActor&& _Other) noexcept = delete;
	DebugActor& operator=(const DebugActor& _Other) = delete;
	DebugActor& operator=(const DebugActor&& _Other) noexcept = delete;

protected:

private:

};

