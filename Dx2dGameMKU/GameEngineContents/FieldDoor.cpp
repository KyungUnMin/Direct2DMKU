#include "PrecompileHeader.h"
#include "FieldDoor.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "RCGDefine.h"
#include "FieldPlayer.h"
#include "Fader.h"

const std::string_view FieldDoor::LockDoorName = "LOCKED_DOOR.png";
const std::string_view FieldDoor::UnlockDoorName = "UNLOCKED_DOOR.png";
const float4 FieldDoor::LockDoorScale = float4{ 76.f, 113.f } * 0.7f;
const float4 FieldDoor::UnlockDoorScale = float4{ 78.f, 114.f } *0.7f;

LevelNames FieldDoor::RegistNextLevel = LevelNames::OpeningLevel;

FieldDoor::FieldDoor()
{

}

FieldDoor::~FieldDoor()
{

}



void FieldDoor::Start()
{
	//리소스 로드
	ImgResLoad();

	//이미지 만들기
	CreateDoorImg();

	CreateScaleState();
	CreateAlphsState();
}


void FieldDoor::ImgResLoad()
{
	static bool IsLoad = false;
	if (true == IsLoad)
		return;

	GameEngineDirectory Dir;
	RCGDefine::MoveContentPath(Dir, ResType::Image);
	Dir.Move("Door");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" });

	for (const GameEngineFile& File : Files)
	{
		GameEngineTexture::Load(File.GetFullPath());
	}
}


void FieldDoor::CreateDoorImg()
{
	LockRender = CreateComponent<GameEngineRenderer>();
	LockRender->SetPipeLine("FieldDoor");
	LockRender->GetShaderResHelper().SetTexture(RCGDefine::EngineTexName, LockDoorName);
	LockRender->GetShaderResHelper().SetConstantBufferLink("AlphaRatio", AlphaRatio);
	LockRender->GetTransform()->SetLocalScale(LockDoorScale);

	UnlockRender = CreateComponent<GameEngineRenderer>();
	UnlockRender->SetPipeLine("FieldDoor");
	UnlockRender->GetShaderResHelper().SetTexture(RCGDefine::EngineTexName, UnlockDoorName);
	UnlockRender->GetShaderResHelper().SetConstantBufferLink("AlphaRatio", AlphaRatio);
	UnlockRender->GetTransform()->SetLocalScale(UnlockDoorScale);

	UnlockRender->Off();
}





void FieldDoor::Update(float _DeltaTime)
{
	CheckNearPlayer();

	ScaleFSM.Update(_DeltaTime);

	if (true == DoorLockValue)
		return;

	AlphaFSM.Update(_DeltaTime);

	if (AlphaRatio.x < 1.f)
		return;

	//Fader
	FieldDoor::RegistNextLevel = NextLevel;
	GetLevel()->CreateActor<Fader>()->Init(float4{ 0.f, 0.f, 0.f, 0.f }, FadeTime, []()
	{
		LevelMgr::ChangeLevel(FieldDoor::RegistNextLevel);
	});

	ScaleFSM.ChangeState(State::Wait);
	AlphaFSM.ChangeState(State::Wait);
}


void FieldDoor::CheckNearPlayer()
{
	std::shared_ptr<FieldPlayer> Player = FieldPlayer::GetPtr();
	if (nullptr == Player)
	{
		MsgAssert("플레이어가 존재하지 않습니다");
	}

	float4 PlayerPos = Player->GetTransform()->GetWorldPosition();
	float4 ThisPos = GetTransform()->GetWorldPosition();
	PlayerPos.z = 0.f;
	ThisPos.z = 0.f;


	const float Range = 100.f;
	float Distance = (PlayerPos - ThisPos).Size();

	IsNearPlayer = (Distance < Range);
}



void FieldDoor::Unlock(LevelNames _NextLevel)
{
	NextLevel = _NextLevel;
	LockRender->Off();
	UnlockRender->On();
	DoorLockValue = false;
}