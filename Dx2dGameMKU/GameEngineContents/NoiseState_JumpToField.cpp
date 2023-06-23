#include "PrecompileHeader.h"
#include "NoiseState_JumpToField.h"

#include <GameEngineCore/GameEngineCollision.h>

#include "RCGEnums.h"

#include "NoiseFSM.h"

#include "FieldEnemyBase.h"
#include "FieldCamController.h"
#include "FieldLevelBase.h"
#include "NoiseFloor.h"
#include "FieldPlayer.h"
#include "GlichSideAttack.h"

const std::vector<std::string_view> NoiseState_JumpToField::AniFileNames =
{
	"Noise_JumpToField1.png",
	"Noise_JumpToField2.png",
	"Noise_LandField1.png",
	"Noise_LandField2.png",
	"Noise_LandField3.png",
	"Noise_LandField4.png",
};

const float NoiseState_JumpToField::AniInterTime = 0.08f;
const size_t NoiseState_JumpToField::HandsUpLoopCount = 10;

NoiseState_JumpToField::NoiseState_JumpToField()
{

}

NoiseState_JumpToField::~NoiseState_JumpToField()
{

}

void NoiseState_JumpToField::Start()
{
	EnemyStateBase::Start();

	LoadAnimation();
	CreateAnimations();
	EnemyStateBase::SetUnbeatable();

	Shadow = GetEnemy()->GetShadowRender();
}

void NoiseState_JumpToField::LoadAnimation()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	IsLoad = true;
	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Character");
	Dir.Move("Enemy");
	Dir.Move("Noise");
	Dir.Move("Movement");
	Dir.Move("JumpToField");

	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileNames[static_cast<size_t>(State::Ready)]).GetFullPath(), 5, 1);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileNames[static_cast<size_t>(State::Jump)]).GetFullPath(), 5, 1);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileNames[static_cast<size_t>(State::Fall)]).GetFullPath(), 5, 1);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileNames[static_cast<size_t>(State::Land)]).GetFullPath(), 5, 3);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileNames[static_cast<size_t>(State::Struct)]).GetFullPath(), 5, 2);
	GameEngineSprite::LoadSheet(Dir.GetPlusFileName(AniFileNames[static_cast<size_t>(State::UnStruct)]).GetFullPath(), 5, 2);
}

void NoiseState_JumpToField::CreateAnimations()
{
	CreateAnimation(State::Ready, 4, false);
	CreateAnimation(State::Jump, 2, false);
	CreateAnimation(State::Fall, 3, false);

	
	std::vector<size_t> LandAniFrms;
	LandAniFrms.reserve(8 + (5 * HandsUpLoopCount));

	for (size_t i = 0; i < 7; ++i)
	{
		LandAniFrms.push_back(i);
	}
	for (size_t i = 0; i < HandsUpLoopCount; ++i)
	{
		for (size_t j = 7; j < 12; ++j)
		{
			LandAniFrms.push_back(j);
		}
	}
	LandAniFrms.push_back(12);
	CreateAnimation(State::Land, LandAniFrms, false);

	CreateAnimation(State::Struct, 8, true);
	CreateAnimation(State::UnStruct, 5, false);
}


void NoiseState_JumpToField::CreateAnimation(State _StateaAni, size_t _EndFrm, bool _Loop)
{
	const std::string_view& AniName = AniFileNames[static_cast<size_t>(_StateaAni)];
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniName,
		.Start = 0,
		.End = _EndFrm,
		.FrameInter = AniInterTime,
		.Loop = _Loop,
	});
}

void NoiseState_JumpToField::CreateAnimation(State _StateaAni, const std::vector<size_t>& _AniFrms, bool _Loop)
{
	const std::string_view& AniName = AniFileNames[static_cast<size_t>(_StateaAni)];
	GetRenderer()->CreateAnimation
	({
		.AnimationName = AniName,
		.SpriteName = AniName,
		.FrameInter = AniInterTime,
		.Loop = _Loop,
		.FrameIndex = _AniFrms,
	});
}



void NoiseState_JumpToField::EnterState()
{
	EnemyStateBase::EnterState();

	ChangeStateAndAni(State::Ready);

	std::shared_ptr<FieldPlayer> Player = FieldPlayer::GetPtr();
	GameEngineTransform* PlayerColTrans = Player->GetMainCollider()->GetTransform();
	OriginPlayerColScale = PlayerColTrans->GetLocalScale();
	PlayerColTrans->SetLocalScale(float4::One * 10.f);
	Player->GetAttackCollider()->SetColType(ColType::MAX);
}



