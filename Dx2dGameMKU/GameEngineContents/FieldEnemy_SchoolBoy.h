#pragma once
#include "FieldEnemyBase.h"

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
	void Update(float _DelatTime) override;

private:

};

/*
	Enemy는 플레이어와는 다르게
	Actor에서 애니메이션을 만들자
	그리고 FSM에서는 애니메이션 교체만
*/