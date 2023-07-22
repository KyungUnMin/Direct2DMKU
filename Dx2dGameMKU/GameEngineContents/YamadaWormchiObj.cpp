#include "PrecompileHeader.h"
#include "YamadaWormchiObj.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "DataMgr.h"

#include "FieldPlayer.h"
#include "AfterImageEffect.h"
#include "FieldLevelBase.h"
#include "BackGround.h"

const std::string_view YamadaWormchiObj::Ani_FileName = "Wormchi_Obj";
const std::string_view YamadaWormchiObj::Light_FileName = "Wormchi_ReleaseLight.png";
const float YamadaWormchiObj::HeightPivot = 100.f;
const int YamadaWormchiObj::Damage = 5;

const float4 YamadaWormchiObj::ObjScale = float4{ 64.f, 64.f, 1.f };
const float4 YamadaWormchiObj::LightScale = float4{ 256.f, 128.f, 1.f };

YamadaWormchiObj::YamadaWormchiObj()
{

}

YamadaWormchiObj::~YamadaWormchiObj()
{
	
}


void YamadaWormchiObj::Start()
{
	FieldActorBase::Start();

	LoadImages();
	CreateRenders();
	SettingCollider();
	MapScale = FieldLevelBase::GetPtr()->GetBackGround()->GetMapScale();

	SetShadowScale(0.5f);
}


void YamadaWormchiObj::LoadImages()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Effect");
	Dir.Move("EnemyAttack");
	Dir.Move("Yamada_Wormchi");
	
	size_t Count = static_cast<size_t>(WormchiObjType::COUNT);
	for (int i = 0; i < Count; ++i)
	{
		std::string Path = Ani_FileName.data() + GameEngineString::ToString(i);
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName(Path).GetFullPath());
	}

	GameEngineTexture::Load(Dir.GetPlusFileName(Light_FileName).GetFullPath());
}

void YamadaWormchiObj::CreateRenders()
{
	std::shared_ptr<GameEngineSpriteRenderer> ObjRender = GetRenderer();
	ObjRender->GetTransform()->SetLocalScale(ObjScale);

	Light = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	Light->SetTexture(Light_FileName);
	Light->ColorOptionValue.MulColor = float4{ 1.f, 1.f, 1.f, 0.5f };
	

	ObjRender->ColorOptionValue.MulColor.a = 0.f;
	Light->Off();
}

void YamadaWormchiObj::SettingCollider()
{
	CreateCollider(CollisionOrder::EnemyAttack);
	std::shared_ptr<GameEngineCollision> Collider = GetAttackCollider();
	Collider->GetTransform()->SetLocalScale(float4::One * 50.f);
}


void YamadaWormchiObj::Init(WormchiObjType _Type)
{
	int Index = static_cast<int>(_Type);
	std::string AniName = Ani_FileName.data() + GameEngineString::ToString(Index);

	std::shared_ptr<GameEngineSpriteRenderer> ObjRender = GetRenderer();
	ObjRender->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniName,
	});

	ObjRender->ChangeAnimation(AniName);
}




void YamadaWormchiObj::Update(float _DeltaTime)
{
	FieldActorBase::Update(_DeltaTime);

	switch (CurState)
	{
	case YamadaWormchiObj::State::Up:
		Update_Up(_DeltaTime);
		break;
	case YamadaWormchiObj::State::Wait:
		Update_Wait(_DeltaTime);
		break;
	case YamadaWormchiObj::State::Move:
		Update_Move(_DeltaTime);
		Update_Shadow();
		break;
	case YamadaWormchiObj::State::Extinct:
		Update_Extinct(_DeltaTime);
		break;
	}
}

void YamadaWormchiObj::Update_Shadow()
{
	float4 Pos  = GetTransform()->GetWorldPosition();
	if (true == GetBackGround()->IsBlockPos(Pos))
	{
		GetShadowRender()->Off();
	}
	else
	{
		GetShadowRender()->On();
	}
}

void YamadaWormchiObj::Update_Up(float _DeltaTime)
{
	static const float Duration = 1.f;

	float Ratio = GetLiveTime() / Duration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	float SinValue = sinf(GameEngineMath::PIE * 0.5f * ClampRatio);

	float4 NowOffset = float4::Lerp(float4::Zero, float4::Up * HeightPivot, SinValue);

	std::shared_ptr<GameEngineSpriteRenderer> ObjRender = GetRenderer();
	GameEngineTransform* ObjTrans = ObjRender->GetTransform();
	ObjTrans->SetLocalPosition(NowOffset);
	ObjRender->ColorOptionValue.MulColor.a = SinValue;

	if (Ratio < 1.f)
		return;

	CurState = State::Wait;
	ResetLiveTime();
}

