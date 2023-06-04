#pragma once
#include "FieldEnemyBase.h"

class FieldBossBase : public FieldEnemyBase
{
public:
	FieldBossBase();
	virtual ~FieldBossBase() = 0;

	FieldBossBase(const FieldBossBase& _Other) = delete;
	FieldBossBase(FieldBossBase&& _Other) noexcept = delete;
	FieldBossBase& operator=(const FieldBossBase& _Other) = delete;
	FieldBossBase& operator=(const FieldBossBase&& _Other) noexcept = delete;

protected:
	void Start() override;

	bool OnDamage(int _Damege) override;

private:
	static const float4 RenderScale;

	std::shared_ptr<class BossHUD> HpBar = nullptr;
};

