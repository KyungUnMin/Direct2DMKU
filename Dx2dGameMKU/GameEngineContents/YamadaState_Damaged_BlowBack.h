#pragma once
#include "EnemyState_DamagedBase.h"

class YamadaState_Damaged_BlowBack : public EnemyState_DamagedBase
{
public:
	YamadaState_Damaged_BlowBack();
	~YamadaState_Damaged_BlowBack() override;

	YamadaState_Damaged_BlowBack(const YamadaState_Damaged_BlowBack& _Other) = delete;
	YamadaState_Damaged_BlowBack(YamadaState_Damaged_BlowBack&& _Other) noexcept = delete;
	YamadaState_Damaged_BlowBack& operator=(const YamadaState_Damaged_BlowBack& _Other) = delete;
	YamadaState_Damaged_BlowBack& operator=(const YamadaState_Damaged_BlowBack&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	const float StartAcc = 1500.f;
	const float Duration = 0.5f;

	std::shared_ptr<class GameEngineSpriteRenderer> ShadowRender = nullptr;
	const float ShadowDuration = 0.5f;
	float ShadowTime = -1.f;

	void LoadAnimation();
	void CreateAnimation();
	void Update_ShadowScale();
};

