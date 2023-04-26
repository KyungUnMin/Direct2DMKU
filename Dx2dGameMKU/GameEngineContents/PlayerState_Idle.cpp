#include "PrecompileHeader.h"
#include "PlayerState_Idle.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "KeyMgr.h"
#include "RCGDefine.h"
#include "PlayerFSM.h"
#include "FieldPlayer.h"


PlayerState_Idle::PlayerState_Idle()
{

}

PlayerState_Idle::~PlayerState_Idle()
{

}

void PlayerState_Idle::Start()
{
	PlayerStateBase::Start();
	SetArrowKey();
	LoadAnimation();
	CreateAnimation();
}


void PlayerState_Idle::SetArrowKey()
{
	ArrowKeyNames.reserve(4);
	ArrowKeyNames.push_back(KeyNames::UpArrow);
	ArrowKeyNames.push_back(KeyNames::DownArrow);
	ArrowKeyNames.push_back(KeyNames::RightArrow);
	ArrowKeyNames.push_back(KeyNames::LeftArrow);
}

void PlayerState_Idle::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Player");
	Dir.Move("Movement");
	Dir.Move("Idle");
	std::vector<GameEngineFile> Images = Dir.GetAllFile({ ".png" });

	for (const GameEngineFile& Image : Images)
	{
		GameEngineTexture::Load(Image.GetFullPath());
	}
}

void PlayerState_Idle::CreateAnimation()
{
	std::shared_ptr<GameEngineRenderer> Renderer = FieldPlayer::GetPtr()->CreateComponent<GameEngineRenderer>();
	Renderer->SetPipeLine(RCGDefine::EnginePipeName);
	Renderer->GetShaderResHelper().SetTexture(RCGDefine::EngineTexName, "RCG_Kyoko_idle0001_anio.png");

	Renderer->GetTransform()->SetLocalScale({ 100.f, 100.f, 100.f });
}




void PlayerState_Idle::Update(float _DeltaTime)
{
	PlayerStateBase::Update(_DeltaTime);

	
	for (KeyNames Arrow : ArrowKeyNames)
	{
		if (false == KeyMgr::IsPress(Arrow))
			continue;

		GetFSM()->ChangeState(PlayerStateType::Move);
		return;
	}

	if (true == KeyMgr::IsPress(KeyNames::Space))
	{
		GetFSM()->ChangeState(PlayerStateType::Jump);
		return;
	}

}

