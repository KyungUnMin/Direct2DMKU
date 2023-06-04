#pragma once
#include "EnemyState_IdleBase.h"

class MisuzuState_Idle : public EnemyState_IdleBase
{
public:
	MisuzuState_Idle();
	~MisuzuState_Idle() override;

	MisuzuState_Idle(const MisuzuState_Idle& _Other) = delete;
	MisuzuState_Idle(MisuzuState_Idle&& _Other) noexcept = delete;
	MisuzuState_Idle& operator=(const MisuzuState_Idle& _Other) = delete;
	MisuzuState_Idle& operator=(const MisuzuState_Idle&& _Other) noexcept = delete;

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

