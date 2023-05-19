#pragma once
#include "EnemyState_DamagedBase.h"

class SchoolBoyState_Damaged_BlowBack : public EnemyState_DamagedBase
{
public:
	SchoolBoyState_Damaged_BlowBack();
	~SchoolBoyState_Damaged_BlowBack() override;

	SchoolBoyState_Damaged_BlowBack(const SchoolBoyState_Damaged_BlowBack& _Other) = delete;
	SchoolBoyState_Damaged_BlowBack(SchoolBoyState_Damaged_BlowBack&& _Other) noexcept = delete;
	SchoolBoyState_Damaged_BlowBack& operator=(const SchoolBoyState_Damaged_BlowBack& _Other) = delete;
	SchoolBoyState_Damaged_BlowBack& operator=(const SchoolBoyState_Damaged_BlowBack&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const std::pair<size_t, size_t> AniFrameIndex;
	static const float AniInterTime;

	const float Duration = 0.5f;

	void LoadAnimation();
	void CreateAnimation();
	
};

