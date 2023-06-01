#include "PrecompileHeader.h"
#include "FieldNPCBase.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "RCGEnums.h"
#include "RCGDefine.h"
#include "FieldPlayer.h"


const std::string FieldNPCBase::IdleAniName = "_Idle";
const std::string FieldNPCBase::ReactAniName = "_React";


FieldNPCBase::FieldNPCBase()
{

}

FieldNPCBase::~FieldNPCBase()
{

}


void FieldNPCBase::Start() 
{
	FieldActorBase::Start();
	FieldActorBase::CreateColliders(CollisionOrder::NPC);
}


void FieldNPCBase::AnimationCreate(const std::string_view& _NpcFolderName)
{
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("NPC");
	Dir.Move(_NpcFolderName);

	std::string FolderName = _NpcFolderName.data();

	//Sprite�̸����� ���� �̸�
	std::string IdleSpriteName = FolderName + IdleAniName;
	std::string ReactSpriteName = FolderName + ReactAniName;
	
	GameEnginePath IdleSheetPath = Dir.GetPlusFileName(IdleSpriteName);
	GameEnginePath ReactSheetPath = Dir.GetPlusFileName(ReactSpriteName);

	if (nullptr == GameEngineSprite::Find(IdleSpriteName))
	{
		GameEngineSprite::LoadFolder(IdleSheetPath.GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find(ReactSpriteName))
	{
		GameEngineSprite::LoadFolder(ReactSheetPath.GetFullPath());
	}

	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();

	//Idle�ִϸ��̼�
	Render->CreateAnimation
	({
		.AnimationName = IdleAniName,
		.SpriteName = IdleSpriteName,
		.Loop = true,
		});

	Render->CreateAnimation
	({
		.AnimationName = ReactAniName,
		.SpriteName = ReactSpriteName,
		.Loop = false,
		});

	Render->ChangeAnimation(IdleAniName);
}


void FieldNPCBase::Update(float _DeltaTime)
{
	FieldActorBase::Update(_DeltaTime);

	//������ Trans ����
	Update_RenderTrans();
	
	switch (CurState)
	{
	case FieldNPCBase::State::Idle:
		Update_Idle(_DeltaTime);
		break;
	case FieldNPCBase::State::React:
		Update_React(_DeltaTime);
		break;
	}
}



void FieldNPCBase::Update_RenderTrans()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render = GetRenderer();
	GameEngineTransform* RenderTrans = Render->GetTransform();

	std::string CurTexName = Render->GetTexName();
	std::shared_ptr<GameEngineTexture> TexPtr = GameEngineTexture::Find(CurTexName);
	if (nullptr == TexPtr)
	{
		MsgAssert("�̷� �̸��� ���� �ؽ�ó�� ����� �� ���� �����ϴ� : " + CurTexName);
		return;
	}

	float4 TexScale = TexPtr->GetScale() * RCGDefine::ResourceScaleConvertor;
	RenderTrans->SetLocalScale(TexScale);
	RenderTrans->SetLocalPosition(float4::Up * TexScale.hy());
}



void FieldNPCBase::Update_Idle(float _DeltaTime)
{

}



void FieldNPCBase::React()
{
	//�̹� React ���϶��� return
	if (State::React == CurState)
		return;

	//���� �� �ִϸ��̼� ����
	CurState = State::React;
	GetRenderer()->ChangeAnimation(ReactAniName);

	//�÷��̾� �ٶ󺸱� ������ ��쿡��
	if (false == IsLookPlayer)
		return;

	GameEngineTransform* PlayerTrans = FieldPlayer::GetPtr()->GetTransform();
	GameEngineTransform* ThisTrans = GetTransform();

	float4 PlayerPos = PlayerTrans->GetWorldPosition();
	float4 ThisPos = ThisTrans->GetWorldPosition();

	float4 DirToPlayer = (PlayerPos - ThisPos);

	//�÷��̾� �ٶ󺸱�
	if (0.f < DirToPlayer.x)
	{
		ThisTrans->SetLocalPositiveScaleX();
	}
	else
	{
		ThisTrans->SetLocalNegativeScaleX();
	}
}



void FieldNPCBase::Update_React(float _DeltaTime) 
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetRenderer()->ChangeAnimation(IdleAniName);
	CurState = State::Idle;
}


