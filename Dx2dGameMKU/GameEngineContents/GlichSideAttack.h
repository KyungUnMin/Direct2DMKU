#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineCollision;

class GlichSideAttack : public GameEngineActor
{
public:
	GlichSideAttack();
	~GlichSideAttack() override;

	GlichSideAttack(const GlichSideAttack& _Other) = delete;
	GlichSideAttack(GlichSideAttack&& _Other) noexcept = delete;
	GlichSideAttack& operator=(const GlichSideAttack& _Other) = delete;
	GlichSideAttack& operator=(const GlichSideAttack&& _Other) noexcept = delete;

	void Init(const float4& _Pos);

	inline void WaveOff(float _DecreseDuration = 1.f)
	{
		WaveOffValue = true;
		DecreseDuration = _DecreseDuration;
	}

protected:
	void Update(float _DeltaTime) override;

private:
	static const float4 RenderScale;
	static const float4 CollisionScale;
	static const int Damage;

	struct GlichData
	{
		float Timer = 0.f;
		float Speed = 10.f;
		float Count = 30.f;
		float WaveDiff = 0.3f;

		float MaxWaveHeight = 1.f;
		float GlichRatio = 0.5f;
		float Garbage2;
		float Garbage3;
	};

	GlichData Data;

	bool WaveOffValue = false;
	float DecreseDuration = 0.f;
	float DecreaseTimer = 0.f;

	std::shared_ptr<GameEngineCollision> AttackCollider = nullptr;
	float LastAttackTime = -100.f;
	class FieldCamController* CamCtrl = nullptr;


	void CreateRenders(float _YRatio);
	void CreateCollider();

	void Update_Collider();
	void Update_WaveOff(float _DeltaTime);

};

