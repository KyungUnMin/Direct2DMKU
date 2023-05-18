#include "PrecompileHeader.h"
#include "FieldEnemy_SchoolBoy.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCG_GameCore.h"
#include "RCGDefine.h"



FieldEnemy_SchoolBoy::FieldEnemy_SchoolBoy()
{

}

FieldEnemy_SchoolBoy::~FieldEnemy_SchoolBoy()
{

}



void FieldEnemy_SchoolBoy::Start()
{
	FieldEnemyBase::Start();
	Fsm.Init(this);
}

void FieldEnemy_SchoolBoy::SitDown()
{
	Fsm.ChangeState(SchoolBoyStateType::Ready);
}


void FieldEnemy_SchoolBoy::Update(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldEnemyBase::Update(_DeltaTime);

	Fsm.Update(_DeltaTime);
}

void FieldEnemy_SchoolBoy::Render(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldEnemyBase::Render(_DeltaTime);

	Fsm.Render(_DeltaTime);
}


