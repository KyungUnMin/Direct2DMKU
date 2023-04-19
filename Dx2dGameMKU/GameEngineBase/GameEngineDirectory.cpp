#include "PrecompileHeader.h"
#include "GameEngineDirectory.h"
#include "GameEngineFile.h"
#include "GameEngineDebug.h"
#include "GameEngineString.h"

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
std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(std::vector<std::string_view>_Ext)
{
	//인자로 들어온 확장자들을 전부 대문자로 바꾸기
	std::vector<std::string> UpperExts;
	UpperExts.reserve(_Ext.size());
	for (size_t i = 0; i < _Ext.size(); ++i)
	{
		std::string OtherUpperExt = GameEngineString::ToUpper(_Ext[i]);
		UpperExts.push_back(OtherUpperExt);
	}

	//파일에 있는 경로를 순환할수 있는 반복자
	std::filesystem::directory_iterator DirIter(Path.Path);
	std::vector<GameEngineFile> Files;

	//파일에 있는 경로들을 순회
	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		//해당 경로가 파일인지 디렉토리인지 확인(파일만 검출)
		if (true == Entry.is_directory())
		{
			//디렉토리인 경우 하위 경로들을 모두 순회
			GameEngineDirectory ChildDir(Entry.path());

			//자식에서 찾은 파일을들 이 경로에 복붙
			std::vector<GameEngineFile> ChildFiles = ChildDir.GetAllFile(_Ext);
			for (size_t i = 0; i < ChildFiles.size(); i++)
			{
				Files.push_back(ChildFiles[i]);
			}

			//찾은 이후에는 상위폴더로 빠져나간다(이래서 무한루프X)
			continue;
		}

		//파일의 전체 경로
		std::string Path = Entry.path().string();

		//파일의 확장자만 뽑아 대문자로 변환
		std::string Ext = Entry.path().extension().string();
		std::string UpperExt = GameEngineString::ToUpper(Ext);

		bool Check = false;

		//맨 위에서 인자로 받은 확장자들 벡터를 순회
		for (size_t i = 0; i < UpperExts.size(); ++i)
		{
			//현재 순회중인 확장자
			const std::string& ExtText = UpperExts[i];

			//찾고자 하는 확장자가 파일 내에 있는 경우
			if (ExtText == UpperExt)
			{
				Check = true;
				break;
			}
		}

		//현재 파일이 인자로 받은 확장자들에 해당 되지 않는 경우 다음 파일을 찾기
		if (false == Check)
			continue;

		//해당 경로 저장
		Files.push_back(GameEngineFile(Entry.path()));
	}

	return Files;
}