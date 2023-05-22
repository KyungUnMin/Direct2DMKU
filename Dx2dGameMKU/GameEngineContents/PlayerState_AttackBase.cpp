#include "PrecompileHeader.h"
#include "PlayerState_AttackBase.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "RCGEnums.h"

#include "FieldPlayer.h"
#include "FieldEnemyBase.h"
#include "HitEffect.h"



void PlayerState_AttackBase::CreateHitEffect_Face()
{
	static const float4 Offset = float4::Up * 150.f + float4::Right * 50.f + float4::Back * 100.f;
	CreateHitEffect(Offset);
}

void PlayerState_AttackBase::CreateHitEffect_Stomach()
{
	static const float4 Offset = float4::Up * 100.f + float4::Right * 50.f + float4::Back * 100.f;
	CreateHitEffect(Offset);
}

void PlayerState_AttackBase::CreateHitEffect_Jaw()
{
	static const float4 Offset = float4::Up * 150.f + float4::Right * 100.f + float4::Back * 100.f;
	CreateHitEffect(Offset);
}

void PlayerState_AttackBase::CreateHitEffect_Blow()
{
	static const float4 Offset = float4::Up * 100.f + float4::Right * 50.f + float4::Back * 100.f;
	CreateHitEffect(Offset);
}


void PlayerState_AttackBase::CreateHitEffect(const float4 _Offset)
{
	std::shared_ptr<FieldPlayer> PlayerPtr = FieldPlayer::GetPtr();
	std::shared_ptr<HitEffect> EffectPtr = PlayerPtr->GetLevel()->CreateActor<HitEffect>(UpdateOrder::Effect);
	GameEngineTransform* PlayerTrans = PlayerPtr->GetTransform();
	GameEngineTransform* EffectTrans = EffectPtr->GetTransform();

	EffectTrans->SetParent(PlayerTrans);
	EffectTrans->SetLocalPosition(_Offset);
}







PlayerState_AttackBase::PlayerState_AttackBase()
{

}

PlayerState_AttackBase::~PlayerState_AttackBase()
{

}

void PlayerState_AttackBase::Start()
{
	PlayerStateBase::Start();
	PlayerStateBase::DirChangeOff();

	AttackCollider = FieldPlayer::GetPtr()->GetAttackCollider();
}


void PlayerState_AttackBase::SetAttackCheckFrame(const std::string_view& _AniName, size_t _Index)
{
	std::shared_ptr<GameEngineSpriteRenderer> PlayerRender = GetRenderer();

	//n��° �����ӿ� ó���� �ݹ� ���
	PlayerRender->SetAnimationStartEvent(_AniName, _Index,
		std::bind(&PlayerState_AttackBase::AttackCheck, this));
}

void PlayerState_AttackBase::SetAttackColValue(const float4& _Offset, const float4& _Scale /*= float4{ 100.f, 100.f, 100.f }*/)
{
	GameEngineTransform* AttackColTrans = AttackCollider->GetTransform();

	if (_Scale.z < 5.f)
	{
		MsgAssert("Enemy Attack�� �浹���� ���� �߿� Z���� ������־�� �մϴ�");
		return;
	}

	AttackColTrans->SetLocalPosition(_Offset);
	AttackColTrans->SetLocalScale(_Scale);
}

void PlayerState_AttackBase::AttackCheck()
{
	static std::vector<std::shared_ptr<GameEngineCollision>> EnemyColliders(10, nullptr);
	if (false == AttackCollider->CollisionAll(CollisionOrder::EnemyMain, ColType::SPHERE3D, ColType::SPHERE3D, EnemyColliders))
		return;

	for (std::shared_ptr<GameEngineCollision>& EnemyCollider : EnemyColliders)
	{
		FieldEnemyBase* EnemyPtr = dynamic_cast<FieldEnemyBase*>(EnemyCollider->GetActor());
		if (nullptr == EnemyPtr)
		{
			MsgAssert("CollisionOrder::EnemyMain �浹�׷쿡 FieldEnemyBase�� �ƴ� Actor�� �����ֽ��ϴ�");
			return;
		}

		Attack(EnemyPtr);
	}

	EnemyColliders.clear();
}



