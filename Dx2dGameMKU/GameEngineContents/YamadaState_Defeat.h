#pragma once
#include "EnemyStateBase.h"

class YamadaState_Defeat : public EnemyStateBase
{
public:
	YamadaState_Defeat();
	~YamadaState_Defeat() override;

	YamadaState_Defeat(const YamadaState_Defeat& _Other) = delete;
	YamadaState_Defeat(YamadaState_Defeat&& _Other) noexcept = delete;
	YamadaState_Defeat& operator=(const YamadaState_Defeat& _Other) = delete;
	YamadaState_Defeat& operator=(const YamadaState_Defeat&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view Sink_AniName;
	static const std::string_view Shudder_AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	bool IsCrying = false;

	void LoadAnimation();
	void CreateAnimation();
};

