#pragma once
#include "EnemyState_IdleBase.h"

class TigerManState_Idle : public EnemyState_IdleBase
{
public:
	TigerManState_Idle();
	~TigerManState_Idle() override;

	TigerManState_Idle(const TigerManState_Idle& _Other) = delete;
	TigerManState_Idle(TigerManState_Idle&& _Other) noexcept = delete;
	TigerManState_Idle& operator=(const TigerManState_Idle& _Other) = delete;
	TigerManState_Idle& operator=(const TigerManState_Idle&& _Other) noexcept = delete;

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

