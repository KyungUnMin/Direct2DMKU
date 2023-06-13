#pragma once
#include "GameEngineTexture.h"

class SpriteInfo
{
public:
	std::shared_ptr<GameEngineTexture> Texture = nullptr;
	float4 CutData = float4::Zero;
};

class GameEngineSprite : public GameEngineResource<GameEngineSprite>
{
public:
	GameEngineSprite();
	~GameEngineSprite() override;

	GameEngineSprite(const GameEngineSprite& _Other) = delete;
	GameEngineSprite(GameEngineSprite&& _Other) noexcept = delete;
	GameEngineSprite& operator=(const GameEngineSprite& _Other) = delete;
	GameEngineSprite& operator=(const GameEngineSprite&& _Other) noexcept = delete;

	//���ҽ� �ε� �� �ִϸ��̼����� �����(����), ���ϸ����� ���ҽ� ����
	static std::shared_ptr<GameEngineSprite> LoadFolder(const std::string_view& _Path)
	{
		GameEnginePath NewPath = std::string(_Path);
		return LoadFolder(NewPath.GetFileName(), _Path);
	}

	//���ҽ� �ε� �� �ִϸ��̼����� �����(����)
	static std::shared_ptr<GameEngineSprite> LoadFolder(const std::string_view& _SpriteName, const std::string_view& _Path)
	{
		GameEnginePath NewPath = std::string(_Path);

		std::shared_ptr<GameEngineSprite> NewTexture = GameEngineResource::Create(_SpriteName);
		NewTexture->ResLoadFolder(_Path);
		return NewTexture;
	}

	//���ҽ� �ε� �� �ִϸ��̼����� �����(��������Ʈ ��Ʈ)
	static std::shared_ptr<GameEngineSprite> LoadSheet(const std::string_view& _Path, size_t _X, size_t _Y)
	{
		GameEnginePath NewPath = std::string(_Path);

		std::shared_ptr<GameEngineSprite> NewTexture = GameEngineResource::Create(NewPath.GetFileName());
		NewTexture->ResLoadSheet(_Path, _X, _Y);
		return NewTexture;
	}

	size_t GetSpriteCount()
	{
		return Sprites.size();
	}

	const SpriteInfo& GetSpriteInfo(size_t _Index)
	{
		if (_Index < 0)
		{
			MsgAssert("0������ ��������Ʈ �ε��� �Դϴ�.");
		}

		if (_Index >= Sprites.size())
		{
			MsgAssert("��������Ʈ�� �ε����� �����߽��ϴ�.");
		}

		return Sprites[_Index];
	}




	static std::shared_ptr<GameEngineSprite> UnLoad(const std::string_view& _Name)
	{
		std::shared_ptr<GameEngineSprite> FindSprite = GameEngineResource::Find(_Name);

		if (nullptr == FindSprite)
		{
			MsgAssert("�������� �ʴ� ��������Ʈ�� ��ε� �Ϸ��� �߽��ϴ�.");
			return nullptr;
		}

		FindSprite->Release();
		return FindSprite;
	}


	static std::shared_ptr<GameEngineSprite> ReLoad(const std::string_view& _Path)
	{
		GameEnginePath NewPath(_Path);
		return ReLoad(_Path, NewPath.GetFileName());
	}


	static std::shared_ptr<GameEngineSprite> ReLoad(const std::string_view& _Path, const std::string_view& _Name)
	{
		std::shared_ptr<GameEngineSprite> FindSprite = GameEngineResource<GameEngineSprite>::Find(_Name);

		if (nullptr == FindSprite)
		{
			return LoadFolder(_Name.data(), _Path);
		}

		FindSprite->ReLoad();
		return FindSprite;
	}


	void ReLoad();
	void Release();

protected:

private:
	std::vector<SpriteInfo> Sprites;

	void ResLoadFolder(const std::string_view& _Path);
	void ResLoadSheet(const std::string_view& _Path, size_t _X, size_t _Y);
};

