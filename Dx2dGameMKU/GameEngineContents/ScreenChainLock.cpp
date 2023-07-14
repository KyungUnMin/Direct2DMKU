#include "PrecompileHeader.h"
#include "ScreenChainLock.h"

#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineUIRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "RCGEnums.h"
#include "RCGDefine.h"
#include "FieldCamController.h"
#include "SoundMgr.h"

#include "FieldLevelBase.h"



const std::string_view ScreenChainLock::SpriteHeadName = "ScreenChainLock_";

const std::vector<std::string_view> ScreenChainLock::ChainPoses =
{
	"Bottom","Left","Right","Top",
};

const std::vector<std::string_view> ScreenChainLock::ChainStates =
{
	"Launch", "Leave","Wobble",
};

const std::vector<std::string_view> ScreenChainLock::LockStates =
{
	"Appear",
	"Damage1",
	"Damage2",
	"Damage3",
	"Disappear",
};


std::string ScreenChainLock::TempSpriteName;

const std::vector<std::string_view> ScreenChainLock::LockSFX =
{
	"ScreenChainLock_Appear.wav",
	"ScreenChainLock_LockDamage1.wav",
	"ScreenChainLock_LockDamage2.wav",
	"ScreenChainLock_LockDamage3.wav",
	"ScreenChainLock_Break.wav",
};

ScreenChainLock::ScreenChainLock()
{

}

ScreenChainLock::~ScreenChainLock()
{

}

void ScreenChainLock::Start()
{
	GameEngineActor::Start();

	if (static_cast<int>(UpdateOrder::ScreenLock) != GetOrder())
	{
		MsgAssert("이 엑터는 반드시 오더를 UpdateOrder::ScreenLock로 설정해주어야 합니다");
		return;
	}

	LoadImageRes();
	CreateChainRender();
	CreateLockRender();
	CreateCollider();

	EnemySpawner& Spawner = FieldLevelBase::GetPtr()->GetEnemySpawner();
	Spawner.SetKillCallBack(std::bind(&ScreenChainLock::HitLock, this));
}


void ScreenChainLock::LoadImageRes()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;


	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("UI");
	Dir.Move("ScreenChainLock");
	Dir.Move("Chain");
	TempSpriteName.reserve(30);

	//Chain 상하좌우
	for (const std::string_view& ChainPos : ChainPoses)
	{
		Dir.Move(ChainPos);

		//Chain상태
		for (const std::string_view& ChainState : ChainStates)
		{
			GameEnginePath SpritePath = Dir.GetPlusFileName(ChainState);

			TempSpriteName.clear();
			TempSpriteName = SpriteHeadName;
			TempSpriteName += ChainPos.data();
			TempSpriteName += ChainState.data();

			GameEngineSprite::LoadFolder(TempSpriteName, SpritePath.GetFullPath());
		}

		Dir.MoveParentToDirectory(ChainPos);
	}

	//자물쇠 상태
	Dir.MoveParentToDirectory("Lock");
	Dir.Move("Lock");
	for (const std::string_view& LockState : LockStates)
	{
		GameEnginePath SpritePath = Dir.GetPlusFileName(LockState);

		TempSpriteName.clear();
		TempSpriteName = SpriteHeadName;
		TempSpriteName += LockState.data();

		GameEngineSprite::LoadFolder(TempSpriteName, SpritePath.GetFullPath());
	}
	
	IsLoad = true;
}



