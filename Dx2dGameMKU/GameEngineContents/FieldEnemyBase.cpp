#include "PrecompileHeader.h"
#include "FieldEnemyBase.h"


#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCG_GameCore.h"

FieldEnemyBase::FieldEnemyBase()
{

}

FieldEnemyBase::~FieldEnemyBase()
{

}

void FieldEnemyBase::Start()
{
	FieldActorBase::Start();

	Fsm.Init(this);
	//RendererPtr->GetTransform()->SetLocalScale()
}

#include "FieldPlayer.h"

void FieldEnemyBase::Update(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;
	
	FieldActorBase::Update(_DeltaTime);
	Fsm.Update(_DeltaTime);
}

void FieldEnemyBase::Render(float _DeltaTime)
{
	FieldActorBase::Render(_DeltaTime);
	Fsm.Render(_DeltaTime);
}

