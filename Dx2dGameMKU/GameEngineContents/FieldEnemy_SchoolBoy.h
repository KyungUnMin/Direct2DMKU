#pragma once
#include "FieldEnemyBase.h"

/*
	Enemy�� �÷��̾�ʹ� �ٸ���
	Actor���� �ִϸ��̼��� ������
	�׸��� FSM������ �ִϸ��̼� ��ü��
*/

class FieldEnemy_SchoolBoy : public FieldEnemyBase
{
public:
	FieldEnemy_SchoolBoy();
	~FieldEnemy_SchoolBoy() override;

	FieldEnemy_SchoolBoy(const FieldEnemy_SchoolBoy& _Other) = delete;
	FieldEnemy_SchoolBoy(FieldEnemy_SchoolBoy&& _Other) noexcept = delete;
	FieldEnemy_SchoolBoy& operator=(const FieldEnemy_SchoolBoy& _Other) = delete;
	FieldEnemy_SchoolBoy& operator=(const FieldEnemy_SchoolBoy&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

	void LoadImages();
	void CreateAnimations();



	//------------------FSM----------

	void CreateFsmStates();

	bool IdleCallBack();
};

