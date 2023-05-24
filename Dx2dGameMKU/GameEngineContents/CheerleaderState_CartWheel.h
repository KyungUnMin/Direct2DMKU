#pragma once
#include "EnemyStateBase.h"

class CheerleaderState_CartWheel : public EnemyStateBase
{
public:
	CheerleaderState_CartWheel();
	~CheerleaderState_CartWheel() override;

	CheerleaderState_CartWheel(const CheerleaderState_CartWheel& _Other) = delete;
	CheerleaderState_CartWheel(CheerleaderState_CartWheel&& _Other) noexcept = delete;
	CheerleaderState_CartWheel& operator=(const CheerleaderState_CartWheel& _Other) = delete;
	CheerleaderState_CartWheel& operator=(const CheerleaderState_CartWheel&& _Other) noexcept = delete;

	void MoveOn()
	{
		MoveOnValue = true;
		MoveStartTime = GetLiveTime();
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;
	static const float Duration;
	static const float StartMoveAcc;

	bool MoveOnValue = false;
	float MoveStartTime = 0.f;
	float4 MoveDir = float4::Zero;

	const float EffectCreateTime = 0.1f;
	float EffectTimer = 0.f;

	void LoadAnimation();
	void CreateAnimation();
};

