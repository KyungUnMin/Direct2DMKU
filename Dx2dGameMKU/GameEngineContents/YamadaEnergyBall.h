#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class GameEngineCollision;

class YamadaEnergyBall : public GameEngineActor
{
public:
	YamadaEnergyBall();
	~YamadaEnergyBall();

	YamadaEnergyBall(const YamadaEnergyBall& _Other) = delete;
	YamadaEnergyBall(YamadaEnergyBall&& _Other) noexcept = delete;
	YamadaEnergyBall& operator=(const YamadaEnergyBall& _Other) = delete;
	YamadaEnergyBall& operator=(const YamadaEnergyBall&& _Other) noexcept = delete;

	void DestroyBall();

	inline bool IsWait() const
	{
		return State::Create == CurState;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view Ball_FileName;
	static const std::string_view Ring_FileName;
	static const std::string_view Air_FileName;
	static const float AniInterTime;
	static const float4 DarkPupple;
	static const int Damage;

	std::shared_ptr<GameEngineSpriteRenderer> AirRender = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> BallRender = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> RingRender = nullptr;
	std::shared_ptr<GameEngineCollision> Collider = nullptr;


	enum class State
	{
		Create,
		Rot,
		Destory,
	};

	State CurState = State::Create;
	const float AfterImgTime = 0.05f;
	float AfterImgTimer = 0.f;
	float LastAttackTime = 0.f;

	void ImageLoad();
	void CreateRenders();
	void CreateRender_Air();
	void CreateRender_Ball();
	void CreateCollider();
	void CreateLight();

	void Update_Create(float _DeltaTime);
	void Update_Rot(float _DeltaTime);
	void Update_CheckCol();
	void Update_Destory(float _DeltaTime);
};

