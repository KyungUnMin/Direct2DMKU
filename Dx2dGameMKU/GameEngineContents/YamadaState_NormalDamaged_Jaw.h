#pragma once
#include "EnemyState_DamagedBase.h"

class YamadaState_NormalDamaged_Jaw : public EnemyState_DamagedBase
{
public:
	YamadaState_NormalDamaged_Jaw();
	~YamadaState_NormalDamaged_Jaw() override;

	YamadaState_NormalDamaged_Jaw(const YamadaState_NormalDamaged_Jaw& _Other) = delete;
	YamadaState_NormalDamaged_Jaw(YamadaState_NormalDamaged_Jaw&& _Other) noexcept = delete;
	YamadaState_NormalDamaged_Jaw& operator=(const YamadaState_NormalDamaged_Jaw& _Other) = delete;
	YamadaState_NormalDamaged_Jaw& operator=(const YamadaState_NormalDamaged_Jaw&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::pair<int, int> AniCutFrame;
	static const std::pair<size_t, size_t> AniFrameIndex;
	static const float AniInterTime;

	void LoadAnimation();
	void CreateAnimation();
};

