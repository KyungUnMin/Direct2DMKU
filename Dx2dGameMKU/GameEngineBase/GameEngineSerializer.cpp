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
	//문자열의 길이부터 넣는다(읽어들일때 문자열의 갯수를 알기 위해)
	int Size = static_cast<int>(_Value.size());

	Write(&Size, sizeof(int));
	Write(_Value.data(), Size);
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













void GameEngineSerializer::Read(int& _Value)
{
	Read(&_Value, sizeof(int));
}

void GameEngineSerializer::Read(std::string& _Value)
{
	//읽어들일 문자열의 갯수부터 알아온다
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
		MsgAssert("데이터를 한도 이상으로 읽으려고 했습니다");
	}

	//_Ptr로 데이터를 복사해라
	//복사받을 버퍼의 여유공간
	//복사할 대상의 시작위치, 복사할 크기
	memcpy_s(_Ptr, _Size, &Datas[Offset], _Size);

	Offset += _Size;
}