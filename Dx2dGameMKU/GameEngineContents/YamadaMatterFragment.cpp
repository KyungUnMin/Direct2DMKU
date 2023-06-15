#include "PrecompileHeader.h"
#include "YamadaMatterFragment.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "RCGEnums.h"

const std::string_view YamadaMatterFragment::Frag_FileName = "MatterCrushFragment (";
const float YamadaMatterFragment::RenderOffset = 50.f;
const float YamadaMatterFragment::Duration = 1.f;
const float4 YamadaMatterFragment::MaxMoveArea = float4{ 150.f, 200.f };
bool YamadaMatterFragment::DirSwitch = false;

YamadaMatterFragment::YamadaMatterFragment()
{

}

YamadaMatterFragment::~YamadaMatterFragment()
{

}

void YamadaMatterFragment::Start()
{
	GameEngineActor::Start();

	CreateRender();
	SettingValue();
}


void YamadaMatterFragment::CreateRender()
{
	int RandNum = GameEngineRandom::MainRandom.RandomInt(1, 7);
	std::string FileName = Frag_FileName.data();
	FileName += GameEngineString::ToString(RandNum);
	FileName += ").png";
	
	Render = CreateComponent<GameEngineSpriteRenderer>(FieldRenderOrder::ZOrder);
	Render->SetScaleToTexture(FileName);


	float OffsetY = GameEngineRandom::MainRandom.RandomFloat(0.f, RenderOffset);
	float OffsetX = GameEngineRandom::MainRandom.RandomFloat(-RenderOffset, RenderOffset);
	Render->GetTransform()->SetLocalPosition({ OffsetX, OffsetY });
}

void YamadaMatterFragment::SettingValue()
{
	MoveArea.x = GameEngineRandom::MainRandom.RandomFloat(0.f, MaxMoveArea.x);
	MoveArea.y = GameEngineRandom::MainRandom.RandomFloat(MaxMoveArea.y * 0.7f, MaxMoveArea.y);

	if (true == DirSwitch)
	{
		MoveArea.x = -MoveArea.x;
	}
	
	DirSwitch = !DirSwitch;
}


void YamadaMatterFragment::Update(float _DeltaTime)
{
	GameEngineActor::Update(_DeltaTime);

	//업데이트 첫 프레임만 동작, 시작 위치를 기억
	if (float4::Null == StartPos)
	{
		StartPos = GetTransform()->GetLocalPosition();
		StartPos.w = 1.f;
	}


	float Ratio = GetLiveTime() / Duration;
	float ClampRatio = std::clamp(Ratio, 0.f, 1.f);
	float SinValueX = sinf(GameEngineMath::PIE * 0.5f * ClampRatio);
	float SinValueY = sinf(GameEngineMath::PIE * ClampRatio);

	float4 Offset = float4::Zero;
	Offset.x = MoveArea.x * SinValueX;
	Offset.y = MoveArea.y * SinValueY;

	GetTransform()->SetLocalPosition(StartPos + Offset);
	Render->ColorOptionValue.MulColor.a = (1.f - ClampRatio);

	if (Ratio < 1.f)
		return;

	Death();
}

