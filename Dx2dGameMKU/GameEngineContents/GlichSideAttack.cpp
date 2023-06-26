#include "PrecompileHeader.h"
#include "GlichSideAttack.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "RCGDefine.h"
#include "RCGEnums.h"
#include "DataMgr.h"
#include "FieldCamController.h"

#include "FieldPlayer.h"
#include "FieldLevelBase.h"


const float4 GlichSideAttack::RenderScale = float4{ 550.f, 180.f, 1.f };
const float4 GlichSideAttack::CollisionScale = float4{ 1500.f, 200.f, 30.f };
const int GlichSideAttack::Damage = 15;

GlichSideAttack::GlichSideAttack()
{

}

GlichSideAttack::~GlichSideAttack()
{

}


void GlichSideAttack::Init(const float4& _Pos)
{
	GameEngineTransform* ThisTrans = GetTransform();
	ThisTrans->SetLocalPosition(_Pos);

	
	const float TopY = -60.f;
	const float BottomY = -445.f;
	const float RangeY = fabs(BottomY - TopY);

	//인자로 받은 위치의 Y값의 TopY 와 BottomY 사이 비율
	float YRatio = fabs(_Pos.y - TopY);
	YRatio = (YRatio / RangeY);

	CreateRenders(YRatio);
	CreateCollider();

	CamCtrl = &(FieldLevelBase::GetPtr()->GetCameraController());
	CamCtrl->SetZoom(CamCtrl->ZoomOrigin - 0.15f);
	CamCtrl->SetZoom(CamCtrl->ZoomOrigin, 0.5f);
	CamCtrl->SetShakeState(0.5f);
}


void GlichSideAttack::CreateRenders(float _YRatio)
{
	const float MaxWidth = 645.f;
	const float MinWidth = 500.f;
	float NowWidth = (MinWidth * (1.f - _YRatio)) + (MaxWidth * _YRatio);

	float4 ThisRenderScale = RenderScale;
	ThisRenderScale.x = NowWidth;
	

	//왼쪽
	std::shared_ptr<GameEngineRenderer> Render1 = CreateComponent<GameEngineRenderer>(FieldRenderOrder::ZOrder);
	Render1->SetMesh("Rect");
	Render1->SetPipeLine(RCGDefine::GetPipeName(PipeType::GlichStair));
	Render1->GetShaderResHelper().SetConstantBufferLink("GlichData", Data);

	float4 Render1LocalPos = { -ThisRenderScale.hx(), ThisRenderScale.hy() };
	Render1->GetTransform()->SetLocalScale(ThisRenderScale);
	Render1->GetTransform()->AddLocalPosition(Render1LocalPos);



	//오른쪽
	std::shared_ptr<GameEngineRenderer> Render2 = CreateComponent<GameEngineRenderer>(FieldRenderOrder::ZOrder);
	Render2->SetMesh("Rect");
	Render2->SetPipeLine(RCGDefine::GetPipeName(PipeType::GlichStair));
	Render2->GetShaderResHelper().SetConstantBufferLink("GlichData", Data);

	float4 Render2LocalPos = { ThisRenderScale.hx(), ThisRenderScale.hy() };
	Render2->GetTransform()->SetLocalScale(ThisRenderScale * float4{ -1.f, 1.f, 1.f });
	Render2->GetTransform()->AddLocalPosition(Render2LocalPos);
}



void GlichSideAttack::CreateCollider()
{
	AttackCollider = CreateComponent<GameEngineCollision>(CollisionOrder::EnemyAttack);
	AttackCollider->SetColType(ColType::AABBBOX3D);

	GameEngineTransform* ColTrans = AttackCollider->GetTransform();
	ColTrans->SetLocalScale(CollisionScale);
	ColTrans->SetLocalPosition(float4::Up * CollisionScale.hy());
}



void GlichSideAttack::Update(float _DeltaTime)
{
	if (nullptr == AttackCollider)
	{
		MsgAssert("Init함수를 호출시켜주지 않았습니다");
		return;
	}

	Data.Timer += _DeltaTime;

	Update_Collider();
	Update_WaveOff(_DeltaTime);
}

void GlichSideAttack::Update_Collider()
{
	std::shared_ptr<FieldPlayer> Player = FieldPlayer::GetPtr();
	if (0.f < Player->GetHeight())
		return;

	float LiveTime = GetLiveTime();
	if (LiveTime < (LastAttackTime + 0.5f))
		return;

	if (nullptr == AttackCollider->Collision(CollisionOrder::PlayerMain, ColType::AABBBOX3D, ColType::SPHERE3D))
		return;


	LastAttackTime = LiveTime;
	if (false == Player->OnDamage_BlowBack())
		return;

	CamCtrl->SetShakeState(0.5f);

	LastAttackTime = (LiveTime + 2.5f);
	Player->Look(float4::Zero);
	DataMgr::MinusPlayerHP(Damage);
}

void GlichSideAttack::Update_WaveOff(float _DeltaTime) 
{
	if (false == WaveOffValue)
		return;

	DecreaseTimer += _DeltaTime;

	float Ratio = (DecreaseTimer / DecreseDuration);
	if (1.f < Ratio)
	{
		Death();
		return;
	}

	Data.MaxWaveHeight = (1.f - Ratio);

	static const float4 DestColScale = float4{ CollisionScale.x, 0.f, 0.f };
	float4 NowColScale = float4::LerpClamp(CollisionScale, DestColScale, Ratio);
	AttackCollider->GetTransform()->SetLocalScale(NowColScale);
}
