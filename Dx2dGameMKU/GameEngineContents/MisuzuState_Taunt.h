#pragma once
#include "EnemyStateBase.h"

class MisuzuState_Taunt : public EnemyStateBase
{
public:
	MisuzuState_Taunt();
	~MisuzuState_Taunt() override;

	MisuzuState_Taunt(const MisuzuState_Taunt& _Other) = delete;
	MisuzuState_Taunt(MisuzuState_Taunt&& _Other) noexcept = delete;
	MisuzuState_Taunt& operator=(const MisuzuState_Taunt& _Other) = delete;
	MisuzuState_Taunt& operator=(const MisuzuState_Taunt&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;
	static const std::vector<std::string_view> LaughSounds;

	size_t SoundIndex = 0;

	void LoadAnimation();
	void CreateAnimation();
};

