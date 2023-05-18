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

	virtual void OnDamage_Face() = 0;
	virtual void OnDamage_Stomach() = 0;
	virtual void OnDamage_Jaw() = 0;

protected:
	void Start() override;

private:


};

