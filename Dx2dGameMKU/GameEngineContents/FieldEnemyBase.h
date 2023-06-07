#pragma once
#include "FieldActorBase.h"

class GameEngineSpriteRenderer;

class FieldEnemyBase : public FieldActorBase
{
	friend class EnemySpawner;

public:
	FieldEnemyBase();
	~FieldEnemyBase() override;

	FieldEnemyBase(const FieldEnemyBase& _Other) = delete;
	FieldEnemyBase(FieldEnemyBase&& _Other) noexcept = delete;
	FieldEnemyBase& operator=(const FieldEnemyBase& _Other) = delete;
	FieldEnemyBase& operator=(const FieldEnemyBase&& _Other) noexcept = delete;

	virtual bool OnDamage_Face(int _Damage) = 0;
	virtual bool OnDamage_Stomach(int _Damage) = 0;
	virtual bool OnDamage_Jaw(int _Damage) = 0;
	virtual bool OnDamage_BlowBack(int _Damage) = 0;


	inline size_t GetSpawnID() const
	{
		return SpawnIdx;
	}

	
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	virtual void OnDamage(int _Damage);

	inline int GetHp() const
	{
		return Hp;
	}


	inline bool IsKO() const
	{
		return IsKOValue;
	}

	void CreateHitEffect(const float4& _Offset = float4::Up * 100.f);

	virtual inline void SetStartHp(int _Hp)
	{
		if (_Hp <= 0)
		{
			MsgAssert("Hp를 0 이하로 세팅할 순 없습니다");
			return;
		}

		Hp = _Hp;
	}



private:
	int Hp = 100;
	bool IsKOValue= false;
	size_t SpawnIdx = -1;


	inline void SetSpawnIdx(size_t _Index)
	{
		SpawnIdx = _Index;
	}
};

