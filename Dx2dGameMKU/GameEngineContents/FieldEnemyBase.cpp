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


	RendererPtr = CreateComponent<GameEngineSpriteRenderer>();
}

void FieldEnemyBase::Update(float _DeltaTime)
{
	FieldActorBase::Update(_DeltaTime);


}

