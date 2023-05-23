#pragma once
#include "EnemyState_WalkBase.h"

class TigerManState_Walk : public EnemyState_WalkBase
{
public:
	TigerManState_Walk();
	~TigerManState_Walk() override;

	TigerManState_Walk(const TigerManState_Walk& _Other) = delete;
	TigerManState_Walk(TigerManState_Walk&& _Other) noexcept = delete;
	TigerManState_Walk& operator=(const TigerManState_Walk& _Other) = delete;
	TigerManState_Walk& operator=(const TigerManState_Walk&& _Other) noexcept = delete;

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

