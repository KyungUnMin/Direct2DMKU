#pragma once
#include "FSMBase.h"

enum class PlayerStateType
{
	//Movement
	Movement_Idle,
	Movement_Walk,
	Movement_Jump,
	Movement_Fall,
	Movement_Dash,
	Movement_Avoid,

	//Quick Attack
	QuickAttack_Chop,
	QuickAttack_SnapKick,
	QuickAttack_BackKick,
	QuickAttack_HookKick,
	QuickAttack_CrescentKick,

	//Special Attack
	SpecialAttack_AxeKick,
	SpecialAttack_DAP,
	SpecialAttack_DonkeyKick,
	

	//Unique Attack
	UniqueAttack_DragonFeet,
	UniqueAttack_HyrricaneKick,


	//Dash Attack
	DashAttack_BackElbow,
	DashAttack_DropKick,


	//Damaged
	NormalDamaged_Face,
	NormalDamaged_Stomach,
	NormalDamaged_Jaw,
	Damaged_BlowBack,
	Damaged_Block,
	Damaged_Stun,



	COUNT
};

class PlayerFSM : public FSMBase
{
public:
	PlayerFSM();
	~PlayerFSM() override;

	PlayerFSM(const PlayerFSM& _Other) = delete;
	PlayerFSM(PlayerFSM&& _Other) noexcept = delete;
	PlayerFSM& operator=(const PlayerFSM& _Other) = delete;
	PlayerFSM& operator=(const PlayerFSM&& _Other) noexcept = delete;

	void Init(PlayerStateType _StartState = PlayerStateType::Movement_Idle);

	//�������� Walk������ Dash������ Ȯ���ϱ� ���� override��
	void ChangeState(size_t _NextIndex) override;
	
	inline PlayerStateType GetLastMovement() const
	{
		return LastMoveState;
	}

	//�÷��̾ ����߿� ������ �޾Ҵ��� ����
	bool OnDamageInBlock();

protected:


private:
	//Move�� Dash�� ��� ���������� ����Ǿ�����
	PlayerStateType LastMoveState = PlayerStateType::Movement_Idle;
};

