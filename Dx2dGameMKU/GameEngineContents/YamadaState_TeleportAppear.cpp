#include "PrecompileHeader.h"
#include "YamadaState_TeleportAppear.h"


#include "YamadaFSM.h"

#include "FieldEnemyBase.h"
#include "FieldPlayer.h"
#include "BackGround.h"

const std::string_view YamadaState_TeleportAppear::AniName = "TeleportAppear";
const std::string_view YamadaState_TeleportAppear::AniFileName = "Yamada_TeleportAppear.png";
const std::pair<int, int> YamadaState_TeleportAppear::AniCutFrame = std::pair<int, int>(5, 2);
const float YamadaState_TeleportAppear::AniInterTime = 0.06f;
const float YamadaState_TeleportAppear::TeleportOffset = 150.f;


YamadaState_TeleportAppear::YamadaState_TeleportAppear()
{

}

YamadaState_TeleportAppear::~YamadaState_TeleportAppear()
{

}

void YamadaState_TeleportAppear::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimation();

	SettingRenderInfo();
}

void YamadaState_TeleportAppear::SettingRenderInfo()
{
	ShadowRender = GetEnemy()->GetShadowRender();
	OriginShadowRenderScale = ShadowRender->GetTransform()->GetLocalScale();
	OriginEnemyRenderScale = GetRenderer()->GetTransform()->GetLocalScale();
}

void YamadaState_TeleportAppear::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Yamada");
	Dir.Move("Movement");
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileName).GetFullPath(), AniCutFrame.first, AniCutFrame.second);
}

void YamadaState_TeleportAppear::CreateAnimation()
{
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniFileName,
		.FrameInter = AniInterTime,
		.Loop = false,
		});
}


void YamadaState_TeleportAppear::EnterState()
{
	Teleport();
	EnemyStateBase::EnterState();

	GetRenderer()->ChangeAnimation(AniName);

	GetRenderer()->GetTransform()->SetLocalScale(float4::Zero);
	ShadowRender->GetTransform()->SetLocalScale(float4::Zero);
}



void YamadaState_TeleportAppear::Teleport()
{
	std::shared_ptr<BackGround> BGPtr = EnemyStateBase::GetBackGround();

	GameEngineTransform* EnemyTrans = GetEnemy()->GetTransform();
	GameEngineTransform* PlayerTrans = FieldPlayer::GetPtr()->GetTransform();
	float4 TelePos = PlayerTrans->GetWorldPosition();

	//플레이어가 Enemy의 왼쪽에 있는 경우
	if (0.f < EnemyStateBase::GetVecToPlayer().x)
	{
		TelePos += (float4::Right * TeleportOffset);
	}

	//플레이어가 Enemy의 오른쪽에 있는 경우
	else
	{
		TelePos += (float4::Left * TeleportOffset);
	}
	
	//순간이동 하려는 곳이 막힌 경우
	std::pair<int, int> TeleGridPos = BGPtr->GetGridFromPos(TelePos);
	if (true == BGPtr->IsBlockPos(TelePos) || true == BGPtr->IsBlockGrid(TeleGridPos.first, TeleGridPos.second))
	{
		//맵 중앙으로 이동
		EnemyTrans->SetLocalPosition(float4::Zero);
		NextState = static_cast<size_t>(YamadaStateType::Idle);
		return;
	}
	
	//순간 이동 하려는 곳이 막히지 않았다면 그 곳으로 이동하고 바로 Blast공격을 수행
	EnemyTrans->SetLocalPosition(TelePos);
	NextState = static_cast<size_t>(YamadaStateType::Blast);
}


void YamadaState_TeleportAppear::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	Update_Scale();

	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(NextState);
}


void YamadaState_TeleportAppear::Update_Scale()
{
	float Ratio = (GetLiveTime()/ Duration);

	float4 NowRenderScale = float4::LerpClamp(float4::Zero, OriginEnemyRenderScale, Ratio);
	float4 NowShadowScale = float4::LerpClamp(float4::Zero, OriginShadowRenderScale, Ratio);

	GetRenderer()->GetTransform()->SetLocalScale(NowRenderScale);
	ShadowRender->GetTransform()->SetLocalScale(NowShadowScale);
}


void YamadaState_TeleportAppear::ExitState()
{
	EnemyStateBase::ExitState();

	GetRenderer()->GetTransform()->SetLocalScale(OriginEnemyRenderScale);
	ShadowRender->GetTransform()->SetLocalScale(OriginShadowRenderScale);
}