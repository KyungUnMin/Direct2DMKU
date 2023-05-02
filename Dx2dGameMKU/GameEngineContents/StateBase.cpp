#include "PrecompileHeader.h"
#include "StateBase.h"

StateBase::StateBase()
{

}

StateBase::~StateBase()
{

}

void StateBase::EnterState()
{
	Timer = 0.f;
}

void StateBase::Update(float _DeltaTime)
{
	Timer += _DeltaTime;
}
