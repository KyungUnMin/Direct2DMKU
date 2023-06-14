#include "PrecompileHeader.h"
#include "YamadaMatterBlock.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "DataMgr.h"

#include "FieldPlayer.h"
#include "LightEffect.h"

const float YamadaMatterBlock::BlockOffsetX = 200.f;

const std::string_view YamadaMatterBlock::BlockName = "MatterCrushFragment (_).png";
const std::string_view YamadaMatterBlock::DustName = "Yamada_MatterCrush_Dust.png";
const std::string_view YamadaMatterBlock::FragmentName = "Yamada_MatterCrush_Block.png";

YamadaMatterBlock::YamadaMatterBlock()
{

}

YamadaMatterBlock::~YamadaMatterBlock()
{

}

void YamadaMatterBlock::Start()
{
	GameEngineActor::Start();

	ImageLoad();
	CreateRenders();
	CreateLight();
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
}

void YamadaMatterBlock::CreateRenders()
{
	Block = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	Block->CreateAnimation
	({
		.AnimationName = BlockName,
		.SpriteName = BlockName,
		.Loop = false,
	});
	Block->ChangeAnimation(BlockName);
	GameEngineTransform* BlockTrans = Block->GetTransform();
	BlockTrans->SetLocalScale(float4::One * 300.f);

	Dust = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	Dust->CreateAnimation
	({
		.AnimationName = DustName,
		.SpriteName = DustName,
		.Loop = false,
	});
	Dust->ChangeAnimation(DustName);
	GameEngineTransform* DustTrans = Dust->GetTransform();
	DustTrans->SetLocalScale(float4::One * 64.f);

	Pivot = CreateComponent<GameEngineComponent>();
	GameEngineTransform* PivotTrans = Pivot->GetTransform();
	BlockTrans->SetParent(PivotTrans);
	DustTrans->SetParent(PivotTrans);

	PivotTrans->SetLocalPosition(float4::Right * BlockOffsetX);
	Pivot->Off();
}


void YamadaMatterBlock::CreateLight()
{
	std::shared_ptr<LightEffect> Light = nullptr;
	GetLevel()->CreateActor<LightEffect>(UpdateOrder::Effect);
	Light->Flicker(float4::Red);

	GameEngineTransform* LightTrans = Light->GetTransform();
	LightTrans->SetParent(GetTransform());
	LightTrans->AddLocalPosition(float4::Right * BlockOffsetX);
}



void YamadaMatterBlock::Update(float _DeltaTime)
{
	GameEngineActor::Update(_DeltaTime);


}

