#pragma once
#include "FieldEnemyBase.h"

#include "TigerManFSM.h"

class FieldEnemy_TigerMan : public FieldEnemyBase
{
public:
	FieldEnemy_TigerMan();
	~FieldEnemy_TigerMan() override;

	FieldEnemy_TigerMan(const FieldEnemy_TigerMan& _Other) = delete;
	FieldEnemy_TigerMan(FieldEnemy_TigerMan&& _Other) noexcept = delete;
	FieldEnemy_TigerMan& operator=(const FieldEnemy_TigerMan& _Other) = delete;
	FieldEnemy_TigerMan& operator=(const FieldEnemy_TigerMan&& _Other) noexcept = delete;


	bool OnDamage_Face(int _Damage) override;
	bool OnDamage_Stomach(int _Damage) override;
	bool OnDamage_Jaw(int _Damage) override;
	bool OnDamage_BlowBack(int _Damage) override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;


private:
	TigerManFSM Fsm;
};

