#pragma once
#include "StateBase.h"
#include "RCGEnums.h"

class SelfRenderer;

class BossVersusState_PortraitMatch : public StateBase
{
public:
	BossVersusState_PortraitMatch();
	~BossVersusState_PortraitMatch() override;

	BossVersusState_PortraitMatch(const BossVersusState_PortraitMatch& _Other) = delete;
	BossVersusState_PortraitMatch(BossVersusState_PortraitMatch&& _Other) noexcept = delete;
	BossVersusState_PortraitMatch& operator=(const BossVersusState_PortraitMatch& _Other) = delete;
	BossVersusState_PortraitMatch& operator=(const BossVersusState_PortraitMatch&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view LinkCBufferName;

	std::shared_ptr<SelfRenderer> PlayerPortrait = nullptr;
	std::shared_ptr<SelfRenderer> BossPortrait = nullptr;
	std::shared_ptr<SelfRenderer> UILightRender = nullptr;
	
	struct ShaderData
	{
		float NoiseFilterValue = 0.0f;
		const float NoiseImageScale = 10.f; /*±âÁ¸°ª 5.0f*/
		const float Garbage1 = 0.f;
		const float Garbage2 = 0.f;
	};

	ShaderData CBufferData;
	float4 UILightColor = float4::Zero;

	float4 PortraitStartPos = float4::Zero;
	float4 PortraitEndPos = float4::Zero;

	const float Duration = 0.5f;

	void CreateRenderers();
	void SettingValue();
};

