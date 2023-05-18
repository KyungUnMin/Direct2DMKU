#pragma once
#include "PlayerState_AttackBase.h"

class PlayerState_SpecialAttack_Stomp : public PlayerState_AttackBase
{
public:
	PlayerState_SpecialAttack_Stomp();
	~PlayerState_SpecialAttack_Stomp() override;

	PlayerState_SpecialAttack_Stomp(const PlayerState_SpecialAttack_Stomp& _Other) = delete;
	PlayerState_SpecialAttack_Stomp(PlayerState_SpecialAttack_Stomp&& _Other) noexcept = delete;
	PlayerState_SpecialAttack_Stomp& operator=(const PlayerState_SpecialAttack_Stomp& _Other) = delete;
	PlayerState_SpecialAttack_Stomp& operator=(const PlayerState_SpecialAttack_Stomp&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

	void Attack(class FieldEnemyBase* _Enemy) override
	{
		int a = 0;
	}

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	void LoadAnimation();
	void CreateAnimation();
};