void NoiseState_JumpToField::ChangeStateAndAni(State _Next)
{
	ResetLiveTime();

	CurState = _Next;
	size_t Index = static_cast<size_t>(CurState);
	const std::string_view& AniName = AniFileNames[Index];
	GetRenderer()->ChangeAnimation(AniName);
}




void NoiseState_JumpToField::Update(float _DeltaTime)
{
	EnemyStateBase::Update(_DeltaTime);

	switch (CurState)
	{
	case NoiseState_JumpToField::State::Ready:
		Update_Ready(_DeltaTime);
		break;
	case NoiseState_JumpToField::State::Jump:
		Update_Jump(_DeltaTime);
		break;
	case NoiseState_JumpToField::State::Fall:
		Update_Fall(_DeltaTime);
		break;
	case NoiseState_JumpToField::State::Land:
		Update_Land(_DeltaTime);
		break;
	case NoiseState_JumpToField::State::Struct:
		Update_Struct(_DeltaTime);
		break;
	case NoiseState_JumpToField::State::UnStruct:
		Update_UnStruct(_DeltaTime);
		break;
	}
}




void NoiseState_JumpToField::Update_Ready(float _DeltaTime)
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	if (false == NoiseFloor::IsAllClear())
		return;

	ChangeStateAndAni(State::Jump);
}


void NoiseState_JumpToField::Update_Jump(float _DeltaTime)
{
	static const float Duration = 0.5f;
	static const float MaxHeight = 1000.f;

	EnemyStateBase::Update_SinHalfJump(Duration, MaxHeight);

	float Ratio = GetLiveTime() / Duration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	Shadow->ColorOptionValue.MulColor.a = (1.f - ClampRatio);

	if (Ratio < 1.f)
		return;

	//이동
	GameEngineTransform* PlayerTrans = FieldPlayer::GetPtr()->GetTransform();
	GameEngineTransform* EnemyTrans = GetEnemy()->GetTransform();

	float4 PlayerPos = PlayerTrans->GetWorldPosition();
	float4 NextPos = float4{ 0.f, PlayerPos.y, PlayerPos.y };
	EnemyTrans->SetLocalPosition(NextPos);


	//카메라 조정
	FieldCamController& CamCtrl = FieldLevelBase::GetPtr()->GetCameraController();
	CamCtrl.SetTraceState();
	FieldCamController::ZoomOrigin = 1.0f;
	CamCtrl.SetZoom(FieldCamController::ZoomOrigin, 0.1f);
	
	ChangeStateAndAni(State::Fall);
}


void NoiseState_JumpToField::Update_Fall(float _DeltaTime)
{
	static const float Duration = 1.0f;
	static const float MaxHeight = 2000.f;

	EnemyStateBase::Update_SinHalfFall(Duration, MaxHeight);

	float Ratio = GetLiveTime() / Duration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	Shadow->ColorOptionValue.MulColor.a = ClampRatio;

	if (Ratio < 1.f)
		return;

	float4 EnemyPos = GetEnemy()->GetTransform()->GetWorldPosition();
	AttackEffect = FieldLevelBase::GetPtr()->CreateActor<GlichSideAttack>(UpdateOrder::Effect);
	AttackEffect->Init(EnemyPos + float4::Forward);

	ChangeStateAndAni(State::Land);
}


void NoiseState_JumpToField::Update_Land(float _DeltaTime)
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	AttackEffect->WaveOff();
	AttackEffect = nullptr;
	ChangeStateAndAni(State::Struct);
}


void NoiseState_JumpToField::Update_Struct(float _DeltaTime)
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	ChangeStateAndAni(State::UnStruct);
}

void NoiseState_JumpToField::Update_UnStruct(float _DeltaTime) 
{
	if (false == GetRenderer()->IsAnimationEnd())
		return;

	GetFSM()->ChangeState(NoiseStateType::Idle);
}


void NoiseState_JumpToField::ExitState()
{
	EnemyStateBase::ExitState();

	if (nullptr != AttackEffect)
	{
		AttackEffect->WaveOff();
		AttackEffect = nullptr;
	}

	std::shared_ptr<FieldPlayer> Player = FieldPlayer::GetPtr();
	Player->GetMainCollider()->GetTransform()->SetLocalScale(OriginPlayerColScale);
	Player->GetAttackCollider()->SetColType(ColType::SPHERE3D);
}