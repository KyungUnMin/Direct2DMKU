#pragma once
#include "FieldEnemyBase.h"

#include "SchoolBoyFSM.h"

class FieldEnemy_SchoolBoy : public FieldEnemyBase
{
public:
	FieldEnemy_SchoolBoy();
	~FieldEnemy_SchoolBoy() override;

	FieldEnemy_SchoolBoy(const FieldEnemy_SchoolBoy& _Other) = delete;
	FieldEnemy_SchoolBoy(FieldEnemy_SchoolBoy&& _Other) noexcept = delete;
	FieldEnemy_SchoolBoy& operator=(const FieldEnemy_SchoolBoy& _Other) = delete;
	FieldEnemy_SchoolBoy& operator=(const FieldEnemy_SchoolBoy&& _Other) noexcept = delete;

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
	SchoolBoyFSM Fsm;
};

