#pragma once
#include <GameEngineCore/GameEngineActor.h>

class ShopInfo : public GameEngineActor
{
public:
	ShopInfo();
	~ShopInfo();

	ShopInfo(const ShopInfo& _Other) = delete;
	ShopInfo(ShopInfo&& _Other) noexcept = delete;
	ShopInfo& operator=(const ShopInfo& _Other) = delete;
	ShopInfo& operator=(const ShopInfo&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

