#include "PrecompileHeader.h"
#include "FieldActorBase.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCGDefine.h"
#include "KeyMgr.h"
#include "RCGEnums.h"

#include "FieldLevelBase.h"
#include "BackGround.h"

const float4 FieldActorBase::RenderScale = float4{ 200.f, 200.f } *2.5f;
const float4 FieldActorBase::CollisionColor = float4{ 0.f, 1.f, 0.f, 0.5f };
bool FieldActorBase::IsGridPosRenderOn_ForDebug = false;
bool FieldActorBase::IsColRenderOn_ForDebug = false;


FieldActorBase::FieldActorBase()
{

}

FieldActorBase::~FieldActorBase()
{

}


void FieldActorBase::Start()
{
	GameEngineActor::Start();

	CreateShadow();
	RendererPtr = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	RendererPtr->GetTransform()->SetLocalScale(RenderScale);

	BGPtr = FieldLevelBase::GetPtr()->GetBackGround();
	CreateDebugGridPoint();
}



void FieldActorBase::CreateShadow()
{
	static bool IsLoad = false;
	const std::string_view ShadowImageName = "FieldCharShadow.png";
	if (false == IsLoad)
	{
		GameEngineDirectory Dir;
		RCGDefine::MoveContentPath(Dir, ResType::Image);
		Dir.Move("Character");
		GameEngineTexture::Load(Dir.GetPlusFileName(ShadowImageName).GetFullPath());
		IsLoad = true;
	}

	ShadowRender = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	ShadowRender->SetScaleToTexture(ShadowImageName);

	GameEngineTransform* ShadowTrans = ShadowRender->GetTransform();
	ShadowTrans->SetLocalScale(ShadowTrans->GetLocalScale() * 1.5f);
	ShadowTrans->AddLocalPosition(float4::Up * 10.f);
}

void FieldActorBase::SetShadowScale(const float4& _ShadowScale)
{
	GameEngineTransform* ShadowTrans = ShadowRender->GetTransform();
	ShadowTrans->SetLocalScale(_ShadowScale);
}

void FieldActorBase::SetShadowScale(float _Ratio) 
{
	GameEngineTransform* ShadowTrans = ShadowRender->GetTransform();
	ShadowTrans->SetLocalScale(ShadowTrans->GetLocalScale() * _Ratio);
}



void FieldActorBase::CreateDebugGridPoint()
{
	GridPosRender_Debug = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::Debug_Grid);
	GridPosRender_Debug->GetTransform()->SetWorldScale(BGPtr->GetGridScale());
	GridPosRender_Debug->Off();
}



void FieldActorBase::CreateColliders(CollisionOrder _Order)
{
	if (CollisionOrder::EnemyMain == _Order || CollisionOrder::EnemyAttack == _Order)
	{
		MainCollider = CreateVisuableCollision(CollisionOrder::EnemyMain);
		AttackCollider = CreateVisuableCollision(CollisionOrder::EnemyAttack);
	}
	else if (CollisionOrder::PlayerMain == _Order || CollisionOrder::PlayerAttack == _Order)
	{
		MainCollider = CreateVisuableCollision(CollisionOrder::PlayerMain);
		AttackCollider = CreateVisuableCollision(CollisionOrder::PlayerAttack);
	}
	else if(CollisionOrder::NPC == _Order)
	{
		MainCollider = CreateVisuableCollision(CollisionOrder::NPC);
	}
	else
	{
		MsgAssert("Player, Enemy, NPC의 충돌체만 만들수 있습니다");
	}
}


FieldActorBase::VisualCollider FieldActorBase::CreateVisuableCollision(CollisionOrder _Order)
{
	VisualCollider Family;

	Family.ParentCollision = CreateComponent<GameEngineCollision>(_Order);
	GameEngineTransform* CollisionTrans = Family.ParentCollision->GetTransform();

	Family.ChildRender = CreateComponent<GameEngineRenderer>(FieldRenderOrder::ZOrder);
	GameEngineTransform* RenderTrans = Family.ChildRender->GetTransform();
	RenderTrans->SetParent(CollisionTrans, false);


	RenderTrans->SetLocalScale(float4::One);
	CollisionTrans->SetLocalScale(float4::One * 100.f);


	static bool IsLoad = false;
	static const std::string_view RenderImageName = "CollisionArea.png";
	if (false == IsLoad)
	{
		GameEngineDirectory Dir;
		RCGDefine::MoveContentPath(Dir, ResType::Image);
		Dir.Move("Character");
		GameEngineTexture::Load(Dir.GetPlusFileName(RenderImageName).GetFullPath());
		IsLoad = true;
	}

	Family.ChildRender->SetMesh("Rect");
	Family.ChildRender->SetPipeLine(RCGDefine::GetPipeName(PipeType::DirectColor));
	Family.ChildRender->GetShaderResHelper().SetTexture(RCGDefine::EngineTexName, RenderImageName);
	Family.ChildRender->GetShaderResHelper().SetConstantBufferLink("LinkColor", CollisionColor);

	Family.ChildRender->Off();
	return Family;
}





void FieldActorBase::Update(float _DeltaTime)
{
	GameEngineActor::Update(_DeltaTime);

	GridPos = GetBackGround()->GetGridFromPos(GetTransform()->GetWorldPosition());
	Update_GridDebug();
	Update_ColliderView();
}


void FieldActorBase::Update_CheckDebugKey()
{
	if (true == KeyMgr::IsDown(KeyNames::DebugF2))
	{
		IsGridPosRenderOn_ForDebug = !IsGridPosRenderOn_ForDebug;
	}

	if (true == KeyMgr::IsDown(KeyNames::DebugF3))
	{
		IsColRenderOn_ForDebug = !IsColRenderOn_ForDebug;
		//GameEngineLevel::IsDebugSwitch();
	}
}


void FieldActorBase::Update_GridDebug()
{
	if (true == IsGridPosRenderOn_ForDebug)
	{
		GridPosRender_Debug->On();
	}
	else
	{
		GridPosRender_Debug->Off();
	}

	if (false == GridPosRender_Debug->IsUpdate())
		return;

	float4 FieldPos = BGPtr->GetPosFromGrid(GridPos.first, GridPos.second);
	GridPosRender_Debug->GetTransform()->SetWorldPosition(FieldPos + float4::Back * 500.f);
}



void FieldActorBase::Update_ColliderView()
{
	if (nullptr != MainCollider.ParentCollision)
	{
		if (false == IsColRenderOn_ForDebug)
		{
			MainCollider.ChildRender->Off();
		}
		else
		{
			MainCollider.ChildRender->On();
		}
	}

	if (nullptr != AttackCollider.ParentCollision)
	{
		if (false == IsColRenderOn_ForDebug)
		{
			AttackCollider.ChildRender->Off();
		}
		else
		{
			AttackCollider.ChildRender->On();
		}
	}

}


