#pragma once
#include <functional>
#include <vector>

class GameEngineTimeEvent
{
private:
	class TimeEvent
	{
		friend GameEngineTimeEvent;

		bool IsLive = true;
		float CurTime = 0.0f;
		float Time = 0.0f;

		std::function<void()> Event;
		bool Loop = false;
	};

public:
	GameEngineTimeEvent();
	~GameEngineTimeEvent();

	GameEngineTimeEvent(const GameEngineTimeEvent& _Other) = delete;
	GameEngineTimeEvent(GameEngineTimeEvent&& _Other) noexcept = delete;
	GameEngineTimeEvent& operator=(const GameEngineTimeEvent& _Other) = delete;
	GameEngineTimeEvent& operator=(const GameEngineTimeEvent&& _Other) noexcept = delete;

	void AddEvent(float _Time, std::function<void()> _Event, bool _Loop = false);

	void Update(float _DeltaTime);

private:
	/*
		Event는 외부에서 TimeEvent에 접근하는 일이 없다
		또한 Update에서 매번 접근하는 경우가 잦음
		때문에 캐시 적중률을 높히기 위해
		포인터가 아닌 값 형으로 가지고 있다
		(배열로 동적할당 되어 있으면 노드 방식 구조보다 언제나 빠르다)
	*/
	std::vector<TimeEvent> Event;
};

