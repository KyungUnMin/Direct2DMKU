#pragma once
#include "EnemyState_WalkBase.h"

class HooliganState_Walk : public EnemyState_WalkBase
{
public:
	HooliganState_Walk();
	~HooliganState_Walk() override;

	HooliganState_Walk(const HooliganState_Walk& _Other) = delete;
	HooliganState_Walk(HooliganState_Walk&& _Other) noexcept = delete;
	HooliganState_Walk& operator=(const HooliganState_Walk& _Other) = delete;
	HooliganState_Walk& operator=(const HooliganState_Walk&& _Other) noexcept = delete;

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

