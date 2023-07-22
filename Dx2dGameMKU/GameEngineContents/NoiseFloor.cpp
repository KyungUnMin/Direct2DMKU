#include "PrecompileHeader.h"
#include "NoiseFloor.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "DataMgr.h"
#include "SoundMgr.h"

#include "FieldPlayer.h"
#include "FieldLevelBase.h"
#include "FieldCamController.h"


size_t NoiseFloor::RunCount = 0;

const std::vector<std::string_view> NoiseFloor::FileNames =
{
	"Noise_Floor_Red.png",
	"Noise_Floor_Yellow.png",
	"Noise_Floor_Blue.png",
	"Noise_Floor_Pupple.png",
	"Noise_Floor_Green.png",
	"Noise_Floor_Pink.png",

	"Noise_FloorSpawnEffect.png",
	"Noise_FloorDestroyLight.png",
	"Noise_FloorHitEffect.png",
};


const std::vector<std::pair<float4, float4>> NoiseFloor::MovePath =
{
	{float4{-407.f, -73.f, -73.f}, float4{-511.f, -414.f, -414.f}},
	{float4{-240.f, -73.f, -73.f}, float4{-300.f, -414.f, -414.f}},
	{float4{-86.f, -73.f, -73.f}, float4{-111.f, -414.f, -414.f}},
	{float4{81.f, -73.f, -73.f}, float4{105.f, -414.f, -414.f}},
	{float4{244.f, -73.f, -73.f}, float4{305.f, -414.f, -414.f}},
	{float4{402.f, -73.f, -73.f}, float4{511.f, -414.f, -414.f}},
};

const int NoiseFloor::Damage = 3;

const std::vector<std::string_view> NoiseFloor::HitSfx_FileNames =
{
	"NoiseFloor_Effect1.wav",
	"NoiseFloor_Effect2.wav",
	"NoiseFloor_Effect3.wav",
	"NoiseFloor_Effect4.wav"
};


NoiseFloor::NoiseFloor()
{
	++RunCount;
}

NoiseFloor::~NoiseFloor()
{
	--RunCount;
}



void NoiseFloor::Start()
{
	FieldActorBase::Start();
	GetShadowRender()->GetTransform()->AddLocalPosition(float4::Down * 20.f);
	ImageLoad();

	CreateCollider(CollisionOrder::EnemyAttack);
	std::shared_ptr<GameEngineCollision> AttackCollider = GetAttackCollider();
	AttackCollider->GetTransform()->SetLocalScale({ 120.f, 30.f, 30.f });
	AttackCollider->SetColType(ColType::AABBBOX3D);

	GetRenderer()->GetTransform()->SetLocalScale({ 120.f, 30.f, 1.f });
	CreateEffects();
}

void NoiseFloor::ImageLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Effect");
	Dir.Move("EnemyAttack");
	Dir.Move("Noise_Floor");

	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}

	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(FileNames[6]).GetFullPath(), 4, 2);
}


void NoiseFloor::CreateEffects()
{
	const float4 SpawnScale = float4{ 512.f, 256.f, 1.f };
	const float4 DestroyScale = float4{ 128.f, 128.f, 1.f };
	const float4 HitScale = float4{ 256.f, 512.f, 1.f };
	GameEngineTransform* EffectTrans = nullptr;
		

	const std::string_view& SpawnAniName = FileNames[6];
	SpawnEffect = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	SpawnEffect->CreateAnimation
	({
		.AnimationName = SpawnAniName,
		.SpriteName = SpawnAniName,
		.Loop = false,
	});
	SpawnEffect->ChangeAnimation(SpawnAniName);
	EffectTrans = SpawnEffect->GetTransform();
	EffectTrans->SetLocalScale(SpawnScale);
	EffectTrans->SetLocalPosition(float4::Up * SpawnScale.hy());


	DestroyLight = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	DestroyLight->SetTexture(FileNames[7]);
	EffectTrans = DestroyLight->GetTransform();
	EffectTrans->SetLocalScale(DestroyScale);



	HitEffect = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	HitEffect->SetTexture(FileNames[8]);
	EffectTrans = HitEffect->GetTransform();
	EffectTrans->SetLocalScale(HitScale);
	EffectTrans->SetLocalPosition(float4::Up * HitScale.hy());

	DestroyLight->Off();
	HitEffect->Off();
}


