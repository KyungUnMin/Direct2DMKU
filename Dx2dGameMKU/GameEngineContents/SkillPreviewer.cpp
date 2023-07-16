#include "PrecompileHeader.h"
#include "SkillPreviewer.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "DataMgr.h"

#include "ShopItem_CursorBar.h"



const std::string_view SkillPreviewer::BackImgSpriteName = "ShopGym_SkillPreviewer.png";
const std::vector<PlayerStateType> SkillPreviewer::GymSkillSlots =
{
	PlayerStateType::SpecialAttack_DAP,
	PlayerStateType::DashAttack_DropKick,
	PlayerStateType::UniqueAttack_DragonFeet,
	PlayerStateType::UniqueAttack_HyrricaneKick,
};


SkillPreviewer::SkillPreviewer()
{

}

SkillPreviewer::~SkillPreviewer()
{
	
}




void SkillPreviewer::Start()
{
	LoadAnimation();
	CreateBackImgRender();

	FieldPlayer::Start();
	CreateLayOutRender();
}


void SkillPreviewer::LoadAnimation()
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Level");
	Dir.Move("Shop");
	Dir.Move("Gym");
	GameEnginePath SpritePath = Dir.GetPlusFileName(BackImgSpriteName);
	GameEngineSprite::LoadSheet(SpritePath.GetFullPath(), 2, 1);
}




void SkillPreviewer::CreateBackImgRender()
{
	const std::string_view AniName = "BackImg";

	std::shared_ptr<GameEngineSpriteRenderer> BackRender = nullptr;
	BackRender = CreateComponent<GameEngineSpriteRenderer>(ShopUIRenderOrder::SkillViewer);
	BackRender->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = BackImgSpriteName,
	});

	BackRender->ChangeAnimation(AniName);

	const float4 RenderScale = float4{ 205.f, 222.f , 1.f};
	const float4 RenderOffset = float4{ 0.f, 73.f };

	GameEngineTransform* RenderTrans = BackRender->GetTransform();
	RenderTrans->SetLocalScale(RenderScale);
	RenderTrans->SetLocalPosition(RenderOffset);
}


void SkillPreviewer::CreateLayOutRender()
{
	const float4 RenderOffset = float4{ 6.f, 75.f };

	std::shared_ptr<GameEngineSpriteRenderer> LayoutRender = nullptr;
	LayoutRender = CreateComponent<GameEngineSpriteRenderer>(ShopUIRenderOrder::SkillViewer);
	LayoutRender->SetScaleToTexture("SkillPreviewerLayOut.png");

	GameEngineTransform* LayoutTrans = LayoutRender->GetTransform();
	LayoutTrans->SetLocalPosition(RenderOffset);
}




void SkillPreviewer::LevelChangeStart()
{
	FieldPlayer::LevelChangeStart();

	NowSkillIndex = 0;
	ChangeState(PlayerStateType::SpecialAttack_DAP);
	OriginPlayerMP = DataMgr::GetPlayerMP();
}


void SkillPreviewer::ChangeState(PlayerStateType _NextType)
{
	CurState = _NextType;
	GetFsm().ChangeState(static_cast<size_t>(_NextType));
}


void SkillPreviewer::Update(float _DeltaTime)
{
	GameEngineActor::Update(_DeltaTime);

	DataMgr::SetPlayerMP(OriginPlayerMP);

	size_t NowCursorIndex = ShopItem_CursorBar::GetCurrentIndex();
	if (NowCursorIndex != NowSkillIndex)
	{
		NowSkillIndex = NowCursorIndex;
		ChangeState(GymSkillSlots[NowSkillIndex]);
		return;
	}

	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	if (false == Render->IsAnimationEnd())
		return;

	if (PlayerStateType::Movement_Idle == GetFsm().GetNowState<PlayerStateType>())
		return;
	
	GetFsm().ChangeState(static_cast<size_t>(PlayerStateType::Movement_Idle));
}


