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
		Event�� �ܺο��� TimeEvent�� �����ϴ� ���� ����
		���� Update���� �Ź� �����ϴ� ��찡 ����
		������ ĳ�� ���߷��� ������ ����
		�����Ͱ� �ƴ� �� ������ ������ �ִ�
		(�迭�� �����Ҵ� �Ǿ� ������ ��� ��� �������� ������ ������)
	*/
	std::vector<TimeEvent> Event;
};

