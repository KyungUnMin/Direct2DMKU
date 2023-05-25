#pragma once
#include "EnemyState_IdleBase.h"

class HooliganState_Idle : public EnemyState_IdleBase
{
public:
	HooliganState_Idle();
	~HooliganState_Idle() override;

	HooliganState_Idle(const HooliganState_Idle& _Other) = delete;
	HooliganState_Idle(HooliganState_Idle&& _Other) noexcept = delete;
	HooliganState_Idle& operator=(const HooliganState_Idle& _Other) = delete;
	HooliganState_Idle& operator=(const HooliganState_Idle&& _Other) noexcept = delete;

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

