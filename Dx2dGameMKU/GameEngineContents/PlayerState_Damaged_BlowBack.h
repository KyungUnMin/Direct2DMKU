#pragma once
#include "PlayerState_DamagedBase.h"

class PlayerState_Damaged_BlowBack : public PlayerState_DamagedBase
{
public:
	PlayerState_Damaged_BlowBack();
	~PlayerState_Damaged_BlowBack() override;

	PlayerState_Damaged_BlowBack(const PlayerState_Damaged_BlowBack& _Other) = delete;
	PlayerState_Damaged_BlowBack(PlayerState_Damaged_BlowBack&& _Other) noexcept = delete;
	PlayerState_Damaged_BlowBack& operator=(const PlayerState_Damaged_BlowBack& _Other) = delete;
	PlayerState_Damaged_BlowBack& operator=(const PlayerState_Damaged_BlowBack&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	const float StartAcc = 2500.f;
	const float Duration = 0.5f;
	GameEngineTransform* PlayerTrans = nullptr;
	std::shared_ptr<class BackGround> BGPtr = nullptr;

	void LoadAnimation();
	void CreateAnimation();

	bool Update_BlowBack(float _DeltaTime);
	bool Update_BlowHorizon(float _Ratio, float _DeltaTime);
};

