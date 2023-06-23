#pragma once
#include "FieldActorBase.h"

enum class NoiseFloorType
{
	Red,
	Yellow,
	Blue,
	Pupple,
	Green,
	Pink
};

class GameEngineSpriteRenderer;

class NoiseFloor : public FieldActorBase
{
public:
	static size_t IsAllClear()
	{
		return (0 == RunCount);
	}

	NoiseFloor();
	~NoiseFloor() override;

	NoiseFloor(const NoiseFloor& _Other) = delete;
	NoiseFloor(NoiseFloor&& _Other) noexcept = delete;
	NoiseFloor& operator=(const NoiseFloor& _Other) = delete;
	NoiseFloor& operator=(const NoiseFloor&& _Other) noexcept = delete;

	void Init(NoiseFloorType _Color, size_t _CurPhase);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static size_t RunCount;

	static const std::vector<std::string_view> FileNames;
	static const std::vector<std::pair<float4, float4>> MovePath;
	static const int Damage;


	enum class State
	{
		Move,
		Destroy,
		Hit
	};

	size_t CurPhase = -1;
	State CurState = State::Move;

	float4 MoveDir = float4::Zero;
	float4 StartPos = float4::Zero;
	float4 DestPos = float4::Zero;

	std::shared_ptr<GameEngineSpriteRenderer> SpawnEffect = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> DestroyLight = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> HitEffect = nullptr;


	void ImageLoad();
	void CreateEffects();

	void Update_Move(float _DeltaTime);
	bool CheckColWithPlayer();

	void Update_Destroy(float _DeltaTime);
	void Update_Hit(float _DeltaTime);

	void Attack();
};

