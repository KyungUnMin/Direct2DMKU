#pragma once
#include "EnemyFSMBase.h"

enum class WaverStateType
{
	//Movement
	Idle,
	Walk,
	//Ready,

	//Attack
	AxeKick,
	Elbow,
	Punch,
	SideKick,

	//Damaged
	NormalDamaged_Face,
	NormalDamaged_Stomach,
	NormalDamaged_Jaw,
	Damaged_BlowBack,
	Damaged_KnockDown,
	Damaged_WallHit,
	Damaged_WallOut,
	Damaged_Dazed,


	COUNT
};

class WaverFSM : public EnemyFSMBase
{
public:
	static const std::string_view NormalDamaged_FileName;

	WaverFSM();
	~WaverFSM() override;

	WaverFSM(const WaverFSM& _Other) = delete;
	WaverFSM(WaverFSM&& _Other) noexcept = delete;
	WaverFSM& operator=(const WaverFSM& _Other) = delete;
	WaverFSM& operator=(const WaverFSM&& _Other) noexcept = delete;

	size_t GetRandomAttack() override;
	
	void Init(class FieldEnemyBase* _Enemy) override;

	


protected:

private:
	static const std::vector<WaverStateType> AttackGroup;



};

