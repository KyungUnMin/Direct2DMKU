#include "GameEngineTimeEvent.h"

GameEngineTimeEvent::GameEngineTimeEvent()
{

}

GameEngineTimeEvent::~GameEngineTimeEvent()
{

}

void GameEngineTimeEvent::AddEvent(float _Time, std::function<void(TimeEvent&, GameEngineTimeEvent*)> _Event, bool _Loop)
{
	//�⺻�����ڰ� ������
	//���������� ����� �ǵ����ش�
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

		//�ð��� ���������
		CurEvent.CurTime -= _DeltaTime;
		if (CurEvent.CurTime < 0.0f)
		{
			CurEvent.Event(CurEvent, this);
			CurEvent.CurTime = CurEvent.Time;

			//�ݺ������ �ƴҶ� �� �̺�Ʈ ���� 
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
* [����]
		(������ ����Լ�)
			TimeEvent.AddEvent(5.0f, std::bind(&TestLevel::TestFunc, this), true);

		(���� �̿�)
		(�ι�°�� ȣ��� �̺�Ʈ�� ���ٸ� �̿��� functional)
			std::function<void(GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)> Test0 =
				[](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
			{
				MsgTextBox("����");
			};

		(ù��°�� ȣ��� �̺�Ʈ�� ���ٸ� �̿��� functional)
			std::function<void(GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)> Test =
				[=](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
			{
				MsgTextBox("����");

				//ù��° �̺�Ʈ ������ ���ÿ� �ι�° �̺�Ʈ ���(ĸ�ĸ� �̿��� Test0����)
				_Manager->AddEvent(3.0f, Test0, false);
			};

		(ù��° �̺�Ʈ ���)
			 TimeEvent.AddEvent(3.0f, Test, false);
*/