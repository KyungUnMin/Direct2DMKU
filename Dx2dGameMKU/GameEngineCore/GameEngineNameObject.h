#pragma once
#include <string>


class GameEngineNameObject
{
public:
	GameEngineNameObject();
	~GameEngineNameObject();

	GameEngineNameObject(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject(GameEngineNameObject&& _Other) noexcept = delete;
	GameEngineNameObject& operator=(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject& operator=(const GameEngineNameObject&& _Other) noexcept = delete;

	inline void SetName(const std::string_view& _Name)
	{
		Name = _Name;
	}

	inline std::string_view GetName() const
	{
		return Name.c_str();
	}

	inline std::string GetNameToString() const
	{
		return Name;
	}

protected:

private:
	std::string Name = "";
};

