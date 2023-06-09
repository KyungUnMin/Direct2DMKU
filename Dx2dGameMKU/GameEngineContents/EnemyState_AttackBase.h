#pragma once
#include "EnemyStateBase.h"

#include "RCGEnums.h"
#include "FieldLevelBase.h"

class FieldEnemyBase;
class GameEngineCollision;

class EnemyState_AttackBase : public EnemyStateBase
{
public:
	static const FieldEnemyBase* const IsAttackAnyone()
	{
		return AttackEnemy;
	}

	EnemyState_AttackBase();
	~EnemyState_AttackBase() override;

	EnemyState_AttackBase(const EnemyState_AttackBase& _Other) = delete;
	EnemyState_AttackBase(EnemyState_AttackBase&& _Other) noexcept = delete;
	EnemyState_AttackBase& operator=(const EnemyState_AttackBase& _Other) = delete;
	EnemyState_AttackBase& operator=(const EnemyState_AttackBase&& _Other) noexcept = delete;

	void MoveOn()
	{
		IsMovingAttack = true;
		MoveStartTime = GetLiveTime();
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

	//_AniName �ִϸ��̼�, _Index��° �����ӿ� �÷��̾�� �浹 üũ�� �ϰڴ�
	void SetAttackCheckFrame(const std::string_view& _AniName, size_t _Index, bool _IsUpdateCallBack = false);

	//�� Enemy�� Collision Transform �� ����
	void SetAttackColValue(const float4& _Offset = float4{50.f, 0.f, 0.f}, const float4& _Scale = float4{100.f, 100.f, 100.f});


	bool AttackCheck();

	//�÷��̾�� �浹������ ó���ؾ� �ϴ� ��Ȳ
	virtual void Attack() = 0;



	void SetMoveEvent(const std::string_view& _AniName, size_t _MoveStartFrame,
		bool _IsReverseDir = false, float _MoveDuration = 0.5f, float _StartAcc = 1000.f);



	inline std::shared_ptr<GameEngineCollision> GetAttackCollider() const
	{
		return AttackCollider;
	}

	template<typename EffectType>
	std::shared_ptr<EffectType> CreateEffect(const float4& _Offset = float4::Zero, const float4& _Scale = float4::One, bool _IsChild = false)
	{
		std::shared_ptr<EffectType> Effect = nullptr;
		Effect = FieldLevelBase::GetPtr()->CreateActor<EffectType>(UpdateOrder::Effect);
		EffectInit(Effect, _Offset, _Scale, _IsChild);
		return Effect;
	}


	inline FieldCamController* GetCamCtrl() const
	{
		return CamCtrl;
	}

private:
	//���� ������ �ϰ� �ִ� Enemy(��� Enemy�� �߿� �Ѹ� ���ݽ�Ű�� ����)
	static FieldEnemyBase* AttackEnemy;

	std::shared_ptr<GameEngineCollision> AttackCollider = nullptr;
	class FieldCamController* CamCtrl = nullptr;

	//True�� ������, false�� ����
	bool EnemyDir = false;

	//�����̴� ���ݿ���
	bool IsMovingAttack = false;
	//�����̴� �����϶� ���������� �����̴��� ����
	bool IsReverseMoveDir = false;

	//�����̴� �����϶� ���� �ӵ�
	float StartAcc = 1000.f;
	//�����̱� ������ �ð�
	float MoveStartTime = 0.0f;

	float MoveDuration = 0.5f;

	void EffectInit(std::shared_ptr<GameEngineActor> _Effect, const float4& _Offset, const float4& _Scale, bool _IsChild);
};

