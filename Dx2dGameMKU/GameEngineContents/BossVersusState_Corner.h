#pragma once
#include "StateBase.h"

class SelfRenderer;

class BossVersusState_Corner : public StateBase
{
public:
	BossVersusState_Corner();
	~BossVersusState_Corner() override;

	BossVersusState_Corner(const BossVersusState_Corner& _Other) = delete;
	BossVersusState_Corner(BossVersusState_Corner&& _Other) noexcept = delete;
	BossVersusState_Corner& operator=(const BossVersusState_Corner& _Other) = delete;
	BossVersusState_Corner& operator=(const BossVersusState_Corner&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view CornerBlack_FileName;
	static const std::string_view CornerPink_FileName;

	std::shared_ptr<SelfRenderer> LeftCorner = nullptr;
	std::shared_ptr<SelfRenderer> RightCorner = nullptr;

	enum class State
	{
		Position,
		Scale
	};

	State CurState = State::Position;

	const float PositionDuration = 0.5f;
	const float4 StartOffset = float4{ 300.f, 300.f };
	float4 DestPos = float4::Zero;

	const float ScaleDuration = 1.f;
	float4 OriginScale = float4::Zero;
	const float4 ScaleOffset = float4::One * 50.f;

	std::shared_ptr<SelfRenderer>  CreateCornerRenders();
	void Update_CornerPosition();
	void Update_CornerScale();
};

