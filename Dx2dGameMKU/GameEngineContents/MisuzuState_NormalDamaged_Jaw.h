#pragma once
#include "EnemyState_DamagedBase.h"

class MisuzuState_NormalDamaged_Jaw : public EnemyState_DamagedBase
{
public:
	MisuzuState_NormalDamaged_Jaw();
	~MisuzuState_NormalDamaged_Jaw() override;

	MisuzuState_NormalDamaged_Jaw(const MisuzuState_NormalDamaged_Jaw& _Other) = delete;
	MisuzuState_NormalDamaged_Jaw(MisuzuState_NormalDamaged_Jaw&& _Other) noexcept = delete;
	MisuzuState_NormalDamaged_Jaw& operator=(const MisuzuState_NormalDamaged_Jaw& _Other) = delete;
	MisuzuState_NormalDamaged_Jaw& operator=(const MisuzuState_NormalDamaged_Jaw&& _Other) noexcept = delete;

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

