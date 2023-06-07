#pragma once
#include "FieldBossBase.h"

#include "MisuzuFSM.h"

class FieldEnemy_Misuzu : public FieldBossBase
{
public:
	FieldEnemy_Misuzu();
	~FieldEnemy_Misuzu() override;

	FieldEnemy_Misuzu(const FieldEnemy_Misuzu& _Other) = delete;
	FieldEnemy_Misuzu(FieldEnemy_Misuzu&& _Other) noexcept = delete;
	FieldEnemy_Misuzu& operator=(const FieldEnemy_Misuzu& _Other) = delete;
	FieldEnemy_Misuzu& operator=(const FieldEnemy_Misuzu&& _Other) noexcept = delete;

	bool OnDamage_Face(int _Damage) override;
	bool OnDamage_Stomach(int _Damage) override;
	bool OnDamage_Jaw(int _Damage) override;
	bool OnDamage_BlowBack(int _Damage) override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	void LevelChangeEnd() override;

private:
	MisuzuFSM Fsm;
	const int RageHpLine = 30;

	//체력이 일정 부분 이하로 떨어지면 이미지가 붉게 물드는 효과
	void RageRender(float _DeltaTime);
};

