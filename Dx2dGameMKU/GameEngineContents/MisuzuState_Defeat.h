#pragma once
#include "EnemyStateBase.h"

class MisuzuState_Defeat : public EnemyStateBase
{
public:
	MisuzuState_Defeat();
	~MisuzuState_Defeat() override;

	MisuzuState_Defeat(const MisuzuState_Defeat& _Other) = delete;
	MisuzuState_Defeat(MisuzuState_Defeat&& _Other) noexcept = delete;
	MisuzuState_Defeat& operator=(const MisuzuState_Defeat& _Other) = delete;
	MisuzuState_Defeat& operator=(const MisuzuState_Defeat&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view Sink_AniName;
	static const std::string_view Cry_AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	bool IsCrying = false;

	void LoadAnimation();
	void CreateAnimation();
};

