#pragma once
#include "GameEngineComponent.h"

class GameEngineCollision : public GameEngineComponent
{
public:
	GameEngineCollision();
	~GameEngineCollision() override;

	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(const GameEngineCollision&& _Other) noexcept = delete;


	template<typename EnumType>
	std::shared_ptr<GameEngineCollision> Collision(EnumType _TargetGroup, ColType _ThisColType, ColType _OtherColtype)
	{
		return Collision(static_cast<int>(_TargetGroup), _ThisColType, _OtherColtype);
	}

	std::shared_ptr<GameEngineCollision> Collision(int _TargetGroup, ColType _ThisColType, ColType _OtherColtype);

	bool CollisionAll(int _TargetGroup, ColType _ThisColType, ColType _OtherColtype, std::vector<std::shared_ptr<GameEngineCollision>>& _Col);

	void SetOrder(int _Order) override;

protected:

private:

};

