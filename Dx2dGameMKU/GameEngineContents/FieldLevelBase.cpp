#include "PrecompileHeader.h"
#include "FieldLevelBase.h"

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCGEnums.h"
#include "RCGDefine.h"
#include "GUIManager.h"
#include "GameEngineActorGUI.h"

#include "BackGround.h"
#include "FieldPlayer.h"
#include "Fader.h"
#include "HUD.h"


FieldLevelBase* FieldLevelBase::GPtr = nullptr;

FieldLevelBase::FieldLevelBase()
{

}

FieldLevelBase::~FieldLevelBase()
{

}




void FieldLevelBase::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetWorldPosition(float4::Back * 500.f);

	PlayerPtr = CreateActor<FieldPlayer>(static_cast<int>(UpdateOrder::Player));
	BGPtr = CreateActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	CreateActor<HUD>(static_cast<int>(UpdateOrder::UI));

	FreeCamDebugMoveCtrl.Init(GetMainCamera());
}


void FieldLevelBase::InitLevelArea(const float4& _Scale, const TileInfoData& _TileData)
{
	BGPtr->InitLevelArea(_Scale, _TileData);
	CamCtrl.Init(GetMainCamera(), _Scale);
}


void FieldLevelBase::CreateBackGrounds(const std::vector<std::pair<std::string_view, float4>> _BackGroundInfoes, const size_t _GuiSelect /*= UINT64_MAX*/)
{
	std::shared_ptr<GameEngineActorGUI> TransCtrlGUI = GUIManager::Find<GameEngineActorGUI>();

	for (size_t i = 0; i < _BackGroundInfoes.size(); ++i)
	{
		const std::pair<std::string_view, float4>& Pair = _BackGroundInfoes[i];

		const std::string_view& BGName = Pair.first;
		float4 BGScale = ResourceHelper::GetTextureScale(BGName) * RCGDefine::ResourceScaleConvertor;
		const float4& Offset = Pair.second;

		std::shared_ptr<GameEngineSpriteRenderer> RenderPtr = BGPtr->CreateBackImage(BGName, BGScale, Offset);

		if (nullptr == TransCtrlGUI)
			continue;

		if (_GuiSelect != i)
			continue;

		TransCtrlGUI->SetTarget(RenderPtr->GetTransform());
	}
}

void FieldLevelBase::CreateCollisionImage(const std::string_view& _ImageName)
{
	BGPtr->CreateCollisionImage(_ImageName);
}



void FieldLevelBase::SetPlayerStartPosition(const float4& _StartPos)
{
	PlayerPtr->GetTransform()->SetLocalPosition({ _StartPos.x, _StartPos.y, _StartPos.y });
}







void FieldLevelBase::LevelChangeStart()
{
	GPtr = this;
	FieldPlayer::GPtr = PlayerPtr.get();

	CreateActor<Fader>(static_cast<int>(UpdateOrder::UI))->Init(float4{ 0.f, 0.f, 0.f, 1.0f });
}



void FieldLevelBase::Update(float _DeltaTime)
{
	CamCtrl.Update(_DeltaTime);
	FreeCamDebugMoveCtrl.Update(_DeltaTime);
}



bool FieldLevelBase::IsBlockPos(const float4& _Pos)
{
	return BGPtr->IsBlockPos(_Pos);
}

