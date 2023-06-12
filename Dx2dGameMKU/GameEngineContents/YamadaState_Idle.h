#pragma once
#include "BossState_IdleBase.h"

class YamadaState_Idle : public BossState_IdleBase
{
public:
	YamadaState_Idle();
	~YamadaState_Idle() override;

	YamadaState_Idle(const YamadaState_Idle& _Other) = delete;
	YamadaState_Idle(YamadaState_Idle&& _Other) noexcept = delete;
	YamadaState_Idle& operator=(const YamadaState_Idle& _Other) = delete;
	YamadaState_Idle& operator=(const YamadaState_Idle&& _Other) noexcept = delete;

	static const std::vector<int> FarAttackPercent;
	static const float SightRadius;

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

