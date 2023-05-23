#pragma once
#include "EnemyState_WalkBase.h"

class CheerleaderState_Walk : public EnemyState_WalkBase
{
public:
	CheerleaderState_Walk();
	~CheerleaderState_Walk() override;

	CheerleaderState_Walk(const CheerleaderState_Walk& _Other) = delete;
	CheerleaderState_Walk(CheerleaderState_Walk&& _Other) noexcept = delete;
	CheerleaderState_Walk& operator=(const CheerleaderState_Walk& _Other) = delete;
	CheerleaderState_Walk& operator=(const CheerleaderState_Walk&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	void LoadAnimation();
	void CreateAnimation();
};

