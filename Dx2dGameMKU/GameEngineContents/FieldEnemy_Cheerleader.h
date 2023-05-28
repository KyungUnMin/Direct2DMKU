#pragma once
#include "FieldEnemyBase.h"

#include "CheerleaderFSM.h"

class FieldEnemy_Cheerleader : public FieldEnemyBase
{
public:
	FieldEnemy_Cheerleader();
	~FieldEnemy_Cheerleader() override;

	FieldEnemy_Cheerleader(const FieldEnemy_Cheerleader& _Other) = delete;
	FieldEnemy_Cheerleader(FieldEnemy_Cheerleader&& _Other) noexcept = delete;
	FieldEnemy_Cheerleader& operator=(const FieldEnemy_Cheerleader& _Other) = delete;
	FieldEnemy_Cheerleader& operator=(const FieldEnemy_Cheerleader&& _Other) noexcept = delete;

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
	CheerleaderFSM Fsm;
};

