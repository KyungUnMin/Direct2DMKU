#pragma once
#include <list>
#include <string_view>
#include <memory>


class GameEngineObject
{
public:
	GameEngineObject();
	~GameEngineObject();

	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(const GameEngineObject&& _Other) noexcept = delete;

	inline void On()
	{
		IsActive = true;
	}

	inline void Off()
	{
		IsActive = false;
	}

	void SetName(const std::string_view& _Name)
	{
		Name = _Name;
	}

protected:

private:
	std::string Name = "";
	bool IsActive = true;
	bool IsDeath = false;

	//��ȯ������ ������� �ʱ� ���� �Ϲ� ������ �̿�(���߿�  week�� �ٲ��)
	GameEngineObject* Parent = nullptr;
	std::list<std::shared_ptr<GameEngineObject>> Childs;
};

