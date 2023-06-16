#pragma once
#include "PlayerState_MovementBase.h"

enum class KeyNames;

class PlayerState_Idle : public PlayerState_MovementBase
{
public:
	PlayerState_Idle();
	~PlayerState_Idle() override;

	PlayerState_Idle(const PlayerState_Idle& _Other) = delete;
	PlayerState_Idle(PlayerState_Idle&& _Other) noexcept = delete;
	PlayerState_Idle& operator=(const PlayerState_Idle& _Other) = delete;
	PlayerState_Idle& operator=(const PlayerState_Idle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;
	

	std::vector<KeyNames> ArrowKeyNames;
	size_t NextQuickAttackType = -1;
	float LastQuickAttackTime = 0.f;

	void SetArrowKey();
	void LoadAnimation();
	void CreateAnimation();

};

