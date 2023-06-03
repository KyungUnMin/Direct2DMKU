#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class GameEngineCollision;

class CopGrenade : public GameEngineActor
{
public:
	CopGrenade();
	~CopGrenade() override;

	CopGrenade(const CopGrenade& _Other) = delete;
	CopGrenade(CopGrenade&& _Other) noexcept = delete;
	CopGrenade& operator=(const CopGrenade& _Other) = delete;
	CopGrenade& operator=(const CopGrenade&& _Other) noexcept = delete;

	void Init(const float4& _ThrowDir);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	enum class State
	{
		Throw,
		Land,
		Explosion,

		COUNT
	};
	
	static const std::string_view Grenade_FileName;
	static const std::string_view Explosion_FileName;
	static const std::pair<int, int> Grenade_CutFrame;
	static const std::pair<int, int> Explosion_CutFrame;

	static const std::vector<std::string_view> AniNames;
	

	State CurState = State::Throw;
	std::shared_ptr<GameEngineSpriteRenderer> Render = nullptr;
	std::shared_ptr<GameEngineCollision> Collider = nullptr;
	std::shared_ptr<class BackGround> BGPtr = nullptr;

	float4 ThrowDir = float4::Zero;
	float4 StartPos = float4::Zero;
	float4 DestPos = float4::Zero;
	const float Duration = 1.f;

	const float MaxHorizon = 30.f;
	const float MaxVertical = 150.f;
	const float PivotVertical = MaxVertical;
	const float4 ExploRenderScale = float4::One * 500.f;

	const int Damage = 30;



	void ImageLoad();
	void CreateAnimation();
	
	void Update_Throw(float _DeltaTime);
	void Update_ThrowHorizon(float _Ratio);
	void Update_ThrowVertical(float _Ratio);

	void Update_Land();
	void Update_Explosion();

	void ChangeState(State _Next);
};

