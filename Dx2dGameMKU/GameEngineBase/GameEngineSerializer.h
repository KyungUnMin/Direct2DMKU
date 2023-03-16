#pragma once
#include <vector>
#include <string>
#include <string_view>

class GameEngineSerializer
{
public:
	GameEngineSerializer();
	~GameEngineSerializer();

	GameEngineSerializer(const GameEngineSerializer& _Other) = delete;
	GameEngineSerializer(GameEngineSerializer&& _Other) noexcept = delete;
	GameEngineSerializer& operator=(const GameEngineSerializer& _Other) = delete;
	GameEngineSerializer& operator=(const GameEngineSerializer&& _Other) noexcept = delete;

	//Int용 직렬화
	void Write(const int& _Value);

	//string용 직렬화
	void Write(const std::string_view& _Value);

	//실제 직렬화가 이루어지는 부분
	void Write(const void* _Ptr, size_t _Size);

	inline void* GetData()
	{
		return &Datas[0];
	}

	inline size_t GetDataSize()
	{
		return Offset;
	}

protected:

private:
	//직렬화된 데이터 버퍼
	std::vector<char> Datas = std::vector<char>(1024);

	//버퍼에 데이터가 얼마나 채워졌는지 확인하기 위한 커서
	size_t Offset = 0;
};

