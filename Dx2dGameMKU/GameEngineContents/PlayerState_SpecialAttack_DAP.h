#pragma once
#include "PlayerState_AttackBase.h"

class PlayerState_SpecialAttack_DAP : public PlayerState_AttackBase
{
public:
	PlayerState_SpecialAttack_DAP();
	~PlayerState_SpecialAttack_DAP() override;

	PlayerState_SpecialAttack_DAP(const PlayerState_SpecialAttack_DAP& _Other) = delete;
	PlayerState_SpecialAttack_DAP(PlayerState_SpecialAttack_DAP&& _Other) noexcept = delete;
	PlayerState_SpecialAttack_DAP& operator=(const PlayerState_SpecialAttack_DAP& _Other) = delete;
	PlayerState_SpecialAttack_DAP& operator=(const PlayerState_SpecialAttack_DAP&& _Other) noexcept = delete;

	inline void EffectEnd()
	{
		EffectOnValue = false;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

	void Attack(class FieldEnemyBase* _Enemy) override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;
	static const size_t EffectCount;
	static const int Damage;

	std::vector<std::shared_ptr<class DapEffect>> Effects;
	const float EffectTime = 0.05f;
	size_t Cursor = 0;

	int TotalDamage = 0;
	bool EffectOnValue = false;

	void LoadAnimation();
	void CreateAnimation();
	void CreateEffect();
};

