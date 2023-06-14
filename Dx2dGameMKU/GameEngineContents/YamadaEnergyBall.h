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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view Ball_FileName;
	static const std::string_view Ring_FileName;
	static const std::string_view Air_FileName;
	static const float AniInterTime;
	static const float4 DarkPupple;

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

	void ImageLoad();
	void CreateRenders();
	void CreateRender_Air();
	void CreateRender_Ball();
	void CreateCollider();

	void Update_Create(float _DeltaTime);
	void Update_Rot(float _DeltaTime);
	void Update_Destory(float _DeltaTime);
};