void ScreenChainLock::CreateChainRender()
{
	const float4 ScreenSize = GameEngineWindow::GetScreenSize();
	const float OffsetY = ScreenSize.hy() - 100.f;
	const std::vector<float4> Offset =
	{
		{0.f,							-OffsetY},	//Bottom
		{-ScreenSize.hx(),	0.f},				//Left
		{ScreenSize.hx(),		0.f},				//Right
		{0.f,							OffsetY},		//Top
	};

	const float ChainWidth = 50.f;

	const std::vector<float4> Scale =
	{
		{ScreenSize.x,	ChainWidth},		//Bottom
		{ChainWidth,	ScreenSize.y},		//Left
		{ChainWidth,	ScreenSize.y},		//Right
		{ScreenSize.x,	ChainWidth},		//Top
	};

	ChainRenders.resize(ChainPoses.size(), nullptr);

	for (size_t PosIdx = 0; PosIdx < ChainRenders.size(); ++PosIdx)
	{
		ChainRenders[PosIdx] = CreateComponent<GameEngineUIRenderer>(FieldUIRenderOrder::ScreenChainLock);

		for (size_t StateIdx = 0; StateIdx < ChainStates.size(); ++StateIdx)
		{
			CreateChainAnimation(PosIdx, StateIdx);
		}

		GameEngineTransform* RenderTrans = ChainRenders[PosIdx]->GetTransform();
		RenderTrans->SetWorldPosition(Offset[PosIdx]);
		RenderTrans->SetWorldScale(Scale[PosIdx]);
		ChainRenders[PosIdx]->ChangeAnimation(ChainStates[static_cast<size_t>(ChainStateType::Launch)]);

		ChainRenders[PosIdx]->Off();
	}
}


void ScreenChainLock::CreateChainAnimation(size_t _PosIdx, size_t _StateIdx)
{
	TempSpriteName.clear();
	TempSpriteName = SpriteHeadName;
	TempSpriteName += ChainPoses[_PosIdx];
	TempSpriteName += ChainStates[_StateIdx];

	ChainRenders[_PosIdx]->CreateAnimation
	({
		.AnimationName = ChainStates[_StateIdx],
		.SpriteName = TempSpriteName,
		.Loop = false,
	});
}

void ScreenChainLock::CreateLockRender()
{
	LockRender = CreateComponent<GameEngineUIRenderer>(FieldUIRenderOrder::ScreenChainLock);
	for (const std::string_view& LockState : LockStates)
	{
		TempSpriteName.clear();
		TempSpriteName = SpriteHeadName;
		TempSpriteName += LockState.data();

		LockRender->CreateAnimation
		({
			.AnimationName = LockState,
			.SpriteName = TempSpriteName,
			.Loop = false,
			.ScaleToImage = true,
		});
	}

	const float4 RenderPos = float4::Up * (GameEngineWindow::GetScreenSize().hy() - 150.f);

	LockRender->ChangeAnimation(LockStates[static_cast<size_t>(LockStateType::Appear)]);
	LockRender->GetTransform()->SetLocalPosition(RenderPos);
	LockRender->Off();
}



void ScreenChainLock::CreateCollider() 
{
	//const float4 ColScale = { 300.f, 100.f, 100.f };
	//const float4 ColPos = { 0.f, 0.f, 0.f };
	
	Collider = CreateComponent<GameEngineCollision>(CollisionOrder::ScreenLock);
	Collider->SetColType(ColType::AABBBOX3D);

	//GameEngineTransform* ColTrans = Collider->GetTransform();
	//ColTrans->SetLocalScale(ColScale);
	//ColTrans->SetLocalPosition(ColPos);
}

void ScreenChainLock::SetTriggerColArea(const float4& _Pos, const float4& _Scale)
{
	GameEngineTransform* ColTrans = Collider->GetTransform();

	float4 Scale = _Scale;
	Scale.z = Scale.y;

	float4 Pos = _Pos;
	Pos.z = Pos.y;

	ColTrans->SetLocalScale(Scale);
	ColTrans->SetLocalPosition(Pos);
}






void ScreenChainLock::Update(float _DeltaTime)
{
	GameEngineActor::Update(_DeltaTime);

	switch (CurState)
	{
	case ScreenChainLock::State::Wait:
		Update_Wait();
		break;
	case ScreenChainLock::State::Lock:
		Update_Lock();
		break;
	case ScreenChainLock::State::Destroy:
		Update_Destroy();
		break;
	}
}


