#pragma once
#include "PlayerState_MovementBase.h"
#include "KeyMgr.h"


class PlayerState_Walk : public PlayerState_MovementBase
{
public:
	PlayerState_Walk();
	~PlayerState_Walk() override;

	PlayerState_Walk(const PlayerState_Walk& _Other) = delete;
	PlayerState_Walk(PlayerState_Walk&& _Other) noexcept = delete;
	PlayerState_Walk& operator=(const PlayerState_Walk& _Other) = delete;
	PlayerState_Walk& operator=(const PlayerState_Walk&& _Other) noexcept = delete;

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
	static std::vector<KeyNames>  CheckArrows;

	KeyNames PressArrow = KeyNames::COUNT;
	KeyNames LastArrow = KeyNames::COUNT;
	float LastTime = 0.f;

	void LoadAnimation();
	void CreateAnimation();

	void CheckPressArrow(KeyNames& _SettingEnum);
};

