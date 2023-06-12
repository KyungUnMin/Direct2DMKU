#pragma once
#include "EnemyStateBase.h"

class YamadaState_Taunt : public EnemyStateBase
{
public:
	YamadaState_Taunt();
	~YamadaState_Taunt() override;

	YamadaState_Taunt(const YamadaState_Taunt& _Other) = delete;
	YamadaState_Taunt(YamadaState_Taunt&& _Other) noexcept = delete;
	YamadaState_Taunt& operator=(const YamadaState_Taunt& _Other) = delete;
	YamadaState_Taunt& operator=(const YamadaState_Taunt&& _Other) noexcept = delete;

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

