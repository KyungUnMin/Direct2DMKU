#include "PrecompileHeader.h"
#include "FSMBase.h"
#include "StateBase.h"


FSMBase::FSMBase()
{
}

FSMBase::~FSMBase()
{
	AllState.clear();
}



void FSMBase::InitState(std::shared_ptr<StateBase> _State, size_t _Index)
{
	if (AllState.size() <= _Index)
	{
		MsgAssert("설정해주려는 State가 벡터의 범위를 넘어갔습니다.\n ResizeStates함수를 호출해주어야 합니다");
		return;
	}

	if (nullptr != AllState[_Index])
	{
		MsgAssert("해당 위치에는 이미 다른 State가 존재합니다\n enum값을 확인해보세요");
		return;
	}

	_State->FsmPtr = this;
	_State->Start();
	AllState[_Index] = _State;
}



void FSMBase::Update(float _DeltaTime)
{
	if (AllState.size() <= CurIndex)
	{
		MsgAssert("현재 FSM의 상태를 설정해주지 않았습니다");
		return;
	}

	AllState[CurIndex]->Update(_DeltaTime);
}

void FSMBase::Render(float _DeltaTime)
{
	if (AllState.size() <= CurIndex)
	{
		MsgAssert("현재 FSM의 상태를 설정해주지 않았습니다");
		return;
	}

	AllState[CurIndex]->Render(_DeltaTime);
}




void FSMBase::ChangeState(size_t _NextIndex)
{
	//자식에서 Resize를 해주지 않음
	if (AllState.size() <= _NextIndex)
	{
		MsgAssert("FSM에 등록한 State의 범위를 넘어서 접근하였습니다");
		return;
	}

	//이전 상태값 찾기
	std::shared_ptr<StateBase>  PrevState = nullptr;
	if (CurIndex < AllState.size())
	{
		PrevState = AllState[CurIndex];
	}

	//다음 상태값 찾기
	std::shared_ptr<StateBase>  NextState = AllState[_NextIndex];
	if (nullptr == NextState)
	{
		MsgAssert("바꾸려는 배틀 State를 만들어준 적이 없습니다");
		return;
	}

	//현재 상태값 교체
	CurIndex = _NextIndex;

	//이전 상태값이 존재했다면 Exit호출
	if (nullptr != PrevState)
	{
		PrevState->ExitState();
	}

	//다음 상태값에 Enter호출
	NextState->EnterState();
}
