#include "PrecompileHeader.h"
#include "PlayerState_AttackBase.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "RCGEnums.h"

#include "FieldPlayer.h"
#include "FieldEnemyBase.h"
#include "FieldNPCBase.h"
#include "HitEffect.h"
#include "FieldLevelBase.h"
#include "BackGround.h"
#include "FieldCamController.h"


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

	//ī�޶� ���� ȿ��
	FieldCamController& CamCtrl = FieldLevelBase::GetPtr()->GetCameraController();
	CamCtrl.SetZoom(FieldCamController::ZoomOrigin - 0.01f);
	CamCtrl.SetZoom(FieldCamController::ZoomOrigin, 0.1f);
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

	std::shared_ptr<FieldLevelBase> Level = FieldLevelBase::GetPtr();
	BGPtr = Level->GetBackGround();
	CamCtrl = &(Level->GetCameraController());
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
	AttackCheck_Enemy();
	AttackCheck_NPC();
}


void PlayerState_AttackBase::AttackCheck_Enemy()
{
	static std::vector<std::shared_ptr<GameEngineCollision>> EnemyColliders(10, nullptr);
	if (false == AttackCollider->CollisionAll(CollisionOrder::EnemyMain, EnemyColliders, ColType::SPHERE3D, ColType::SPHERE3D))
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

void PlayerState_AttackBase::AttackCheck_NPC() 
{
	static std::vector<std::shared_ptr<GameEngineCollision>> NpcColliders(10, nullptr);
	if (false == AttackCollider->CollisionAll(CollisionOrder::NPC, NpcColliders, ColType::SPHERE3D, ColType::SPHERE3D))
		return;

	for (std::shared_ptr<GameEngineCollision>& NpcCollider : NpcColliders)
	{
		FieldNPCBase* NpcPtr = dynamic_cast<FieldNPCBase*>(NpcCollider->GetActor());
		if (nullptr == NpcPtr)
		{
			MsgAssert("CollisionOrder::NPC �浹�׷쿡 FieldNPCBase�� �ƴ� Actor�� �����ֽ��ϴ�");
			return;
		}

		NpcPtr->React();
	}

	NpcColliders.clear();
}


void PlayerState_AttackBase::EnterState()
{
	PlayerStateBase::EnterState();
	PlayerDir = FieldPlayer::GetPtr()->IsRightDir();
}


void PlayerState_AttackBase::Update_DashIneria(const float _DeltaTime, const float _Duration, const float _StartAcc /*= 1000.f*/)
{
	GameEngineActor* PlayerActor = GetRenderer()->GetActor();
	GameEngineTransform* PlayerTrans = PlayerActor->GetTransform();

	float LiveTime = GetLiveTime();
	float Ratio = (LiveTime / _Duration);
	if (1.f < Ratio)
		return;


	float NowAcc = _StartAcc * (1.f - Ratio);
	float4 NextPos = PlayerTrans->GetLocalPosition();

	//�������� �ٶ󺸰� ������
	if (true == PlayerDir)
	{
		NextPos += (float4::Right * NowAcc * _DeltaTime);
	}
	//������ �ٶ󺸰� ������
	else
	{
		NextPos += (float4::Left * NowAcc * _DeltaTime);
	}

	//���� ���� ���̸� �������� �ʴ´�
	if (true == BGPtr->IsBlockPos(NextPos))
		return;

	std::pair<int, int> NextGridPos = BGPtr->GetGridFromPos(NextPos);
	if (true == BGPtr->IsBlockGrid(NextGridPos.first, NextGridPos.second))
		return;

	PlayerTrans->SetLocalPosition(NextPos);
}


void PlayerState_AttackBase::Update_QuickAttackMove(float _DeltaTime)
{
	Update_DashIneria(_DeltaTime, 0.1f, 300.f);
}


//������ �� ���µ� ������ ���� ���ܵ�
void PlayerState_AttackBase::Update_Vertical(float _Duration, float _StartHeight /*= 80.f*/)
{
	float LiveTime = GetLiveTime();
	float Ratio = (LiveTime / _Duration);
	Ratio = std::clamp(Ratio, 0.f, 1.f);

	float NowHeight = _StartHeight * (1.f - Ratio);
	FieldPlayer::GetPtr()->SetHeight(NowHeight);
}



void PlayerState_AttackBase::Update_SinVertical(float _Duration, float _MaxHeight /*= 80.f*/)
{
	float LiveTime = GetLiveTime();
	float Ratio = (LiveTime / _Duration);
	Ratio = std::clamp(Ratio, 0.f, 1.f);

	float SinValue = std::sinf(GameEngineMath::PIE * Ratio);

	float NowHeight = _MaxHeight * SinValue;
	FieldPlayer::GetPtr()->SetHeight(NowHeight);
}

void PlayerState_AttackBase::ExitState()
{
	PlayerStateBase::ExitState();
	FieldPlayer::GetPtr()->SetHeight(0.f);
}

