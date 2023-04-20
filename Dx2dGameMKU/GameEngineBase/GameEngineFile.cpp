#include "PrecompileHeader.h"
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

void GameEngineFile::SaveBin(const GameEngineSerializer& _Data)
{
	FILE* FilePtr = nullptr;

	//저장할 파일의 절대경로 string으로 받아오기
	std::string PathString = Path.GetFullPath();
	//바이트쓰기 모드로 파일 열기
	std::string Text = "wb";

	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());

	if (nullptr == FilePtr)
	{
		MsgAssert("파일 오픈에 실패하였습니다 : " + PathString);
		return;
	}

	//_Data.GetConstData() 위치로 부터
	//_Data.GetOffset()만큼
	//한번에
	//FilePtr가 가르키는 파일에 기록해라
	fwrite(_Data.GetConstData(), _Data.GetOffset(), 1, FilePtr);

	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}

void GameEngineFile::SaveText(const std::string_view& _View)
{
	FILE* FilePtr = nullptr;

	//저장할 파일의 절대경로 string으로 받아오기
	std::string PathString = Path.GetFullPath();
	//텍스트쓰기 모드로 파일 열기
	std::string Text = "wt";

	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());

	if (nullptr == FilePtr)
	{
		MsgAssert("파일 오픈에 실패하였습니다 : " + PathString);
		return;
	}

	//_View.data() 위치로 부터
	//_View.size()만큼
	//한번에
	//FilePtr가 가르키는 파일에 기록해라
	fwrite(_View.data(), _View.size(), 1, FilePtr);

	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}

void GameEngineFile::LoadBin(GameEngineSerializer& _Data)
{
	FILE* FilePtr = nullptr;

	//읽을 파일의 절대경로 string으로 받아오기
	std::string PathString = Path.GetFullPath();
	//바이트읽기 모드로 파일 열기
	std::string Text = "rb";

	fopen_s(&FilePtr, PathString.c_str(), Text.c_str());

	if (nullptr == FilePtr)
	{
		MsgAssert("파일 오픈에 실패하였습니다 : " + PathString);
		return;
	}

	//파일의 크기 알아오기
	size_t FileSize = std::filesystem::file_size(Path.Path);

	fread_s(_Data.GetData(), _Data.GetBufferSize(), FileSize, 1, FilePtr);

	if (nullptr != FilePtr)
	{
		fclose(FilePtr);
	}
}

