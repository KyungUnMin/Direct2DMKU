#pragma once
#include "EnemyState_AttackBase.h"

class MisuzuState_Attack_WUPunch : public EnemyState_AttackBase
{
public:
	MisuzuState_Attack_WUPunch();
	~MisuzuState_Attack_WUPunch() override;

	MisuzuState_Attack_WUPunch(const MisuzuState_Attack_WUPunch& _Other) = delete;
	MisuzuState_Attack_WUPunch(MisuzuState_Attack_WUPunch&& _Other) noexcept = delete;
	MisuzuState_Attack_WUPunch& operator=(const MisuzuState_Attack_WUPunch& _Other) = delete;
	MisuzuState_Attack_WUPunch& operator=(const MisuzuState_Attack_WUPunch&& _Other) noexcept = delete;

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

	class FieldCamController* CamCtrl = nullptr;
	bool IsAttackHited = false;

	void LoadAnimation();
	void CreateAnimation();
};

