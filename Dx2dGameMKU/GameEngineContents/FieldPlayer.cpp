#include "PrecompileHeader.h"
#include "FieldPlayer.h"

FieldPlayer* FieldPlayer::GPtr = nullptr;

FieldPlayer::FieldPlayer()
{
	GPtr = this;
}

FieldPlayer::~FieldPlayer()
{
	if (this == GPtr)
	{
		GPtr = nullptr;
	}
}


void FieldPlayer::Start()
{
	FieldActorBase::Start();

	Fsm.Init();
}

void FieldPlayer::Update(float _DeltaTime) 
{
	FieldActorBase::Update(_DeltaTime);

	Fsm.Update(_DeltaTime);
}

void FieldPlayer::Render(float _DeltaTime)
{
	FieldActorBase::Render(_DeltaTime);

	Fsm.Render(_DeltaTime);
}
