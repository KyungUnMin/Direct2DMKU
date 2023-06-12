#pragma once
#include "BossState_AttackBase.h"

class YamadaState_Attack_Elbow : public BossState_AttackBase
{
public:
	YamadaState_Attack_Elbow();
	~YamadaState_Attack_Elbow() override;

	YamadaState_Attack_Elbow(const YamadaState_Attack_Elbow& _Other) = delete;
	YamadaState_Attack_Elbow(YamadaState_Attack_Elbow&& _Other) noexcept = delete;
	YamadaState_Attack_Elbow& operator=(const YamadaState_Attack_Elbow& _Other) = delete;
	YamadaState_Attack_Elbow& operator=(const YamadaState_Attack_Elbow&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

	void Attack() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;
	static const int Damage;

	void LoadAnimation();
	void CreateAnimation();
};

