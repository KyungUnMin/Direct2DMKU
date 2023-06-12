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

	void SetStartHp(int _Hp) override;

	void OnDamage(int _Damege) override;

private:
	static const int MaxHp;

	MisuzuFSM Fsm;


	//ü���� ���� �κ� ���Ϸ� �������� �̹����� �Ӱ� ����� ȿ��
	void RageRender(float _DeltaTime);


	enum class ExceptionType
	{
		DamageOk_StateChanged,
		DamageOk_StateKeep,
		DamageNo,
		NoException
	};

	//true�� ��ȯ�Ǹ� FSM�� ��ȭ��ų �ʿ� ������ �ǹ�
	ExceptionType OnDamageException();
};
