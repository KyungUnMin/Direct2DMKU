#pragma once
#include "FieldEnemyBase.h"

#include "SchoolGirlFSM.h"

class FieldEnemy_SchoolGirl : public FieldEnemyBase
{
public:
	FieldEnemy_SchoolGirl();
	~FieldEnemy_SchoolGirl();

	FieldEnemy_SchoolGirl(const FieldEnemy_SchoolGirl& _Other) = delete;
	FieldEnemy_SchoolGirl(FieldEnemy_SchoolGirl&& _Other) noexcept = delete;
	FieldEnemy_SchoolGirl& operator=(const FieldEnemy_SchoolGirl& _Other) = delete;
	FieldEnemy_SchoolGirl& operator=(const FieldEnemy_SchoolGirl&& _Other) noexcept = delete;

	void OnDamage_Face(int _Damage) override;
	void OnDamage_Stomach(int _Damage) override;
	void OnDamage_Jaw(int _Damage) override;
	void OnDamage_BlowBack(int _Damage) override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	SchoolGirlFSM Fsm;
};

