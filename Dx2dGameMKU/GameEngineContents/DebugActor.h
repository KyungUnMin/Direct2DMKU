#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;

class DebugActor : public GameEngineActor
{
public:
	DebugActor();
	~DebugActor();

	DebugActor(const DebugActor& _Other) = delete;
	DebugActor(DebugActor&& _Other) noexcept = delete;
	DebugActor& operator=(const DebugActor& _Other) = delete;
	DebugActor& operator=(const DebugActor&& _Other) noexcept = delete;

	void Init_PositionPointer(const std::string_view& _TexName = "");

protected:

private:
	static const float4 PositionPointerColor; /*= float4{ 1.f, 0.f ,1.f, 1.f };*/
	std::shared_ptr<GameEngineSpriteRenderer> PositionPointerRender = nullptr;
};

