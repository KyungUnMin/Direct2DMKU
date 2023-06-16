#pragma once
#include "EnemyStateBase.h"

class YamadaState_PhaseTransition : public EnemyStateBase
{
public:
	YamadaState_PhaseTransition();
	~YamadaState_PhaseTransition() override;

	YamadaState_PhaseTransition(const YamadaState_PhaseTransition& _Other) = delete;
	YamadaState_PhaseTransition(YamadaState_PhaseTransition&& _Other) noexcept = delete;
	YamadaState_PhaseTransition& operator=(const YamadaState_PhaseTransition& _Other) = delete;
	YamadaState_PhaseTransition& operator=(const YamadaState_PhaseTransition&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	std::shared_ptr<class GameEngineSpriteRenderer> Night = nullptr;

	void LoadAnimation();
	void CreateAnimation();
	void BindNightBackImage();
};

