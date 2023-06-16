#pragma once
#include "FieldBossBase.h"

#include "YamadaFSM.h"

class FieldEnemy_Yamada : public FieldBossBase
{
public:
	FieldEnemy_Yamada();
	~FieldEnemy_Yamada() override;

	FieldEnemy_Yamada(const FieldEnemy_Yamada& _Other) = delete;
	FieldEnemy_Yamada(FieldEnemy_Yamada&& _Other) noexcept = delete;
	FieldEnemy_Yamada& operator=(const FieldEnemy_Yamada& _Other) = delete;
	FieldEnemy_Yamada& operator=(const FieldEnemy_Yamada&& _Other) noexcept = delete;

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

	YamadaFSM Fsm;

	//3����� ���������� ��Ÿ���� OutLineȿ��
	std::shared_ptr<class GameEngineSpriteRenderer> OutLineRender = nullptr;
	float4 OutLineAtlas = float4::Zero;


	void CreateRageRender();

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

