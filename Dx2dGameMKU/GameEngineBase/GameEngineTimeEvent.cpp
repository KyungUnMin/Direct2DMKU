#include "GameEngineTimeEvent.h"

GameEngineTimeEvent::GameEngineTimeEvent()
{

}

GameEngineTimeEvent::~GameEngineTimeEvent()
{

}

void GameEngineTimeEvent::AddEvent(float _Time, std::function<void()> _Event, bool _Loop)
{
	//기본생성자가 있을때
	//내부적으로 만들고 되돌려준다
	TimeEvent& NewEvent = Event.emplace_back();

	NewEvent.CurTime = _Time;
	NewEvent.Time = _Time;
	NewEvent.Loop = _Loop;
	NewEvent.Event = _Event;
}

void GameEngineTimeEvent::Update(float _DeltaTime)
{
	for (size_t i = 0; i < Event.size(); ++i)
	{
		Event[i].CurTime -= _DeltaTime;

		//시간이 모두 소진됐다면
		if (Event[i].CurTime < 0.0f)
		{
			//이벤트 실행
			Event[i].Event();

			if (true == Event[i].Loop)
			{
				Event[i].CurTime = Event[i].Time;
			}
		}
	}

}
