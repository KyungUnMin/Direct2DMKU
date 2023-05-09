#include "PrecompileHeader.h"
#include "FieldPlayer.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "KeyMgr.h"

#include "FieldLevelBase.h"
#include "BackGround.h"


FieldPlayer* FieldPlayer::GPtr = nullptr;

FieldPlayer::FieldPlayer()
{
	//Start부분을 위해 여기서도 설정
	GPtr = this;
}

FieldPlayer::~FieldPlayer()
{
	if (this == GPtr)
	{
		GPtr = nullptr;
	}
}


void FieldPlayer::Start()
{
	FieldActorBase::Start();

	CreateRender();

	Fsm.Init();
	BGPtr = FieldLevelBase::GetPtr()->GetBackGround();

	CreateDebugGridPoint();
}


void FieldPlayer::CreateDebugGridPoint()
{
	GridPosRender_Debug = CreateComponent<GameEngineSpriteRenderer>();
	GridPosRender_Debug->GetTransform()->SetWorldScale(BGPtr->GetGridScale());
	GridPosRender_Debug->Off();
}


void FieldPlayer::CreateRender()
{
	/*std::shared_ptr<GameEngineSpriteRenderer> Shadow = CreateComponent<GameEngineSpriteRenderer>();
	Shadow->SetScaleToTexture("player_shadow.png");*/

	RendererPtr = CreateComponent<GameEngineSpriteRenderer>();
	RendererPtr->SetName("PlayerRender");
}



void FieldPlayer::Update(float _DeltaTime) 
{
	FieldActorBase::Update(_DeltaTime);

	Fsm.Update(_DeltaTime);

	GridPos = BGPtr->GetGridFromPos(GetTransform()->GetWorldPosition());
	Update_GridRender_Debug();
}

void FieldPlayer::Update_GridRender_Debug()
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



void FieldPlayer::Render(float _DeltaTime)
{
	FieldActorBase::Render(_DeltaTime);

	Fsm.Render(_DeltaTime);
}

