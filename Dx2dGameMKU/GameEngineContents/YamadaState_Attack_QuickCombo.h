#pragma once
#include "BossState_AttackBase.h"

class YamadaState_Attack_QuickCombo : public BossState_AttackBase
{
public:
	YamadaState_Attack_QuickCombo();
	~YamadaState_Attack_QuickCombo() override;

	YamadaState_Attack_QuickCombo(const YamadaState_Attack_QuickCombo& _Other) = delete;
	YamadaState_Attack_QuickCombo(YamadaState_Attack_QuickCombo&& _Other) noexcept = delete;
	YamadaState_Attack_QuickCombo& operator=(const YamadaState_Attack_QuickCombo& _Other) = delete;
	YamadaState_Attack_QuickCombo& operator=(const YamadaState_Attack_QuickCombo&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

	void Attack() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;
	static const int Damage;

	static const std::string_view EffectName;
	static const float4 EffectScale;

	std::shared_ptr<class GameEngineSpriteRenderer> Effect = nullptr;

	void LoadAnimation();
	void CreateAnimation();
	void CreateAttackEffect();
};

