#pragma once
#include "EnemyFSMBase.h"

enum class SchoolBoyStateType
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

	COUNT
};

class SchoolBoyFSM : public EnemyFSMBase
{
public:
	SchoolBoyFSM();
	~SchoolBoyFSM() override;

	SchoolBoyFSM(const SchoolBoyFSM& _Other) = delete;
	SchoolBoyFSM(SchoolBoyFSM&& _Other) noexcept = delete;
	SchoolBoyFSM& operator=(const SchoolBoyFSM& _Other) = delete;
	SchoolBoyFSM& operator=(const SchoolBoyFSM&& _Other) noexcept = delete;

	void Init(class FieldEnemyBase* _Enemy) override;

	


protected:

private:

};

