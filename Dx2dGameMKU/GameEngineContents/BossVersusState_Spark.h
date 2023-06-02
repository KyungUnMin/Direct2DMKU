#pragma once
#include "StateBase.h"

class SelfRenderer;

class BossVersusState_Spark : public StateBase
{
public:
	BossVersusState_Spark();
	~BossVersusState_Spark() override;

	BossVersusState_Spark(const BossVersusState_Spark& _Other) = delete;
	BossVersusState_Spark(BossVersusState_Spark&& _Other) noexcept = delete;
	BossVersusState_Spark& operator=(const BossVersusState_Spark& _Other) = delete;
	BossVersusState_Spark& operator=(const BossVersusState_Spark&& _Other) noexcept = delete;



protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;

private:
	enum class State
	{
		Act_Spark1,
		Act_Spark2
	};

	State CurState = State::Act_Spark1;
	
	std::shared_ptr<SelfRenderer> BackImg = nullptr;
	std::shared_ptr<SelfRenderer> Spark1 = nullptr;
	std::shared_ptr<SelfRenderer> Spark2 = nullptr;
	std::shared_ptr<SelfRenderer> VersusLogo = nullptr;

	const float4 BackImgColor = float4{ 0.f, 0.f, 0.f, 0.5f };
	float4 ScreenSize = float4::Zero;
	const float Duration_Spark1 = 0.5f;
	const float Duration_Spark2 = 0.5f;
	float StateChangeTime = 0.0f;

	void CreateRenders();
	void CraeteBackImg();


	void Update_Spark1(float _DeltaTime);
	void Update_Spark2(float _DeltaTime);
};

