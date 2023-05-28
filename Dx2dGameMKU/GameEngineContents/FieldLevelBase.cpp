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
	//다른 클래스가 Start시점에서 FieldPlayer::GPtr 를 통해 레벨에 접근할 때를 위함
	GPtr = this;

	std::shared_ptr<GameEngineCamera> CamPtr = GetMainCamera();
	CamPtr->SetProjectionType(CameraType::Orthogonal);
	CamPtr->SetSortType(FieldRenderOrder::ZOrder, SortType::ZSort);
	CamPtr->GetTransform()->SetWorldPosition(float4::Back * 500.f);
}


void FieldLevelBase::Init(const float4& _Scale, const TileInfoData& _TileData)
{
	//BG먼저 생성 후에 플레이어가 생성되어야 함
	BGPtr = CreateActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	BGPtr->InitLevelArea(_Scale, _TileData);
	CamCtrl.Init(GetMainCamera(), _Scale);

	PlayerPtr = CreateActor<FieldPlayer>(static_cast<int>(UpdateOrder::Player));
	CreateActor<HUD>(static_cast<int>(UpdateOrder::UI));
	FreeCamDebugMoveCtrl.Init(GetMainCamera());
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
	GameEngineLevel::LevelChangeStart();

	GPtr = this;
	FieldPlayer::GPtr = PlayerPtr.get();

	CreateActor<Fader>(static_cast<int>(UpdateOrder::UI))->Init(float4{ 0.f, 0.f, 0.f, 1.0f });
}


void FieldLevelBase::LevelChangeEnd()
{
	GameEngineLevel::LevelChangeEnd();

	//카메라 줌 초기화
	CamCtrl.SetZoom();
}


void FieldLevelBase::Update(float _DeltaTime)
{
	CamCtrl.Update(_DeltaTime);
	FreeCamDebugMoveCtrl.Update(_DeltaTime);
}


//
//bool FieldLevelBase::IsBlockPos(const float4& _Pos)
//{
//	return BGPtr->IsBlockPos(_Pos);
//}
//