void ScreenChainLock::Update_Wait()
{
	std::shared_ptr<GameEngineCollision> PlayerCol = nullptr;
	PlayerCol = Collider->Collision(CollisionOrder::PlayerMain, ColType::AABBBOX3D, ColType::SPHERE3D);
	if (nullptr == PlayerCol)
		return;


	//충돌 범위 변경
	const float4 ScreenSize = GameEngineWindow::GetScreenSize();
	const float4 Offset = float4{ 200.f, 200.f };

	float4 LockArea = (ScreenSize - Offset);
	LockArea.z = LockArea.y;
	Collider->GetTransform()->SetLocalScale(LockArea);

	
	PlayerTrans = PlayerCol->GetActor()->GetTransform();
	PrevPlayerPos = PlayerTrans->GetWorldPosition();


	CurState = State::Lock;
	LockRender->On();
	for (size_t i = 0; i < ChainRenders.size(); ++i)
	{
		ChainRenders[i]->On();
	}

	float4 CamLookPos = Collider->GetTransform()->GetWorldPosition();
	FieldLevelBase::GetPtr()->GetCameraController().SetFixedState(CamLookPos);

	SoundMgr::PlaySFX(LockSFX[static_cast<size_t>(LockState)]);
	SoundMgr::PlaySFX("ScreenChainLock_ChainLaunch.wav");

	//콜백 호출
	if (nullptr != TriggerCallback)
	{
		TriggerCallback();
		TriggerCallback = nullptr;
	}
}





void ScreenChainLock::Update_Lock()
{
	//이번 프레임에 플레이어가 콜리전 영역안에 있는지 여부
	std::shared_ptr<GameEngineCollision> PlayerCol = nullptr;
	PlayerCol = Collider->Collision(CollisionOrder::PlayerMain, ColType::AABBBOX3D, ColType::SPHERE3D);

	//영역 안에 있다면
	if (nullptr != PlayerCol)
	{
		PrevPlayerPos = PlayerTrans->GetWorldPosition();
		return;
	}
	
	PlayerTrans->SetWorldPosition(PrevPlayerPos);
}


void ScreenChainLock::HitLock()
{
	if (State::Lock != CurState)
		return;

	size_t PrevLockIdx = static_cast<size_t>(LockState);
	size_t NextLockIdx = (PrevLockIdx + 1);
	LockState = static_cast<LockStateType>(NextLockIdx);
	LockRender->ChangeAnimation(LockStates[NextLockIdx]);
	SoundMgr::PlaySFX(LockSFX[static_cast<size_t>(LockState)]);

	if (LockStateType::Disappear == LockState)
	{
		EnemySpawner& Spawner = FieldLevelBase::GetPtr()->GetEnemySpawner();
		Spawner.SetKillCallBack(nullptr);

		LockBreak();
		return;
	}

	const std::string_view& NextChainAni = ChainStates[static_cast<size_t>(ChainStateType::Wobble)];
	for (std::shared_ptr<GameEngineUIRenderer> ChainRender : ChainRenders)
	{
		ChainRender->ChangeAnimation(NextChainAni);
	}
}

void ScreenChainLock::LockBreak()
{
	const std::string_view& NextChainAni = ChainStates[static_cast<size_t>(ChainStateType::Leave)];
	for (std::shared_ptr<GameEngineUIRenderer> ChainRender : ChainRenders)
	{
		ChainRender->ChangeAnimation(NextChainAni);
	}

	FieldLevelBase::GetPtr()->GetCameraController().SetTraceState();

	CurState = State::Destroy;
	SoundMgr::PlaySFX("ScreenChainLock_Break.wav");
	ResetLiveTime();
}

void ScreenChainLock::Update_Destroy()
{
	static const float Duration = 1.f;

	float Ratio = GetLiveTime() / Duration;
	if (1.f < Ratio)
	{
		Death();
		return;
	}

	for (std::shared_ptr<GameEngineUIRenderer> ChainRender : ChainRenders)
	{
		ChainRender->ColorOptionValue.MulColor.a = (1.f - Ratio);
	}
}
