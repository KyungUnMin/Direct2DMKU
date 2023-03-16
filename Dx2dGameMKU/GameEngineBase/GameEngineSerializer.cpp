#include "GameEngineSerializer.h"

GameEngineSerializer::GameEngineSerializer()
{

}

GameEngineSerializer::~GameEngineSerializer()
{

}

void GameEngineSerializer::Write(const void* _Ptr, size_t _Size)
{
	//버퍼가 넘칠땐 버퍼 확장
	if (Datas.size() <= Offset + _Size)
	{
		Datas.resize(Datas.size() + 1024);
	}

	//&Datas[Offset]로 데이터를 복사해라
	//복사받을 버퍼의 여유공간
	//복사할 대상의 시작위치, 복사할 크기
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

