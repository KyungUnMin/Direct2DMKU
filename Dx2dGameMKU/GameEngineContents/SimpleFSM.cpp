#include "PrecompileHeader.h"
#include "SimpleFSM.h"

SimpleFSM::SimpleFSM()
{

}

SimpleFSM::~SimpleFSM()
{

}

void SimpleFSM::AddState(size_t _Index, const SimpleFSMState& _State)
{
	if (States.size() <= _Index)
	{
		MsgAssert("SimpleFSM 배열의 범위를 넘어간 값에 접근했습니다");
		return;
	}
	
	if (true == States[_Index].Registered)
	{
		MsgAssert("해당 위치에는 다른 State가 이미 존재합니다\nIndex : " + GameEngineString::ToString(static_cast<int>(_Index)));
		return;
	}
	
	States[_Index] = _State;
	States[_Index].Registered = true;
}


void SimpleFSM::ChangeState(size_t _Index)
{
	size_t PrevState = CurState;
	size_t NextState = _Index;
	CurState = _Index;
	StateLiveTime = 0.f;

	if (States.size() <= NextState)
	{
		MsgAssert("SimpleFSM 배열의 범위를 넘어간 값에 접근했습니다");
		return;
	}

	if (false == States[NextState].Registered)
	{
		MsgAssert("해당 위치에는 State를 만들어주지 않았습니다\nIndex : " + GameEngineString::ToString(static_cast<int>(_Index)));
		return;
	}

	//첫 상태 전환이 아닌 경우에만(배열의 인덱스 범위 때문에)
	if ((UINT32_MAX != PrevState) && (nullptr != States[PrevState].ExitCallBack))
	{
		States[PrevState].ExitCallBack();
	}


	if (nullptr != States[NextState].EnterCallBack)
	{
		States[PrevState].EnterCallBack();
	}
}



void SimpleFSM::Update(float _DeltaTime)
{
	if (UINT32_MAX == CurState)
	{
		MsgAssert("SimpleFSM을 시작할 첫 State를 설정해주지 않았습니다");
		return;
	}

	if (nullptr == States[CurState].UpdateCallBack)
		return;

	StateLiveTime += _DeltaTime;
	States[CurState].UpdateCallBack(_DeltaTime);
}
