#include "PrecompileHeader.h"
#include "FieldEnemyBase.h"

#include <queue>

#include <GameEngineCore/GameEngineSpriteRenderer.h>

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
	RendererPtr = CreateComponent<GameEngineSpriteRenderer>();
	//RendererPtr->GetTransform()->SetLocalScale()
}

void FieldEnemyBase::Update(float _DeltaTime)
{
	FieldActorBase::Update(_DeltaTime);
	Fsm.Update(_DeltaTime);
}

void FieldEnemyBase::Render(float _DeltaTime)
{
	FieldActorBase::Render(_DeltaTime);
	Fsm.Render(_DeltaTime);
}

