#include "PrecompileHeader.h"
#include "GameEngineSerializer.h"
#include "GameEngineDebug.h"

GameEngineSerializer::GameEngineSerializer()
{

}

GameEngineSerializer::~GameEngineSerializer()
{

}


void GameEngineSerializer::BufferResize(size_t _Size)
{
	Datas.resize(_Size);
}



void GameEngineSerializer::Write(const int& _Value)
{
	Write(&_Value, sizeof(int));
}

void GameEngineSerializer::Write(const std::string_view& _Value)
{
	//���ڿ��� ���̺��� �ִ´�(�о���϶� ���ڿ��� ������ �˱� ����)
	int Size = static_cast<int>(_Value.size());

	Write(&Size, sizeof(int));
	Write(_Value.data(), Size);
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













void GameEngineSerializer::Read(int& _Value)
{
	Read(&_Value, sizeof(int));
}

void GameEngineSerializer::Read(std::string& _Value)
{
	//�о���� ���ڿ��� �������� �˾ƿ´�
	int Size = 0;
	Read(&Size, sizeof(int));

	_Value.clear();
	_Value.resize(Size);
	Read(_Value.data(), Size);
}

void GameEngineSerializer::Read(void* _Ptr, size_t _Size)
{
	if (Datas.size() <= Offset + _Size)
	{
		MsgAssert("�����͸� �ѵ� �̻����� �������� �߽��ϴ�");
	}

	//_Ptr�� �����͸� �����ض�
	//������� ������ ��������
	//������ ����� ������ġ, ������ ũ��
	memcpy_s(_Ptr, _Size, &Datas[Offset], _Size);

	Offset += _Size;
}