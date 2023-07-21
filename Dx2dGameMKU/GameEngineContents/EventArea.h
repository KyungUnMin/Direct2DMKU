#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineCollision;

class EventArea : public GameEngineActor
{
public:
	EventArea();
	~EventArea() override;

	EventArea(const EventArea& _Other) = delete;
	EventArea(EventArea&& _Other) noexcept = delete;
	EventArea& operator=(const EventArea& _Other) = delete;
	EventArea& operator=(const EventArea&& _Other) noexcept = delete;

	inline void Init(std::function<void()> _CallBack)
	{
		CallBack = _CallBack;
	}

	void Init_Tutorial(
		const std::string_view& _TutoTitle,
		const std::string_view& _TutoDesc);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineCollision> Collider = nullptr;
	std::function<void()> CallBack = nullptr;
};

