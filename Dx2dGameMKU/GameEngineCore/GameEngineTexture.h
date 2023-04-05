#pragma once
#include "GameEngineResource.h"

class GameEngineTexture : public GameEngineResource<GameEngineTexture>
{
public:
	GameEngineTexture();
	~GameEngineTexture() override;

	GameEngineTexture(const GameEngineTexture& _Other) = delete;
	GameEngineTexture(GameEngineTexture&& _Other) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _Other) = delete;
	GameEngineTexture& operator=(const GameEngineTexture&& _Other) noexcept = delete;

	//Core에서 이 함수를 호출시키므로써
	//만들려는 리소스를
	//static Resources 자료구조에 Texture별로 저장하게 됨
	//(이름이 키값인 Map or List)
	static void Create(const std::string_view& _Name, const std::string_view& _Path)
	{
		std::shared_ptr<GameEngineTexture> NewTex = GameEngineResource::Create(_Name);
		//TODO
	}

protected:

private:

};

