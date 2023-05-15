#pragma once
#include "EnemyFSMBase.h"

enum class SchoolGirlStateType
{
	Idle,
	Walk,

	COUNT
};

class SchoolGirlFSM : public EnemyFSMBase
{
public:
	SchoolGirlFSM();
	~SchoolGirlFSM();

	SchoolGirlFSM(const SchoolGirlFSM& _Other) = delete;
	SchoolGirlFSM(SchoolGirlFSM&& _Other) noexcept = delete;
	SchoolGirlFSM& operator=(const SchoolGirlFSM& _Other) = delete;
	SchoolGirlFSM& operator=(const SchoolGirlFSM&& _Other) noexcept = delete;

	void Init(class FieldEnemyBase* _Enemy) override;

protected:

private:

};

