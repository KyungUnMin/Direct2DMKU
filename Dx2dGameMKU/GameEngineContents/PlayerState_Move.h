#pragma once
#include "PlayerStateBase.h"
#include "KeyMgr.h"


class PlayerState_Move : public PlayerStateBase
{
public:
	PlayerState_Move();
	~PlayerState_Move() override;

	PlayerState_Move(const PlayerState_Move& _Other) = delete;
	PlayerState_Move(PlayerState_Move&& _Other) noexcept = delete;
	PlayerState_Move& operator=(const PlayerState_Move& _Other) = delete;
	PlayerState_Move& operator=(const PlayerState_Move&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
	void EnterState() override;
	void ExitState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFolderName;
	static const float AniInterTime;
	static std::vector<KeyNames>  CheckArrows;

	KeyNames PressArrow = KeyNames::COUNT;
	KeyNames LastArrow = KeyNames::COUNT;
	float LastTime = 0.f;

	void LoadAnimation();
	void CreateAnimation();

	void CheckPressArrow(KeyNames& _SettingEnum);
};

