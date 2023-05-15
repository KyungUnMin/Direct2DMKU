#pragma once
#include "StateBase.h"

class BossVursus;
class GameEngineTransform;

class BossVursusState_Approach : public StateBase
{
public:
	BossVursusState_Approach();
	~BossVursusState_Approach() override;

	BossVursusState_Approach(const BossVursusState_Approach& _Other) = delete;
	BossVursusState_Approach(BossVursusState_Approach&& _Other) noexcept = delete;
	BossVursusState_Approach& operator=(const BossVursusState_Approach& _Other) = delete;
	BossVursusState_Approach& operator=(const BossVursusState_Approach&& _Other) noexcept = delete;

	void Init(BossVursus* _VursusUI);

protected:
	void Update(float _DeltaTime) override;


private:
	struct PortraitCBuffer
	{
		float NoiseFilterValue = 0.f;
		const float NoiseImageScale = 5.f;
		const float Garbage1 = 0.f;
		const float Garbage2 = 0.f;
	};

	PortraitCBuffer PortraitRenderData;

	GameEngineTransform* PlayerPortTrans = nullptr;
	GameEngineTransform* BossPortTrans = nullptr;

};

