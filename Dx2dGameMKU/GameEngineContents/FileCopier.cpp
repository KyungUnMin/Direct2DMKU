#include "PrecompileHeader.h"
#include "FileCopier.h"

#include <regex>

#include <GameEngineBase/GameEngineSerializer.h>

FileCopier::FileCopier()
{

}

FileCopier::~FileCopier()
{

}


void FileCopier::Test(/*GameEngineDirectory _Dir*/)
{
	MsgTextBox("파일 카피를 시작합니다");

	GameEngineDirectory _Dir;
	

	std::vector<GameEngineFile> Files =  _Dir.GetAllFile({ ".cpp", ".h"});

	for (GameEngineFile& File : Files)
	{
		GameEngineSerializer Serializer;
		/*const size_t Size = 1024;
		Serializer.BufferResize(Size);*/
		File.LoadBin(Serializer);

		size_t FileSize = File.GetFileSize();
		char* DataPtr = reinterpret_cast<char*>(Serializer.GetData());
		
		std::string FileStr;
		for (size_t i = 0; i < FileSize; ++i)
		{
			FileStr += DataPtr[i];
		}

		FileStr = std::regex_replace(FileStr, std::regex("wWinMain"), "Main");

		GameEngineSerializer SaveData;
		for (size_t i = 0; i < FileStr.size(); ++i)
		{
			SaveData.Write(&FileStr[i], 1);
		}


		GameEngineFile SaveFolder(_Dir.GetPlusFileName("StateSample\\Test.cpp").GetFullPath());
		SaveFolder.SaveBin(SaveData);

		int a = 0;
	}
}

