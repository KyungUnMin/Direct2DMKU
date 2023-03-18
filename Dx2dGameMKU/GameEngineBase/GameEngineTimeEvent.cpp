#include "GameEngineTimeEvent.h"

GameEngineTimeEvent::GameEngineTimeEvent()
{

}

GameEngineTimeEvent::~GameEngineTimeEvent()
{

}

void GameEngineTimeEvent::AddEvent(float _Time, std::function<void()> _Event, bool _Loop)
{
	//�⺻�����ڰ� ������
	//���������� ����� �ǵ����ش�
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

		//�ð��� ��� �����ƴٸ�
		if (Event[i].CurTime < 0.0f)
		{
			//�̺�Ʈ ����
			Event[i].Event();

			if (true == Event[i].Loop)
			{
				Event[i].CurTime = Event[i].Time;
			}
		}
	}

}
