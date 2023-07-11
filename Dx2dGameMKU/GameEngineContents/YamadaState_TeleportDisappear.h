#pragma once
#include "EnemyStateBase.h"
#include "SoundMgr.h"

class YamadaState_TeleportDisappear : public EnemyStateBase
{
public:
	YamadaState_TeleportDisappear();
	~YamadaState_TeleportDisappear() override;

	YamadaState_TeleportDisappear(const YamadaState_TeleportDisappear& _Other) = delete;
	YamadaState_TeleportDisappear(YamadaState_TeleportDisappear&& _Other) noexcept = delete;
	YamadaState_TeleportDisappear& operator=(const YamadaState_TeleportDisappear& _Other) = delete;
	YamadaState_TeleportDisappear& operator=(const YamadaState_TeleportDisappear&& _Other) noexcept = delete;

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

	static const std::vector<std::string_view> LaughSfx;

	std::shared_ptr<class GameEngineSpriteRenderer> ShadowRender = nullptr;
	const float ShadowDuration = AniInterTime * 10.f;

	GameEngineSoundPlayer EffectSfx;

	void LoadAnimation();
	void CreateAnimation();
	void Update_ShadowScale();
};

