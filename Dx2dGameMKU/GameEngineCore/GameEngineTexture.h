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

	//Core���� �� �Լ��� ȣ���Ű�Ƿν�
	//������� ���ҽ���
	//static Resources �ڷᱸ���� Texture���� �����ϰ� ��
	//(�̸��� Ű���� Map or List)
	static void Create(const std::string_view& _Name, const std::string_view& _Path)
	{
		std::shared_ptr<GameEngineTexture> NewTex = GameEngineResource::Create(_Name);
		//TODO
	}

protected:

private:

};

