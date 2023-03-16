#include "GameEngineDirectory.h"
#include "GameEngineFile.h"
#include "GameEngineDebug.h"

GameEngineDirectory::GameEngineDirectory()
{
}

GameEngineDirectory::~GameEngineDirectory()
{
}


//인자로 받은 _String이 있는 곳 까지 부모 경로로 이동
void GameEngineDirectory::MoveParentToDirectory(const std::string_view& _String)
{
	std::string MovePath = "\\";
	MovePath += _String;

	Path.MoveParentToChildPath(MovePath.c_str());
}


//디렉토리 상에서 인자로 받은 자식 경로로 이동
bool GameEngineDirectory::Move(const std::string_view& _String)
{
	std::string MovePath = "\\";
	MovePath += _String;
	return Path.Move(MovePath.c_str());
}


//멤버변수 Path와 인자로 받은 _String를 합친 경로를 새로 만들어 반환
GameEnginePath GameEngineDirectory::GetPlusFileName(const std::string_view& _String)
{

	std::string PathString = Path.GetPathToString();
	PathString += "\\";
	PathString += _String;

	return GameEnginePath(PathString);
}


//디렉토리 상에서 부모 경로로 이동
bool GameEngineDirectory::MoveParent()
{
	if (true == Path.IsRoot())
	{
		MsgAssert("루트 디렉토리는 부모디렉토리로 이동할수 없습니다.");
		return false;
	}

	Path.MoveParent();

	return true;
}


//이 파일에 있는 경로들을 벡터에 담아 리턴
std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(const std::string_view& _Ext)
{
	//파일에 있는 경로를 순환할수 있는 반복자
	std::filesystem::directory_iterator DirIter(Path.Path);

	std::string Ext = _Ext.data();
	std::vector<GameEngineFile> Files;

	//순환
	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		//존재하는 경로인지 확인
		if (true == Entry.is_directory())
			continue;

		Files.push_back(GameEngineFile(Entry.path()));
	}

	return Files;
}