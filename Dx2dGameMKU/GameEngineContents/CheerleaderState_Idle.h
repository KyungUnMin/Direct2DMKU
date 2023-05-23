#pragma once
#include "EnemyStateBase.h"

class CheerleaderState_Idle : public EnemyStateBase
{
public:
	CheerleaderState_Idle();
	~CheerleaderState_Idle() override;

	CheerleaderState_Idle(const CheerleaderState_Idle& _Other) = delete;
	CheerleaderState_Idle(CheerleaderState_Idle&& _Other) noexcept = delete;
	CheerleaderState_Idle& operator=(const CheerleaderState_Idle& _Other) = delete;
	CheerleaderState_Idle& operator=(const CheerleaderState_Idle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	void LoadAnimation();
	void CreateAnimation();
};

