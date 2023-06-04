#pragma once
#include "EnemyState_WalkBase.h"

class MisuzuState_Walk : public EnemyState_WalkBase
{
public:
	MisuzuState_Walk();
	~MisuzuState_Walk() override;

	MisuzuState_Walk(const MisuzuState_Walk& _Other) = delete;
	MisuzuState_Walk(MisuzuState_Walk&& _Other) noexcept = delete;
	MisuzuState_Walk& operator=(const MisuzuState_Walk& _Other) = delete;
	MisuzuState_Walk& operator=(const MisuzuState_Walk&& _Other) noexcept = delete;

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

