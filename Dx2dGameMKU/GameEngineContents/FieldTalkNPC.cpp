#include "PrecompileHeader.h"
#include "FieldTalkNPC.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "RCGDefine.h"
#include "RCGEnums.h"
#include "KeyMgr.h"

FieldTalkNPC::FieldTalkNPC()
{

}

FieldTalkNPC::~FieldTalkNPC()
{

}

void FieldTalkNPC::Start()
{
	FieldActorBase::Start();
	FieldActorBase::CreateColliders(CollisionOrder::NPC);
	GetMainCollider()->GetTransform()->SetLocalScale(float4::One * 100.f);

	IconBackRender = CreateIconRender();
	IconBackRender->ColorOptionValue.MulColor.a = 0.5f;
	IconFrontRender = CreateIconRender();
	IconFrontRender->ImageClippingY(0.0f, ClipYDir::Bot);
}


std::shared_ptr<GameEngineSpriteRenderer> FieldTalkNPC::CreateIconRender()
{
	const std::string_view IconFileName = "TalkNpc_Icon";
	if (nullptr == GameEngineSprite::Find(IconFileName))
	{
		GameEngineDirectory Dir;
		RCGDefine::MoveContentPath(Dir, ResType::Image);
		Dir.Move("Character");
		Dir.Move("NPC");
		Dir.Move("TalkNPC");
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName(IconFileName).GetFullPath());
	}

	std::shared_ptr<GameEngineSpriteRenderer> IconRender = nullptr;
	IconRender = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	IconRender->CreateAnimation
	({
		.AnimationName = IconFileName,
		.SpriteName = IconFileName,
		.ScaleToImage = true,
	});

	const float4 RenderOffset = float4{ 100.f, 250.f };
	IconRender->ChangeAnimation(IconFileName);
	IconRender->GetTransform()->SetLocalPosition(RenderOffset);
	return IconRender;
}




void FieldTalkNPC::AnimationCreate(const std::string_view& _NpcFolderName)
{
	if (nullptr == GameEngineSprite::Find(_NpcFolderName))
	{
		GameEngineDirectory Dir;
		RCGDefine::MoveContentPath(Dir, ResType::Image);
		Dir.Move("Character");
		Dir.Move("NPC");
		Dir.Move("TalkNPC");
		GameEngineSprite::LoadFolder(Dir.GetPlusFileName(_NpcFolderName).GetFullPath());
	}

	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	Render->CreateAnimation
	({
		.AnimationName = _NpcFolderName,
		.SpriteName = _NpcFolderName,
		.Loop = true,
	});

	Render->ChangeAnimation(_NpcFolderName);
}

void FieldTalkNPC::Update(float _DeltaTime)
{
	FieldActorBase::Update(_DeltaTime);
	FieldNPCBase::Update_RenderTrans();

	Update_Collision(_DeltaTime);

	
}

void FieldTalkNPC::Update_Collision(float _DeltaTime)
{
	if (true == IsTalking)
		return;

	if (false == KeyMgr::IsPress(KeyNames::Z))
	{
		TalkWaitTime = 0.f;
		IconFrontRender->ImageClippingY(0.f, ClipYDir::Bot);
		return;
	}

	if (nullptr == GetMainCollider()->Collision(CollisionOrder::PlayerMain, ColType::SPHERE3D, ColType::SPHERE3D))
	{
		TalkWaitTime = 0.f;
		IconFrontRender->ImageClippingY(0.f, ClipYDir::Bot);
		return;
	}

	TalkWaitTime += _DeltaTime;
	float Ratio = (TalkWaitTime / TalkWaitDuration);
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	IconFrontRender->ImageClippingY(ClampRatio, ClipYDir::Bot);

	if (Ratio < 1.f)
		return;

	//TODO
	//대화 UI창 띄우기
	IsTalking = true;

}