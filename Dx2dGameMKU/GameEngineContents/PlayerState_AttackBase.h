#pragma once
#include "PlayerStateBase.h"
#include "DataMgr.h"

class PlayerState_AttackBase : public PlayerStateBase
{
public:
	PlayerState_AttackBase();
	~PlayerState_AttackBase() override;

	PlayerState_AttackBase(const PlayerState_AttackBase& _Other) = delete;
	PlayerState_AttackBase(PlayerState_AttackBase&& _Other) noexcept = delete;
	PlayerState_AttackBase& operator=(const PlayerState_AttackBase& _Other) = delete;
	PlayerState_AttackBase& operator=(const PlayerState_AttackBase&& _Other) noexcept = delete;

	static void CreateHitEffect_Face();
	static void CreateHitEffect_Stomach();
	static void CreateHitEffect_Jaw();
	static void CreateHitEffect_Blow();
	static void CreateHitEffect(const float4 _Offset);

protected:
	void Start() override;
	void EnterState() override;
	void ExitState() override;
	

	//_AniName �ִϸ��̼�, _Index��° �����ӿ� �÷��̾�� �浹 üũ�� �ϰڴ�
	void SetAttackCheckFrame(const std::string_view& _AniName, size_t _Index);

	
	//�� Player�� Collision Transform �� ����
	void SetAttackColValue(const float4& _Offset = float4{50.f, 0.f, 0.f}, const float4& _Scale = float4{ 100.f, 100.f, 100.f });


	//���� �浹������ ó���ؾ� �ϴ� ��Ȳ
	virtual void Attack(class FieldEnemyBase* _Enemy) = 0;


	void Update_DashIneria(const float _DeltaTime, const float _Duration, const float _StartAcc = 1000.f);

	void Update_Vertical(float _Duration, float _StartHeight = 80.f);

	void Update_SinVertical(float _Duration, float _MaxHeight = 80.f);

private:
	std::shared_ptr<class GameEngineCollision> AttackCollider = nullptr;

	//�������϶� true, �����϶� false
	bool PlayerDir = true;
	std::shared_ptr<class BackGround> BGPtr = nullptr;


	class FieldCamController* CamCtrl = nullptr;

	void AttackCheck();
	void AttackCheck_Enemy();
	void AttackCheck_NPC();
};

