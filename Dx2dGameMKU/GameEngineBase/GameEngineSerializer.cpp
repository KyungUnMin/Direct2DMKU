#include "GameEngineSerializer.h"

GameEngineSerializer::GameEngineSerializer()
{

}

GameEngineSerializer::~GameEngineSerializer()
{

}

void GameEngineSerializer::Write(const void* _Ptr, size_t _Size)
{
	//���۰� ��ĥ�� ���� Ȯ��
	if (Datas.size() <= Offset + _Size)
	{
		Datas.resize(Datas.size() + 1024);
	}

	//&Datas[Offset]�� �����͸� �����ض�
	//������� ������ ��������
	//������ ����� ������ġ, ������ ũ��
	memcpy_s(&Datas[Offset], Datas.size() - Offset, _Ptr, _Size);

	Offset += _Size;
}


void GameEngineSerializer::Write(const int& _Value)
{
	Write(&_Value, sizeof(int));
}

void GameEngineSerializer::Write(const std::string_view& _Value)
{
	//TODO
}

