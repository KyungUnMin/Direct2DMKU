#include "PrecompileHeader.h"
#include "BossVersusState_Wait.h"

#include "BossVersus.h"

BossVersusState_Wait::BossVersusState_Wait()
{

}

BossVersusState_Wait::~BossVersusState_Wait()
{

}

void BossVersusState_Wait::EnterState()
{
	StateBase::EnterState();

	//TODO
}

void BossVersusState_Wait::Update(float _DeltaTime)
{
	StateBase::Update(_DeltaTime);

	if (GetLiveTime() < Duration)
		return;

	//TODO
	BossVersus::GetPtr()->Death();
}
