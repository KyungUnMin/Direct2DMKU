#include "GameEngineFile.h"
#include "GameEngineDebug.h"

GameEngineFile::GameEngineFile()
{

}

GameEngineFile::~GameEngineFile()
{

}

GameEngineFile::GameEngineFile(std::filesystem::path _Path)
	:Path(_Path)
{
}

void GameEngineFile::Save(const GameEngineSerializer& _Data)
{
	FILE* FilePtr = nullptr;

	//저장할 파일의 절대경로 string으로 받아오기
	std::string PathString = Path.GetPathToString();

	//바이트쓰기 모드로 파일 열기
	fopen_s(&FilePtr, PathString.c_str(), "wb");

	if (nullptr == FilePtr)
	{
		MsgAssert("파일 오픈에 실패하였습니다 : " + PathString);
		return;
	}

	//fwrite(_Data);

	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}

