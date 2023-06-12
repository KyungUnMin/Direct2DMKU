#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineComponent.h"

class GameEngineCamera;

class GameEngineCollision : public GameEngineComponent
{
	friend class GameEngineLevel;

	static GameEngineRenderUnit DebugUnit;

public:
	GameEngineCollision();
	~GameEngineCollision();

	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(const GameEngineCollision&& _Other) noexcept = delete;


	template<typename EnumType>
	std::shared_ptr<GameEngineCollision> Collision(EnumType _TargetGroup, ColType _ThisColType = ColType::MAX, ColType _OtherColtype = ColType::MAX)
	{
		return Collision(static_cast<int>(_TargetGroup), _ThisColType, _OtherColtype);
	}

	std::shared_ptr<GameEngineCollision> Collision(int _TargetGroup, ColType _ThisColType = ColType::MAX, ColType _OtherColtype = ColType::MAX);

	template<typename EnumType>
	bool CollisionAll(EnumType _TargetGroup, std::vector<std::shared_ptr<GameEngineCollision>>& _Col, ColType _ThisColType = ColType::MAX, ColType _OtherColtype = ColType::MAX)
	{
		return CollisionAll(static_cast<int>(_TargetGroup), _Col, _ThisColType, _OtherColtype);
	}

	bool CollisionAll(int _TargetGroup, std::vector<std::shared_ptr<GameEngineCollision>>& _Col, ColType _ThisColType = ColType::MAX, ColType _OtherColtype = ColType::MAX);

	void SetOrder(int _Order) override;

	inline void SetColType(ColType _Type)
	{
		Type = _Type;
	}

	inline void SetDebugCamera(GameEngineCamera* _DebugCamera)
	{
		DebugCamera = _DebugCamera;
	}

protected:
	void Start() override;

private:
	ColType Type = ColType::SPHERE3D;

	GameEngineCamera* DebugCamera = nullptr;

	void DebugRender(float _DeltaTime);
};

