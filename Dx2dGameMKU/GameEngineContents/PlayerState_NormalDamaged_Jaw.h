#pragma once
#include "PlayerState_DamagedBase.h"

class PlayerState_NormalDamaged_Jaw : public PlayerState_DamagedBase
{
public:
	PlayerState_NormalDamaged_Jaw();
	~PlayerState_NormalDamaged_Jaw() override;

	PlayerState_NormalDamaged_Jaw(const PlayerState_NormalDamaged_Jaw& _Other) = delete;
	PlayerState_NormalDamaged_Jaw(PlayerState_NormalDamaged_Jaw&& _Other) noexcept = delete;
	PlayerState_NormalDamaged_Jaw& operator=(const PlayerState_NormalDamaged_Jaw& _Other) = delete;
	PlayerState_NormalDamaged_Jaw& operator=(const PlayerState_NormalDamaged_Jaw&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view AniName;
	static const float AniInterTime;
	static const std::pair<size_t, size_t> AniFrame;

	void CreateAnimation();
};

