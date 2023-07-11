#pragma once
#include "BossState_AttackBase.h"

class GameEngineSpriteRenderer;

class YamadaState_Attack_Blast : public BossState_AttackBase
{
public:
	YamadaState_Attack_Blast();
	~YamadaState_Attack_Blast() override;

	YamadaState_Attack_Blast(const YamadaState_Attack_Blast& _Other) = delete;
	YamadaState_Attack_Blast(YamadaState_Attack_Blast&& _Other) noexcept = delete;
	YamadaState_Attack_Blast& operator=(const YamadaState_Attack_Blast& _Other) = delete;
	YamadaState_Attack_Blast& operator=(const YamadaState_Attack_Blast&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void EnterState() override;
	void ExitState() override;

	void Attack() override;

private:
	static const std::string_view AniName;
	static const std::string_view AniFileName;
	static const std::pair<int, int> AniCutFrame;
	static const float AniInterTime;

	static const int Damage;
	static const float4 ColOffset;
	static const float4 ColScale;

	static const std::string_view BlastName;
	static const std::vector<std::string_view> SfxVoiceNames;
	
	float AfterEffectTimer = 0.f;
	bool FirstHit = false;

	std::shared_ptr<GameEngineComponent> EffectHandler = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> EffectRender = nullptr;

	void LoadAnimation();
	void CreateAnimation();
	void CreateBlastEffect();
	

	void Update_AfterEffect(float _DeltaTime);
};

