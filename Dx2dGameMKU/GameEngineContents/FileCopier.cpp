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


void FileCopier::FileCopy(const std::string_view& _ChangeName)
{
	MsgTextBox("몬스터 FSM State 파일을 카피합니다");


	GameEngineDirectory SourDir;
	GameEngineDirectory DescDir;

	SourDir.MoveParentToDirectory("ContentsResource");
	DescDir.MoveParentToDirectory("ContentsResource");

	SourDir.Move("FileStamp");
	DescDir.Move("FileStamp");

	SourDir.Move("StateSample");
	DescDir.Move("StateOutput");



	std::vector<GameEngineFile> Files = SourDir.GetAllFile({ ".cpp", ".h"});

	for (GameEngineFile& File : Files)
	{
		GameEngineSerializer Serializer;
		Serializer.BufferResize(1024 * 1000);
		File.LoadBin(Serializer);

		size_t FileSize = File.GetFileSize();
		char* DataPtr = reinterpret_cast<char*>(Serializer.GetData());
		
		std::string FileStr;
		for (size_t i = 0; i < FileSize; ++i)
		{
			FileStr += DataPtr[i];
		}

		FileStr = std::regex_replace(FileStr, std::regex("SchoolBoy"), _ChangeName.data());

		GameEngineSerializer SaveData;
		for (size_t i = 0; i < FileStr.size(); ++i)
		{
			SaveData.Write(&FileStr[i], 1);
		}

		std::string FileFullPath = File.GetFullPath();
		size_t Index = FileFullPath.size();
		while ('\\' != FileFullPath[--Index])
		{

		}

		++Index;
		std::string SourceFileName = FileFullPath.substr(Index, FileFullPath.size() - Index);
		std::string DescFileName = std::regex_replace(SourceFileName, std::regex("SchoolBoy"), _ChangeName.data());

		GameEngineFile SaveFolder(DescDir.GetPlusFileName(DescFileName).GetFullPath());
		SaveFolder.SaveBin(SaveData);
	}
}

