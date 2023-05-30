#include "PrecompileHeader.h"
#include "DebugActor.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCGEnums.h"
#include "RCGDefine.h"
#include "GUIManager.h"
#include "GameEngineActorGUI.h"

const float4 DebugActor::PositionPointerColor = float4{ 1.f, 0.f ,1.f, 1.f };

DebugActor::DebugActor()
{

}

DebugActor::~DebugActor()
{

}

void DebugActor::Init_PositionPointer(const std::string_view& _TexName /*= ""*/)
{
	MsgTextBox("DebugActor에서 TransViewer를 실행합니다");

	PositionPointerRender = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::Debug_Grid);
	if (false == _TexName.empty())
	{
		PositionPointerRender->SetTexture(_TexName);
	}

	std::shared_ptr<GameEngineActorGUI> TransViewer = nullptr;
	TransViewer = GUIManager::CreateGui<GameEngineActorGUI>();
	TransViewer->SetTarget(PositionPointerRender->GetTransform());
}