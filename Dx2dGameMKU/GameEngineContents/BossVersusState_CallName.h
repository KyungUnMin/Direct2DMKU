#pragma once
#include "StateBase.h"

class SelfRenderer;

class BossVersusState_CallName : public StateBase
{
public:
	BossVersusState_CallName();
	~BossVersusState_CallName() override;

	BossVersusState_CallName(const BossVersusState_CallName& _Other) = delete;
	BossVersusState_CallName(BossVersusState_CallName&& _Other) noexcept = delete;
	BossVersusState_CallName& operator=(const BossVersusState_CallName& _Other) = delete;
	BossVersusState_CallName& operator=(const BossVersusState_CallName&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DelatTime) override;
	void EnterState() override;

private:
	static const std::string_view NameTag_FileName;
	static const float4 NameDestPos;
	static const float4 NameTagDestPos;

	std::shared_ptr<SelfRenderer> PlayerName = nullptr;
	std::shared_ptr<SelfRenderer> BossName = nullptr;
	std::shared_ptr<SelfRenderer> PlayerNameTag = nullptr;
	std::shared_ptr<SelfRenderer> BossNameTag = nullptr;

	float Duration = 0.5f;
	float4 NameStartPos = float4::Zero;
	float4 NameTagStartPos = float4::Zero;

	void CreateNameTags();
	void BindNameRenders();
	void SettingMovePoint();

	inline float4 PosFlip(const float4& _Pos)
	{
		return float4{ -_Pos.x,  _Pos.y };
	}
};

