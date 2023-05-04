#include "PrecompileHeader.h"
#include "FieldPlayer.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

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

	CreateRender();

	Fsm.Init();
}

void FieldPlayer::CreateRender()
{
	/*std::shared_ptr<GameEngineSpriteRenderer> Shadow = CreateComponent<GameEngineSpriteRenderer>();
	Shadow->SetScaleToTexture("player_shadow.png");*/

	RendererPtr = CreateComponent<GameEngineSpriteRenderer>();
	RendererPtr->SetName("PlayerRender");
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

