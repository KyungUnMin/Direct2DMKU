#pragma once
#include "FieldActorBase.h"

class GameEngineSpriteRenderer;
class GameEngineComponent;
class GameEngineCollision;

class YamadaMatterBlock : public FieldActorBase
{
public:
	static const float BlockOffsetX;

	YamadaMatterBlock();
	~YamadaMatterBlock() override;

	YamadaMatterBlock(const YamadaMatterBlock& _Other) = delete;
	YamadaMatterBlock(YamadaMatterBlock&& _Other) noexcept = delete;
	YamadaMatterBlock& operator=(const YamadaMatterBlock& _Other) = delete;
	YamadaMatterBlock& operator=(const YamadaMatterBlock&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	static const std::string_view BlockName;
	static const std::string_view DustName;
	static const std::string_view FragmentName;

	static const float Duration;
	static const int Damage;


	std::shared_ptr<GameEngineSpriteRenderer> Dust = nullptr;
	std::shared_ptr<GameEngineComponent> Pivot = nullptr;


	enum class State
	{
		Light,
		BlockCreate,
		Approach,
		BlockDestroy,
	};

	State CurState = State::Light;
	float4 PrevBlockPos = float4::Zero;
	std::shared_ptr<class BackGround> BGPtr = nullptr;

	void ImageLoad();
	void CreateRenders();
	void CreateCollider();
	void CreateLight();

	void Update_Light(float _DeltaTime);
	void Update_BlockCreate(float _DeltaTime);
	void Update_Approach(float _DeltaTime);
	void Update_BlockDestroy(float _DeltaTime);

	void CheckColWithPlayer();
	void Attack();
	void Attack_FixedBlock();
	void Attack_MoveBlock();
};

