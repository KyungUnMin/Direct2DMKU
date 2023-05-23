#pragma once
#include "EnemyFSMBase.h"

enum class TigerManStateType
{
	//Movement
	Idle,
	Walk,
	Ready,

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

class TigerManFSM : public EnemyFSMBase
{
public:
	static const std::string_view NormalDamaged_FileName;

	TigerManFSM();
	~TigerManFSM() override;

	TigerManFSM(const TigerManFSM& _Other) = delete;
	TigerManFSM(TigerManFSM&& _Other) noexcept = delete;
	TigerManFSM& operator=(const TigerManFSM& _Other) = delete;
	TigerManFSM& operator=(const TigerManFSM&& _Other) noexcept = delete;

	static TigerManStateType GetRandomAttack();
	
	void Init(class FieldEnemyBase* _Enemy) override;

	


protected:

private:
	static const std::vector<TigerManStateType> AttackGroup;



};

