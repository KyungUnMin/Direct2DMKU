#include "PrecompileHeader.h"
#include "FieldPlayer.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "KeyMgr.h"

FieldPlayer* FieldPlayer::GPtr = nullptr;

FieldPlayer::FieldPlayer()
{
	//Start부분을 위해 여기서도 설정
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
