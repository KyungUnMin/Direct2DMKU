#include "PrecompileHeader.h"
#include "FieldActorBase.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "KeyMgr.h"

#include "FieldLevelBase.h"
#include "BackGround.h"

FieldActorBase::FieldActorBase()
{

}

FieldActorBase::~FieldActorBase()
{

}


void FieldActorBase::Start()
{
	GameEngineActor::Start();

	RendererPtr = CreateComponent<GameEngineSpriteRenderer>();
	BGPtr = FieldLevelBase::GetPtr()->GetBackGround();
	CreateDebugGridPoint();
}

void FieldActorBase::CreateDebugGridPoint()
{
	GridPosRender_Debug = CreateComponent<GameEngineSpriteRenderer>();
	GridPosRender_Debug->GetTransform()->SetWorldScale(BGPtr->GetGridScale());
	GridPosRender_Debug->Off();
}




void FieldActorBase::Update(float _DeltaTime)
{
	GameEngineActor::Update(_DeltaTime);

	GridPos = GetBackGround()->GetGridFromPos(GetTransform()->GetWorldPosition());
	Update_GridDebug();
}




void FieldActorBase::Update_GridDebug()
{
	if (true == KeyMgr::IsDown(KeyNames::DebugF2))
	{
		if (true == GridPosRender_Debug->IsUpdate())
		{
			GridPosRender_Debug->Off();
		}
		else
		{
			GridPosRender_Debug->On();
		}
	}

	if (false == GridPosRender_Debug->IsUpdate())
		return;

	float4 FieldPos = BGPtr->GetPosFromGrid(GridPos.first, GridPos.second);
	GridPosRender_Debug->GetTransform()->SetWorldPosition(FieldPos + float4::Back * 500.f);
}




