#pragma once
#include "FieldEnemyBase.h"

#include "HooliganFSM.h"

class FieldEnemy_Hooligan : public FieldEnemyBase
{
public:
	FieldEnemy_Hooligan();
	~FieldEnemy_Hooligan() override;

	FieldEnemy_Hooligan(const FieldEnemy_Hooligan& _Other) = delete;
	FieldEnemy_Hooligan(FieldEnemy_Hooligan&& _Other) noexcept = delete;
	FieldEnemy_Hooligan& operator=(const FieldEnemy_Hooligan& _Other) = delete;
	FieldEnemy_Hooligan& operator=(const FieldEnemy_Hooligan&& _Other) noexcept = delete;

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
	HooliganFSM Fsm;
};

