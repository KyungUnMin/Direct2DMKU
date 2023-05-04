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
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = FieldPlayer::GetPtr()->GetRenderer();
	//Renderer->SetTexture("RCG_Kyoko_idle0001_anio.png");

	Renderer->SetScaleToTexture("RCG_Kyoko_idle0001_anio.png");
	GameEngineTransform* RenderTrans = Renderer->GetTransform();
	//RenderTrans->SetLocalScale(float4{ 37.f, 70.f, 1.f } *RCGDefine::ResourceScaleConvertor);

	float4 TexSize = RenderTrans->GetLocalScale() * RCGDefine::ResourceScaleConvertor;
	RenderTrans->SetLocalScale(TexSize);
	RenderTrans->SetLocalPosition(float4::Up * TexSize.hy());
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

