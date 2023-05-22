#include "PrecompileHeader.h"
#include "FileCopier.h"

#include <GameEngineBase/GameEngineSerializer.h>

FileCopier::FileCopier()
{

}

FileCopier::~FileCopier()
{

}


void FileCopier::Test(/*GameEngineDirectory _Dir*/)
{
	GameEngineDirectory _Dir;

	std::vector<GameEngineFile> Files =  _Dir.GetAllFile({ ".cpp", ".h"});

	for (GameEngineFile& File : Files)
	{
		GameEngineSerializer Serializer;
		const size_t Size = 1024 * 10000000;
		Serializer.BufferResize(Size);
		File.LoadBin(Serializer);

		std::string Value;
		Serializer.Read(Value);
		int a = 0;
	}
}