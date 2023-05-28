#pragma once
#include "FieldEnemyBase.h"

#include "WaverFSM.h"

class FieldEnemy_Waver : public FieldEnemyBase
{
public:
	FieldEnemy_Waver();
	~FieldEnemy_Waver() override;

	FieldEnemy_Waver(const FieldEnemy_Waver& _Other) = delete;
	FieldEnemy_Waver(FieldEnemy_Waver&& _Other) noexcept = delete;
	FieldEnemy_Waver& operator=(const FieldEnemy_Waver& _Other) = delete;
	FieldEnemy_Waver& operator=(const FieldEnemy_Waver&& _Other) noexcept = delete;


	bool OnDamage_Face(int _Damage) override;
	bool OnDamage_Stomach(int _Damage) override;
	bool OnDamage_Jaw(int _Damage) override;
	bool OnDamage_BlowBack(int _Damage) override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	void LevelChangeEnd() override;

private:
	WaverFSM Fsm;
};