void NoiseFloor::Init(NoiseFloorType _Color, size_t _CurPhase)
{
	size_t Index = static_cast<size_t>(_Color);

	const std::string_view& TexName = FileNames[Index];
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	Render->SetTexture(TexName);

	const std::pair<float4, float4>& Path = MovePath[Index];
	StartPos = Path.first;
	DestPos = Path.second;

	GetTransform()->SetLocalPosition(StartPos);
	MoveDir = (DestPos - StartPos);
	MoveDir.Normalize();

	CurPhase = _CurPhase;
	if (3 <= CurPhase)
	{
		MsgAssert("현재 페이즈 설정이 잘못 되었습니다");
		return;
	}
}



void NoiseFloor::Update(float _DeltaTime)
{
	FieldActorBase::Update(_DeltaTime);

	switch (CurState)
	{
	case NoiseFloor::State::Move:
		Update_Move(_DeltaTime);
		break;
	case NoiseFloor::State::Destroy:
		Update_Destroy(_DeltaTime);
		break;
	case NoiseFloor::State::Hit:
		Update_Hit(_DeltaTime);
		break;
	}


}


void NoiseFloor::Update_Move(float _DeltaTime)
{
	static const std::vector<float> PhaseSpeed = { 100.f, 200.f, 300.f };
	float Speed = PhaseSpeed[CurPhase];

	GameEngineTransform* ThisTrans = GetTransform();
	ThisTrans->AddLocalPosition(MoveDir * Speed * _DeltaTime);
	ThisTrans->AddLocalScale(float4{ 0.08f, 0.08f } *_DeltaTime);

	//플레이어와 충돌한 경우
	if (true == CheckColWithPlayer())
		return;

	if (DestPos.y < ThisTrans->GetWorldPosition().y)
		return;

	ResetLiveTime();
	GetRenderer()->Off();
	GetAttackCollider()->Off();
	GetShadowRender()->Off();

	DestroyLight->On();
	CurState = State::Destroy;
}

bool NoiseFloor::CheckColWithPlayer()
{
	std::shared_ptr<GameEngineCollision> CollisionResult = nullptr;
	CollisionResult = GetAttackCollider()->Collision(CollisionOrder::PlayerMain, ColType::AABBBOX3D, ColType::AABBBOX3D);

	if (nullptr == CollisionResult)
		return false;
	
	Attack();
	return true;
}


void NoiseFloor::Attack()
{
	ResetLiveTime();
	GetRenderer()->Off();
	GetAttackCollider()->Off();
	GetShadowRender()->Off();

	if (true == FieldPlayer::GetPtr()->OnDamage_Jaw(Damage, true))
	{
		CurState = State::Hit;
		HitEffect->On();

		FieldLevelBase::GetPtr()->GetCameraController().SetShakeState(0.2f);

		static size_t Index = 0;
		SoundMgr::PlaySFX(HitSfx_FileNames[Index]);
		Index = (Index + 1) % HitSfx_FileNames.size();
	}
	else
	{
		CurState = State::Destroy;
		DestroyLight->On();
	}
}


void NoiseFloor::Update_Destroy(float _DeltaTime) 
{
	static const float Duration = 0.5f;
	static const float4 AddScale = float4{ 100.f, 100.f};

	DestroyLight->GetTransform()->AddLocalScale(AddScale *_DeltaTime);

	float Ratio = GetLiveTime() / Duration;
	if (1.f < Ratio)
	{
		Death();
		return;
	}

	Ratio = std::clamp(Ratio, 0.f, 1.f);
	DestroyLight->ColorOptionValue.MulColor.a = (1.f - Ratio);
}

void NoiseFloor::Update_Hit(float _DeltaTime)
{
	static const float Duration = 0.5f;

	float Ratio = GetLiveTime() / Duration;
	if (1.f < Ratio)
	{
		Death();
		return; 
	}

	Ratio = std::clamp(Ratio, 0.f, 1.f);
	HitEffect->ColorOptionValue.MulColor.a = (1.f - Ratio);
}

