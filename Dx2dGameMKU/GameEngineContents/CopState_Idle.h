#pragma once
#include "EnemyState_IdleBase.h"

class CopState_Idle : public EnemyState_IdleBase
{
public:
	CopState_Idle();
	~CopState_Idle() override;

	CopState_Idle(const CopState_Idle& _Other) = delete;
	CopState_Idle(CopState_Idle&& _Other) noexcept = delete;
	CopState_Idle& operator=(const CopState_Idle& _Other) = delete;
	CopState_Idle& operator=(const CopState_Idle&& _Other) noexcept = delete;

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

