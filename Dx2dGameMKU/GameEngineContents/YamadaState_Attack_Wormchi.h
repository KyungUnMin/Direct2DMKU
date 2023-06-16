#pragma once
#include "BossState_AttackBase.h"

class YamadaState_Attack_Wormchi : public BossState_AttackBase
{
public:
	YamadaState_Attack_Wormchi();
	~YamadaState_Attack_Wormchi() override;

	YamadaState_Attack_Wormchi(const YamadaState_Attack_Wormchi& _Other) = delete;
	YamadaState_Attack_Wormchi(YamadaState_Attack_Wormchi&& _Other) noexcept = delete;
	YamadaState_Attack_Wormchi& operator=(const YamadaState_Attack_Wormchi& _Other) = delete;
	YamadaState_Attack_Wormchi& operator=(const YamadaState_Attack_Wormchi&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

	void Attack() override {}

private:
	static const std::string_view AniFileName;
	static const std::vector<std::string_view> AniNames;
	static const std::pair<int, int> AniCurFrame;
	static const float AniInterTime;
	static const float SitDuration;


	enum class State
	{
		SitDown,
		Sit,
		GetUp
	};

	State CurState = State::SitDown;

	const float AfterEffectTime = 0.05f;
	float AfterEffectTimer = 0.f;

	float SitTime = 0.f;
	std::vector<std::shared_ptr<class YamadaWormchiObj>> ThrowObjs;
	int ThrowIndex = 0;
	float ThrowTimer = 0.f;


	void LoadAnimation();
	void CreateAnimation();
	void CreateThrowObjs();

	void Update_SitDown(float _DeltaTime);
	void Update_Sit(float _DeltaTime);
	void Update_GetUp(float _DeltaTime);
	
	void ChangeStateAndAni(State _Next);
};

