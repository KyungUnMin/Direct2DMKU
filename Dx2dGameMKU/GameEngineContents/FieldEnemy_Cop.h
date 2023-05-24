#pragma once
#include "FieldEnemyBase.h"

#include "CopFSM.h"

class FieldEnemy_Cop : public FieldEnemyBase
{
public:
	FieldEnemy_Cop();
	~FieldEnemy_Cop() override;

	FieldEnemy_Cop(const FieldEnemy_Cop& _Other) = delete;
	FieldEnemy_Cop(FieldEnemy_Cop&& _Other) noexcept = delete;
	FieldEnemy_Cop& operator=(const FieldEnemy_Cop& _Other) = delete;
	FieldEnemy_Cop& operator=(const FieldEnemy_Cop&& _Other) noexcept = delete;

	void SitDown();

	bool OnDamage_Face(int _Damage) override;
	bool OnDamage_Stomach(int _Damage) override;
	bool OnDamage_Jaw(int _Damage) override;
	bool OnDamage_BlowBack(int _Damage) override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;


private:
	CopFSM Fsm;
};
