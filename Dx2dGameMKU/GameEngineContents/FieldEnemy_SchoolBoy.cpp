#include "PrecompileHeader.h"
#include "FieldEnemy_SchoolBoy.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "RCGDefine.h"



FieldEnemy_SchoolBoy::FieldEnemy_SchoolBoy()
{

}

FieldEnemy_SchoolBoy::~FieldEnemy_SchoolBoy()
{

}


void FieldEnemy_SchoolBoy::Start()
{
	FieldEnemyBase::Start();

	LoadImages();
	CreateAnimations();
	CreateFsmStates();
}

void FieldEnemy_SchoolBoy::LoadImages()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("SchoolBoy");
	Dir.Move("Idle");
	GameEngineTexture::Load(Dir.GetPlusFileName("RCG_School_Boy_Idle_01_anio.png").GetFullPath());
}

void FieldEnemy_SchoolBoy::CreateAnimations()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	Render->SetScaleToTexture("RCG_School_Boy_Idle_01_anio.png");
	GameEngineTransform* RenderTrans = Render->GetTransform();

	RenderTrans->SetLocalScale(RenderTrans->GetLocalScale() * RCGDefine::ResourceScaleConvertor);
	RenderTrans->AddLocalPosition(float4::Up * RenderTrans->GetLocalScale().hy());
}



