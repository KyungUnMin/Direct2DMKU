#pragma once
#include "BossState_AttackBase.h"

class NoiseState_Attack_WUPunch : public BossState_AttackBase
{
public:
	NoiseState_Attack_WUPunch();
	~NoiseState_Attack_WUPunch() override;

	NoiseState_Attack_WUPunch(const NoiseState_Attack_WUPunch& _Other) = delete;
	NoiseState_Attack_WUPunch(NoiseState_Attack_WUPunch&& _Other) noexcept = delete;
	NoiseState_Attack_WUPunch& operator=(const NoiseState_Attack_WUPunch& _Other) = delete;
	NoiseState_Attack_WUPunch& operator=(const NoiseState_Attack_WUPunch&& _Other) noexcept = delete;

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
	static const int AttackFrm;

	bool IsAttackHited = false;
	std::shared_ptr<class GameEngineSpriteRenderer> OutLineRender = nullptr;
	float4 OutLineAtlas = float4::Zero;

	void LoadAnimation();
	void CreateAnimation();
	void CreateOutLine();

	void Update_OutLine();
};