void YamadaWormchiObj::Update_Wait(float _DeltaTime)
{
	static const float OffsetRange = 10.f;
	static const float CycleRatioForSec = 0.5f;

	float LiveTime = GetLiveTime();
	float SinValue = sinf(GameEngineMath::PIE2 * LiveTime * CycleRatioForSec);
	float NowHeight = HeightPivot + (SinValue * OffsetRange);

	std::shared_ptr<GameEngineSpriteRenderer> ObjRender = GetRenderer();
	GameEngineTransform* ObjTrans = ObjRender->GetTransform();
	ObjTrans->SetLocalPosition(float4::Up * NowHeight);
}


void YamadaWormchiObj::MoveOn()
{
	CurState = State::Move;

	float4 DestPos = FieldPlayer::GetPtr()->GetTransform()->GetWorldPosition();
	float4 StartPos = GetTransform()->GetWorldPosition();
	Dir = (DestPos - StartPos);
	Dir.Normalize();
}



void YamadaWormchiObj::Update_Move(float _DeltaTime) 
{
	static const float Speed = 900.f;

	//맵 밖으로 나갔을때 처리
	GameEngineTransform* ThisTrans = GetTransform();
	float4 NowPos = ThisTrans->GetWorldPosition();
	if (true == CheckMapOut(NowPos))
	{
		Extinct();
		return;
	}

	//이동
	ThisTrans->AddLocalPosition(Dir * Speed * _DeltaTime);

	//충돌
	std::shared_ptr<GameEngineCollision> Collider = GetAttackCollider();
	if(Collider->IsUpdate() && nullptr != Collider->Collision(CollisionOrder::PlayerMain, ColType::SPHERE3D, ColType::SPHERE3D))
	{
		Attack();
		Collider->Off();
	}


	//잔상 효과
	EffectTimer += _DeltaTime;
	if (EffectTimer < EffectTime)
		return;

	EffectTimer = 0.f;

	std::shared_ptr<AfterImageEffect> Effect = nullptr;
	Effect = GetLevel()->CreateActor<AfterImageEffect>(UpdateOrder::Effect);
	std::shared_ptr<GameEngineSpriteRenderer> ObjRender = GetRenderer();
	Effect->Init(ObjRender);

	float4 EffectPos = ObjRender->GetTransform()->GetWorldPosition();
	Effect->GetTransform()->SetWorldPosition(EffectPos);
}





bool YamadaWormchiObj::CheckMapOut(const float4& _Pos)
{
	static const float4 MapArea = MapScale.half();

	if (MapArea.x < _Pos.x)
		return true;

	if (MapArea.y < _Pos.y)
		return true;

	if (_Pos.x < -MapArea.x)
		return true;

	if (_Pos.y < -MapArea.y)
		return true;

	return false;
}



void YamadaWormchiObj::Attack()
{
	std::shared_ptr<FieldPlayer> Player = FieldPlayer::GetPtr();
	float4 ThisPos = GetTransform()->GetWorldPosition();
	Player->Look(ThisPos);

	if (false == Player->OnDamage_BlowBack(Damage))
		return;
	
	
}




void YamadaWormchiObj::Extinct()
{
	CurState = State::Extinct;
	std::shared_ptr<GameEngineSpriteRenderer> ObjRender = GetRenderer();
	ObjRender->Off();
	Light->On();
	GetShadowRender()->Off();
	
	float4 ObjLocalPos = ObjRender->GetTransform()->GetLocalPosition();
	Light->GetTransform()->SetLocalPosition(ObjLocalPos);

	ResetLiveTime();
}


void YamadaWormchiObj::Update_Extinct(float _DeltaTime)
{
	static const float Duration = 0.8f;

	float Ratio = GetLiveTime() / Duration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	float SinValue = sinf(GameEngineMath::PIE * ClampRatio);

	float4 NextScale = float4::Lerp(float4::Zero, LightScale, SinValue);
	Light->GetTransform()->SetLocalScale(NextScale);

	if (Ratio < 1.f)
		return;

	Death();
}
