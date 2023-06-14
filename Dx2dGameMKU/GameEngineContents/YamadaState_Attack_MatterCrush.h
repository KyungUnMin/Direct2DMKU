#pragma once
#include "BossState_AttackBase.h"

class YamadaState_Attack_MatterCrush : public BossState_AttackBase
{
public:
	YamadaState_Attack_MatterCrush();
	~YamadaState_Attack_MatterCrush() override;

	YamadaState_Attack_MatterCrush(const YamadaState_Attack_MatterCrush& _Other) = delete;
	YamadaState_Attack_MatterCrush(YamadaState_Attack_MatterCrush&& _Other) noexcept = delete;
	YamadaState_Attack_MatterCrush& operator=(const YamadaState_Attack_MatterCrush& _Other) = delete;
	YamadaState_Attack_MatterCrush& operator=(const YamadaState_Attack_MatterCrush&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;


	void Attack() override{}

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;


	void LoadAnimation();
	void CreateAnimation();
};

