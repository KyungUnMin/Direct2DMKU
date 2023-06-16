#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class WormchiObjType
{
	Phone,
	Antenna,
	Cat,
	Ball,
	Pipe,
	Tv,

	COUNT
};

class GameEngineSpriteRenderer;

class YamadaWormchiObj : public GameEngineActor
{
public:
	YamadaWormchiObj();
	~YamadaWormchiObj() override;

	YamadaWormchiObj(const YamadaWormchiObj& _Other) = delete;
	YamadaWormchiObj(YamadaWormchiObj&& _Other) noexcept = delete;
	YamadaWormchiObj& operator=(const YamadaWormchiObj& _Other) = delete;
	YamadaWormchiObj& operator=(const YamadaWormchiObj&& _Other) noexcept = delete;

	void Init(WormchiObjType _Type);

	void MoveOn();


	//¼Ò¸ê
	void Extinct();

	inline bool IsWait() const
	{
		return (State::Up == CurState) || (State::Wait == CurState);
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	

private:
	static const std::string_view Ani_FileName;
	static const std::string_view Light_FileName;
	static const float HeightPivot;
	static const int Damage;

	static const float4 ObjScale;
	static const float4 LightScale;


	std::shared_ptr<GameEngineSpriteRenderer> ObjRender = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Light = nullptr;
	std::shared_ptr<class GameEngineCollision> Collider = nullptr;

	enum class State
	{
		Up,
		Wait,
		Move,
		Extinct,
	};

	State CurState = State::Up;
	float4 Dir = float4::Zero;
	float4 MapScale = float4::Zero;

	const float EffectTime = 0.05f;
	float EffectTimer = 0.f;


	void LoadImages();
	void CreateRenders();
	void CreateCollider();

	void Update_Up(float _DeltaTime);
	void Update_Wait(float _DeltaTime);
	void Update_Move(float _DeltaTime);
	void Update_Extinct(float _DeltaTime);

	bool CheckMapOut(const float4& _Pos);
	void Attack();
};

