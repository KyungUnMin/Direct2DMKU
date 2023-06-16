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

	//해당 위치를 바라보면서 다음 Fsm State의 ChangeRenderDirection가 계산되지 않는다
	void Look(const float4& _LookPos) override;

	inline bool IsDirRegist()
	{
		bool Return = IsDirRegistValue;
		IsDirRegistValue = false;
		return Return;
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

	//외부에서 바라볼 방향을 예약했는지 여부(true라면  Fsm State의 ChangeRenderDirection가 계산되지 않는다)
	bool IsDirRegistValue = false;


	inline void SetSpawnIdx(size_t _Index)
	{
		SpawnIdx = _Index;
	}
};

