#include "PrecompileHeader.h"
#include "FieldEnemy_SchoolGirl.h"

#include "RCG_GameCore.h"
#include "RCGDefine.h"


FieldEnemy_SchoolGirl::FieldEnemy_SchoolGirl()
{

}

FieldEnemy_SchoolGirl::~FieldEnemy_SchoolGirl()
{

}

void FieldEnemy_SchoolGirl::Start()
{
	FieldEnemyBase::Start();

	Fsm.Init(this);
}

void FieldEnemy_SchoolGirl::Update(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldEnemyBase::Update(_DeltaTime);

	Fsm.Update(_DeltaTime);
}

void FieldEnemy_SchoolGirl::Render(float _DeltaTime)
{
	if (GameState::OnField != RCG_GameCore::GetCurGameState())
		return;

	FieldEnemyBase::Render(_DeltaTime);
	Fsm.Render(_DeltaTime);
}

void FieldEnemy_SchoolGirl::OnDamage_Face(int _Damage)
{

}

void FieldEnemy_SchoolGirl::OnDamage_Stomach(int _Damage)
{

}

void FieldEnemy_SchoolGirl::OnDamage_Jaw(int _Damage)
{

}
