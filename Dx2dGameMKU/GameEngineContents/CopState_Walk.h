#pragma once
#include "EnemyState_WalkBase.h"

class CopState_Walk : public EnemyState_WalkBase
{
public:
	CopState_Walk();
	~CopState_Walk() override;

	CopState_Walk(const CopState_Walk& _Other) = delete;
	CopState_Walk(CopState_Walk&& _Other) noexcept = delete;
	CopState_Walk& operator=(const CopState_Walk& _Other) = delete;
	CopState_Walk& operator=(const CopState_Walk&& _Other) noexcept = delete;

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

