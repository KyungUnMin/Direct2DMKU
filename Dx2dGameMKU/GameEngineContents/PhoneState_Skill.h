#pragma once
#include "PhoneStateBase.h"

class GameEngineUIRenderer;
enum class PlayerStateType;

class PhoneState_Skill : public PhoneStateBase
{
public:
	PhoneState_Skill();
	~PhoneState_Skill() override;

	PhoneState_Skill(const PhoneState_Skill& _Other) = delete;
	PhoneState_Skill(PhoneState_Skill&& _Other) noexcept = delete;
	PhoneState_Skill& operator=(const PhoneState_Skill& _Other) = delete;
	PhoneState_Skill& operator=(const PhoneState_Skill&& _Other) noexcept = delete;

protected:
	void Start() override;
	void EnterState() override;
	void Update(float _DeltaTime) override;
	void ExitState() override;

private:
	static const std::string_view UnknownSkillTexName;
	static const std::vector<std::pair<std::string_view, PlayerStateType>> SkillInfoTexNames;
	static const std::vector<float4> Positions;

	//실제 게임 시간 스케일을 0으로 만들었기 때문에 별도의 DeltaTime을 구하기 위한 타이머
	static GameEngineTime Time;

	std::shared_ptr<GameEngineUIRenderer> CursorRender = nullptr;
	std::vector<std::shared_ptr<GameEngineUIRenderer>> SkillInfoRenders;

	size_t CursorIndex = 0;
	size_t InfoIndex = 0;
	float VerticalArrowTimer = 0.f;
	const float VerticalArrowMoveTime = 0.2f;

	void SettingCursorRender();
	void SettingInfoRender();


	bool Update_HorizonArrow();
	void Update_VerticalArrow();

	void MoveUp();
	void MoveDown();
};

