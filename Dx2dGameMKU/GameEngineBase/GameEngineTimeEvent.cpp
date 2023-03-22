#include "GameEngineTimeEvent.h"

GameEngineTimeEvent::GameEngineTimeEvent()
{

}

GameEngineTimeEvent::~GameEngineTimeEvent()
{

}

void GameEngineTimeEvent::AddEvent(float _Time, std::function<void(TimeEvent&, GameEngineTimeEvent*)> _Event, bool _Loop)
{
	//기본생성자가 있을때
	//내부적으로 만들고 되돌려준다
	TimeEvent& NewEvent = Events.emplace_back();

	NewEvent.CurTime = _Time;
	NewEvent.Time = _Time;
	NewEvent.Loop = _Loop;
	NewEvent.Event = _Event;
}

void GameEngineTimeEvent::Update(float _DeltaTime)
{
	std::list<TimeEvent>::iterator StartIter = Events.begin();
	std::list<TimeEvent>::iterator EndIter = Events.end();

	for ( ; StartIter != EndIter ; )
	{
		TimeEvent& CurEvent = (*StartIter);

		//시간이 경과했을때
		CurEvent.CurTime -= _DeltaTime;
		if (CurEvent.CurTime < 0.0f)
		{
			CurEvent.Event(CurEvent, this);
			CurEvent.CurTime = CurEvent.Time;

			//반복재생이 아닐때 그 이벤트 삭제 
			if (false == CurEvent.Loop)
			{
				StartIter = Events.erase(StartIter);
				continue;
			}
		}

		++StartIter;
	}
}

/*
* [사용법]
		(레벨의 멤버함수)
			TimeEvent.AddEvent(5.0f, std::bind(&TestLevel::TestFunc, this), true);

		(람다 이용)
		(두번째로 호출될 이벤트의 람다를 이용한 functional)
			std::function<void(GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)> Test0 =
				[](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
			{
				MsgTextBox("도주");
			};

		(첫번째로 호출될 이벤트의 람다를 이용한 functional)
			std::function<void(GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)> Test =
				[=](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
			{
				MsgTextBox("공격");

				//첫번째 이벤트 끝남과 동시에 두번째 이벤트 등록(캡쳐를 이용한 Test0접근)
				_Manager->AddEvent(3.0f, Test0, false);
			};

		(첫번째 이벤트 등록)
			 TimeEvent.AddEvent(3.0f, Test, false);
*/