#include "PrecompileHeader.h"
#include "FieldDoor.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "RCGDefine.h"
#include "FieldPlayer.h"
#include "Fader.h"

const std::string_view FieldDoor::LockDoorName = "LOCKED_DOOR.png";
const float4 FieldDoor::LockDoorScale = float4{ 76.f, 113.f } * 0.7f;

const std::string_view FieldDoor::UnlockDoorName = "UNLOCKED_DOOR.png";
const float4 FieldDoor::UnlockDoorScale = float4{ 78.f, 114.f } *0.7f;

const std::string_view FieldDoor::ShopIconName = "ShopDoor.png";
const float4 FieldDoor::ShopIconScale = float4{ 117.f, 101.f } *0.7f;

const std::string_view FieldDoor::GymIconName = "GymDoor.png";
const float4 FieldDoor::GymIconScale = float4{ 123.f, 91.f } *0.7f;


LevelNames FieldDoor::RegistNextLevel = LevelNames::OpeningLevel;

FieldDoor::FieldDoor()
{

}

FieldDoor::~FieldDoor()
{

}


void FieldDoor::Init(DoorType _Type)
{
	//리소스 로드
	ImgResLoad();

	ImageType = _Type;
	switch (_Type)
	{
	case DoorType::Normal:
	{
		CreateDoorImage(LockDoorName, LockDoorScale, true);
		CreateDoorImage(UnlockDoorName, UnlockDoorScale, false);

		LockRender->On();
		UnlockRender->Off();
		break;
	}
	case DoorType::Gym:
	{
		CreateDoorImage(GymIconName, GymIconScale, false);
		break;
	}
	case DoorType::Shop:
	{
		CreateDoorImage(ShopIconName, ShopIconScale, false);
		break;
	}
	default:
		break;
	}

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

	IsLoad = true;
}


void FieldDoor::CreateDoorImage(
	const std::string_view& _ImageName, 
	const float4& _Scale, 
	bool _IsLockImage)
{
	std::shared_ptr<GameEngineRenderer> RenderPtr = nullptr;

	RenderPtr = CreateComponent<GameEngineRenderer>();
	RenderPtr->SetPipeLine("FieldDoor");
	RenderPtr->GetShaderResHelper().SetTexture(RCGDefine::EngineTexName, _ImageName);
	RenderPtr->GetShaderResHelper().SetConstantBufferLink("AlphaRatio", AlphaRatio);
	RenderPtr->GetTransform()->SetLocalScale(_Scale);

	if (true == _IsLockImage)
	{
		LockRender = RenderPtr;
	}
	else
	{
		UnlockRender = RenderPtr;
	}

}





void FieldDoor::Update(float _DeltaTime)
{
	if (nullptr == UnlockRender)
	{
		MsgAssert("어떤 종류의 문인지 초기화해주지 않았습니다");
		return;
	}


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

	AlphaRatio.x = 0.f;
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

	if (nullptr != LockRender)
	{
		LockRender->Off();
	}

	if (nullptr == UnlockRender)
	{
		MsgAssert("사용하려는 문 이미지를 만들어주지 않았습니다");
		return;
	}

	UnlockRender->On();
	DoorLockValue = false;
}