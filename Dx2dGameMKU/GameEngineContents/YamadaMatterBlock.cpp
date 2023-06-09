#include "PrecompileHeader.h"
#include "YamadaMatterBlock.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "RCGDefine.h"
#include "RCGEnums.h"
#include "DataMgr.h"
#include "SoundMgr.h"

#include "FieldPlayer.h"
#include "LightEffect.h"
#include "FieldLevelBase.h"
#include "BackGround.h"
#include "YamadaMatterDust.h"
#include "YamadaMatterFragment.h"

const float YamadaMatterBlock::BlockOffsetX = 200.f;

const std::string_view YamadaMatterBlock::BlockName = "Yamada_MatterCrush_Block.png";
const std::string_view YamadaMatterBlock::DustName = "Yamada_MatterCrush_Dust.png";
const std::string_view YamadaMatterBlock::SparkName = "MatterCruchSpark.png";

const float YamadaMatterBlock::Duration = 0.5f;
const int YamadaMatterBlock::Damage = 2;



YamadaMatterBlock::YamadaMatterBlock()
{

}

YamadaMatterBlock::~YamadaMatterBlock()
{

}

void YamadaMatterBlock::Start()
{
	FieldActorBase::Start();

	ImageLoad();
	CreateRenders();
	SettingCollider();
	CreateLight();
	CreateSparkEffect();
	
	BGPtr = FieldLevelBase::GetPtr()->GetBackGround();
}

void YamadaMatterBlock::ImageLoad()
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

	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });
	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}

	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(BlockName).GetFullPath(), 5, 1);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(DustName).GetFullPath(), 4, 4);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(SparkName).GetFullPath(), 2, 2);
}

void YamadaMatterBlock::CreateRenders()
{
	const float4 BlockScale = float4{ 600.f, 600.f, 1.f };
	const float4 DustScale = float4{ 128.f, 128.f, 1.f };
	const float4 DustOffset = float4{ 50.f, 50.f, -1.f };


	//기둥
	std::shared_ptr<GameEngineSpriteRenderer> Block = GetRenderer();
	Block->CreateAnimation
	({
		.AnimationName = BlockName,
		.SpriteName = BlockName,
		.Loop = false,
		});
	Block->ChangeAnimation(BlockName);
	GameEngineTransform* BlockTrans = Block->GetTransform();
	BlockTrans->SetLocalScale(BlockScale);


	//먼지
	Dust = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	Dust->CreateAnimation
	({
		.AnimationName = DustName,
		.SpriteName = DustName,
		.FrameInter = 0.06f,
		.Loop = false,
	});
	Dust->ChangeAnimation(DustName);
	GameEngineTransform* DustTrans = Dust->GetTransform();
	DustTrans->SetLocalScale(DustScale);
	DustTrans->SetLocalPosition(DustOffset);


	


	//부모자식 관계 설정
	Pivot = CreateComponent<GameEngineComponent>();
	GameEngineTransform* PivotTrans = Pivot->GetTransform();
	BlockTrans->SetParent(PivotTrans);
	DustTrans->SetParent(PivotTrans);
	GetShadowRender()->GetTransform()->SetParent(PivotTrans);


	//위치 조절
	PivotTrans->SetLocalPosition(float4::Right * BlockOffsetX);
	Pivot->Off();
}

void YamadaMatterBlock::SettingCollider()
{
	const float4 ColScale = float4{ 50.f, 200.f, 50.f };

	CreateCollider(CollisionOrder::EnemyAttack);
	std::shared_ptr<GameEngineCollision> Collider = GetAttackCollider();
	Collider->SetColType(ColType::AABBBOX3D);

	GameEngineTransform* ColTrans = Collider->GetTransform();
	ColTrans->SetParent(Pivot->GetTransform(), false);
	ColTrans->SetLocalScale(ColScale);
	ColTrans->SetLocalPosition(float4::Up * ColScale.hy());
}


void YamadaMatterBlock::CreateLight()
{
	std::shared_ptr<LightEffect> Light = nullptr;
	Light = GetLevel()->CreateActor<LightEffect>(UpdateOrder::Effect);
	Light->Flicker(float4::Red, Duration);

	GameEngineTransform* LightTrans = Light->GetTransform();
	LightTrans->SetParent(GetTransform());
	LightTrans->AddLocalPosition(float4::Right * BlockOffsetX);
}


void YamadaMatterBlock::CreateSparkEffect()
{
	const float4 SparkScale = float4{ 128.f, 256.f };
	
	Spark = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	
	Spark->CreateAnimation
	({
		.AnimationName = SparkName,
		.SpriteName = SparkName,
		.FrameInter = 0.08f,
		.Loop = true,
	});

	Spark->ChangeAnimation(SparkName);
	Spark->ColorOptionValue.MulColor = float4{ 0.0f, 0.f, 0.5f, 0.5f };

	GameEngineTransform* SparkTrans = Spark->GetTransform();
	SparkTrans->SetParent(Pivot->GetTransform());

	SparkTrans->SetLocalScale(SparkScale);
	SparkTrans->SetLocalPosition(float4::Up * SparkScale.hy());
}


