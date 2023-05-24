#pragma once
#include "EnemyFSMBase.h"

enum class CheerleaderStateType
{
	//Movement
	Idle,
	Walk,
	//Ready,
	CartWheel,


	//Attack
	BackFlip,
	DoublePom,
	Jab,
	SpinPom,


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

class CheerleaderFSM : public EnemyFSMBase
{
public:
	static const std::string_view NormalDamaged_FileName;

	CheerleaderFSM();
	~CheerleaderFSM() override;

	CheerleaderFSM(const CheerleaderFSM& _Other) = delete;
	CheerleaderFSM(CheerleaderFSM&& _Other) noexcept = delete;
	CheerleaderFSM& operator=(const CheerleaderFSM& _Other) = delete;
	CheerleaderFSM& operator=(const CheerleaderFSM&& _Other) noexcept = delete;

	static CheerleaderStateType GetRandomAttack();
	
	void Init(class FieldEnemyBase* _Enemy) override;

	


protected:

private:
	static const std::vector<CheerleaderStateType> AttackGroup;



};

