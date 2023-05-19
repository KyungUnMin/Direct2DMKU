#pragma once
#include "FieldActorBase.h"

class GameEngineSpriteRenderer;

class FieldEnemyBase : public FieldActorBase
{
public:
	FieldEnemyBase();
	~FieldEnemyBase() override;

	FieldEnemyBase(const FieldEnemyBase& _Other) = delete;
	FieldEnemyBase(FieldEnemyBase&& _Other) noexcept = delete;
	FieldEnemyBase& operator=(const FieldEnemyBase& _Other) = delete;
	FieldEnemyBase& operator=(const FieldEnemyBase&& _Other) noexcept = delete;

	virtual void OnDamage_Face(int _Damage) = 0;
	virtual void OnDamage_Stomach(int _Damage) = 0;
	virtual void OnDamage_Jaw(int _Damage) = 0;
	virtual void OnDamage_BlowBack(int _Damage) = 0;

protected:
	void Start() override;

	inline int GetHp() const
	{
		return Hp;
	}

	void OnDamage(int _Damage);

	inline bool IsKO() const
	{
		return IsKOValue;
	}

private:
	int Hp = 100;
	bool IsKOValue= false;
};