void YamadaMatterBlock::Update(float _DeltaTime)
{
	FieldActorBase::Update(_DeltaTime);

	switch (CurState)
	{
	case YamadaMatterBlock::State::Light:
		Update_Light(_DeltaTime);
		break;
	case YamadaMatterBlock::State::BlockCreate:
		Update_BlockCreate(_DeltaTime);
		break;
	case YamadaMatterBlock::State::Approach:
		Update_Approach(_DeltaTime);
		break;
	case YamadaMatterBlock::State::BlockDestroy:
		Update_BlockDestroy(_DeltaTime);
		break;
	}
	
}

void YamadaMatterBlock::Update_Light(float _DeltaTime)
{
	float LiveTime = GetLiveTime();
	if (LiveTime < Duration)
		return;

	CurState = State::BlockCreate;
	Pivot->On();

	SoundMgr::PlaySFX("Yamada_MatterCrush_Create_Effect.wav").SetVolume(3.f);
}

void YamadaMatterBlock::Update_BlockCreate(float _DeltaTime)
{
	CheckColWithPlayer();

	if (false == Dust->IsAnimationEnd())
		return;

	Spark->Off();
	Dust->Off();
	ResetLiveTime();
	PrevBlockPos = Pivot->GetTransform()->GetWorldPosition();
	CurState = State::Approach;

	SoundMgr::PlaySFX("Yamada_MatterCrush_Come_Effect.wav").SetVolume(3.f);
}

void YamadaMatterBlock::Update_Approach(float _DeltaTime)
{
	//이동하기 전 위치 기억
	PrevBlockPos = Pivot->GetTransform()->GetWorldPosition();

	//이동
	float LiveTime = GetLiveTime();
	float Ratio = (LiveTime / 0.2f);
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);

	float CosValue = cosf(GameEngineMath::PIE * 0.5f * ClampRatio);
	float NowLocalPosX = BlockOffsetX * CosValue;
	Pivot->GetTransform()->SetLocalPosition(float4::Right * NowLocalPosX);

	//충돌체크
	CheckColWithPlayer();

	if (Ratio <= 1.f)
		return;

	std::shared_ptr<GameEngineSpriteRenderer> Block = GetRenderer();
	Block->Off();
	CurState = State::BlockDestroy;

	SoundMgr::PlaySFX("Yamada_MatterCrush_Break_Effect.mp3").SetVolume(3.f);
}

void YamadaMatterBlock::Update_BlockDestroy(float _DeltaTime) 
{
	//충돌 이펙트 생성
	std::shared_ptr<YamadaMatterDust> Dust = nullptr;
	Dust = GetLevel()->CreateActor<YamadaMatterDust>(UpdateOrder::Effect);
	Dust->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());

	//충돌 파편 생성
	for (size_t i = 0; i < 10; ++i)
	{
		std::shared_ptr<YamadaMatterFragment> Fragment = nullptr;
		Fragment = GetLevel()->CreateActor<YamadaMatterFragment>(UpdateOrder::Effect);
		Fragment->GetTransform()->SetLocalPosition(GetTransform()->GetWorldPosition());
	}
	

	Death();
}




void YamadaMatterBlock::CheckColWithPlayer()
{
	std::shared_ptr<GameEngineCollision> Collider = GetAttackCollider();
	if (nullptr == Collider->Collision(CollisionOrder::PlayerMain, ColType::AABBBOX3D, ColType::SPHERE3D))
		return;

	Attack();
}

void YamadaMatterBlock::Attack() 
{
	switch (CurState)
	{
	case YamadaMatterBlock::State::BlockCreate:
		Attack_FixedBlock();
		return;
	case YamadaMatterBlock::State::Approach:
		Attack_MoveBlock();
		return;
	}

	MsgAssert("해당 상태에서는 충돌이 일어날 수 없습니다");
}


void YamadaMatterBlock::Attack_FixedBlock()
{
	std::shared_ptr<FieldPlayer> Player = FieldPlayer::GetPtr();

	if (true == Player->IsStuned())
		return;

	bool AttackResult = false;
	if (true == Player->IsBlowing())
	{
		AttackResult = Player->OnDamage_Stun(false, true);
		return;
	}

	AttackResult = Player->OnDamage_BlowBack(true);
	if (false == AttackResult)
		return;

	DataMgr::MinusPlayerHP(Damage);
}


void YamadaMatterBlock::Attack_MoveBlock()
{
	float4 BlockNowPos = Pivot->GetTransform()->GetWorldPosition();
	float4 BlockMoveVec = (BlockNowPos - PrevBlockPos);

	GameEngineTransform* PlayerTrans = FieldPlayer::GetPtr()->GetTransform();
	float4 PlayerNowPos = PlayerTrans->GetLocalPosition();
	float4 PlayerNextPos = (PlayerNowPos + BlockMoveVec);

	if (true == BGPtr->IsBlockPos(PlayerNextPos))
		return;

	std::pair<int, int> GridNextPos = BGPtr->GetGridFromPos(PlayerNextPos);
	if (true == BGPtr->IsBlockGrid(GridNextPos.first, GridNextPos.second))
		return;

	PlayerTrans->SetLocalPosition(PlayerNextPos);
}