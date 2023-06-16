#include "PrecompileHeader.h"
#include "YamadaMatterDust.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "DataMgr.h"
#include "FieldCamController.h"

#include "FieldPlayer.h"
#include "FieldLevelBase.h"

const std::string_view YamadaMatterDust::CircleEffect_FileName = "Yamada_MatterCrush_BlockEffect1.png";
const std::string_view YamadaMatterDust::Explo_FileName = "Yamada_MatterCrush_BlockEffect2.png";
const float4 YamadaMatterDust::ExploScale = { 512.f, 512.f, 1.f };
const float4 YamadaMatterDust::ExploOffset = { 0.f, 200.f, -10.f };
const int YamadaMatterDust::Damage = 10;

YamadaMatterDust::YamadaMatterDust()
{
	
}

YamadaMatterDust::~YamadaMatterDust()
{

}

void YamadaMatterDust::Start()
{
	GameEngineActor::Start();

	LoadSheet();
	CreateRenders();
	CreateCollider();
	CamCtrl = &(FieldLevelBase::GetPtr()->GetCameraController());
}


void YamadaMatterDust::LoadSheet()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Effect");
	Dir.Move("EnemyAttack");
	Dir.Move("Yamada_MatterCrushBlocks");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(Explo_FileName).GetFullPath(), 4, 2);
}



void YamadaMatterDust::CreateRenders()
{
	//폭발 이펙트
	Explo = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	Explo->CreateAnimation
	({
		.AnimationName = Explo_FileName,
		.SpriteName = Explo_FileName,
		.FrameInter = 0.08f,
		.Loop = false,
		});
	Explo->ChangeAnimation(Explo_FileName);

	GameEngineTransform* ExploTrans = Explo->GetTransform();
	ExploTrans->SetLocalScale(ExploScale);
	ExploTrans->SetLocalPosition(ExploOffset);


	CircleEffect = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	CircleEffect->SetTexture(CircleEffect_FileName);

	CircleEffectScale = GameEngineTexture::Find(CircleEffect_FileName)->GetScale();
	CircleEffect->GetTransform()->SetLocalPosition(float4::Up * 100.f + float4::Back * 100.f);
	CircleEffect->Off();
}


void YamadaMatterDust::CreateCollider()
{
	Collider = CreateComponent<GameEngineCollision>(CollisionOrder::EnemyAttack);
	Collider->GetTransform()->SetLocalScale(float4::One * 100.f);
}



void YamadaMatterDust::Update(float _DeltaTime)
{
	GameEngineActor::Update(_DeltaTime);

	CheckColWithPlayer();

	if (Explo->IsUpdate() && true == Explo->IsAnimationEnd())
	{
		Explo->Off();
	}

	float Ratio = GetLiveTime() / Duration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	float SinValue = sinf(GameEngineMath::PIE * 0.5f * ClampRatio);

	float4 NowEffectScale = float4::Lerp(float4::Zero, CircleEffectScale, SinValue);
	CircleEffect->GetTransform()->SetLocalScale(NowEffectScale);
	CircleEffect->ColorOptionValue.MulColor.a = (1.f - SinValue);

	if (Ratio < 1.f)
		return;

	if (true == Explo->IsUpdate())
		return;

	Death();
}




void YamadaMatterDust::CheckColWithPlayer()
{
	if (nullptr == Collider)
		return;

	//업데이트 첫 프레임 한 순간만 충돌 체크
	std::shared_ptr<GameEngineCollision> PlayerCol = nullptr;
	PlayerCol = Collider->Collision(CollisionOrder::PlayerMain, ColType::SPHERE3D, ColType::SPHERE3D);
	Collider->Off();
	Collider->Death();
	Collider = nullptr;

	if (nullptr == PlayerCol)
		return;

	Attack();
}

void YamadaMatterDust::Attack()
{
	bool AttackResult = FieldPlayer::GetPtr()->OnDamage_Stun(true, true);
	if (false == AttackResult)
		return;

	CamCtrl->SetZoom(0.95f);
	CamCtrl->SetZoom(CamCtrl->ZoomOrigin, 0.5f);
	CircleEffect->On();
	DataMgr::MinusPlayerHP(Damage);
}


