#pragma once
#include "EnemyState_WalkBase.h"

class YamadaState_Walk : public EnemyState_WalkBase
{
public:
	YamadaState_Walk();
	~YamadaState_Walk() override;

	YamadaState_Walk(const YamadaState_Walk& _Other) = delete;
	YamadaState_Walk(YamadaState_Walk&& _Other) noexcept = delete;
	YamadaState_Walk& operator=(const YamadaState_Walk& _Other) = delete;
	YamadaState_Walk& operator=(const YamadaState_Walk&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;

	bool ChangeStateWhenFarWithAwayPlayer() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	class BossFSMBase* BossFsmPtr = nullptr;

	void LoadAnimation();
	void CreateAnimation();
};

