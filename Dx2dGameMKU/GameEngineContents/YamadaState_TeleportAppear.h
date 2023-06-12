#pragma once
#include "EnemyStateBase.h"

class YamadaState_TeleportAppear : public EnemyStateBase
{
public:
	YamadaState_TeleportAppear();
	~YamadaState_TeleportAppear() override;

	YamadaState_TeleportAppear(const YamadaState_TeleportAppear& _Other) = delete;
	YamadaState_TeleportAppear(YamadaState_TeleportAppear&& _Other) noexcept = delete;
	YamadaState_TeleportAppear& operator=(const YamadaState_TeleportAppear& _Other) = delete;
	YamadaState_TeleportAppear& operator=(const YamadaState_TeleportAppear&& _Other) noexcept = delete;

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
	static const float TeleportOffset;

	size_t NextState = -1;
	const float Duration = 0.15f;

	std::shared_ptr<class GameEngineSpriteRenderer> ShadowRender = nullptr;

	float4 OriginEnemyRenderScale = float4::Zero;
	float4 OriginShadowRenderScale = float4::Zero;

	void LoadAnimation();
	void CreateAnimation();
	void SettingRenderInfo();

	void Teleport();
	void Update_Scale();
};

