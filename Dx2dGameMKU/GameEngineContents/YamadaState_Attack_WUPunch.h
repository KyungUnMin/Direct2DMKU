#pragma once
#include "BossState_AttackBase.h"

class YamadaState_Attack_WUPunch : public BossState_AttackBase
{
public:
	YamadaState_Attack_WUPunch();
	~YamadaState_Attack_WUPunch() override;

	YamadaState_Attack_WUPunch(const YamadaState_Attack_WUPunch& _Other) = delete;
	YamadaState_Attack_WUPunch(YamadaState_Attack_WUPunch&& _Other) noexcept = delete;
	YamadaState_Attack_WUPunch& operator=(const YamadaState_Attack_WUPunch& _Other) = delete;
	YamadaState_Attack_WUPunch& operator=(const YamadaState_Attack_WUPunch&& _Other) noexcept = delete;

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

