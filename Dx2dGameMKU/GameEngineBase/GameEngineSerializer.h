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

	//Int�� ����ȭ
	void Write(const int& _Value);

	//string�� ����ȭ
	void Write(const std::string_view& _Value);

	//���� ����ȭ�� �̷������ �κ�
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
	//����ȭ�� ������ ����
	std::vector<char> Datas = std::vector<char>(1024);

	//���ۿ� �����Ͱ� �󸶳� ä�������� Ȯ���ϱ� ���� Ŀ��
	size_t Offset = 0;
};

