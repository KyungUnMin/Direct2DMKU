#include "TestLevel.h"
#include <GameEngineBase/GameEngineDebug.h>

TestLevel::TestLevel()
{

}

TestLevel::~TestLevel()
{

}

void TestLevel::Loading()
{
	TimeEvent.AddEvent(1.f, [] {MsgTextBox("�̺�Ʈ ����")}, true);
}
