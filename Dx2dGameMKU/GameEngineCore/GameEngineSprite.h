#pragma once
#include "GameEngineTexture.h"

class GameEngineSprite : public GameEngineResource<GameEngineSprite>
{
private:
	class SpriteInfo
	{
		std::shared_ptr<GameEngineTexture> Sprite;
		float4 CutData;
	};

public:
	GameEngineSprite();
	~GameEngineSprite() override;

	GameEngineSprite(const GameEngineSprite& _Other) = delete;
	GameEngineSprite(GameEngineSprite&& _Other) noexcept = delete;
	GameEngineSprite& operator=(const GameEngineSprite& _Other) = delete;
	GameEngineSprite& operator=(const GameEngineSprite&& _Other) noexcept = delete;

	//리소스 로드 및 애니메이션으로 만들기
	static std::shared_ptr<GameEngineSprite> LoadFolder(const std::string_view& _Path);

protected:

private:
	std::vector<SpriteInfo> Sprites;
};

