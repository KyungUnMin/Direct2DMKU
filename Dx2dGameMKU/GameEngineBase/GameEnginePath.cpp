#include "GameEnginePath.h"
#include <Windows.h>
#include <io.h>
#include <GameEngineBase/GameEngineDebug.h>

GameEnginePath::GameEnginePath()
	: Path(std::filesystem::current_path())
{
}

GameEnginePath::GameEnginePath(std::filesystem::path _Path)
	: Path(_Path)
{
}



GameEnginePath::GameEnginePath(const std::string& _Path)
	: Path(_Path)
{

}

GameEnginePath::GameEnginePath(GameEnginePath&& _Other)
	: Path(_Other.Path)
{

}



GameEnginePath::~GameEnginePath()
{
}










GameEnginePath::GameEnginePath(const GameEnginePath& _Other)
	: Path(_Other.Path)
{

}


//멤버변수 Path의 말단경로만 반환
std::string GameEnginePath::GetFileName() const
{
	return Path.filename().string();
}


//멤버변수 Path를 string으로 변환하는 함수
std::string GameEnginePath::GetPathToString() const
{
	return Path.string();
}


//상위 경로로 이동
void GameEnginePath::MoveParent()
{
	Path = Path.parent_path();
}


//특정 경로가 존재할때 까지 상위폴더로 이동
void GameEnginePath::MoveParentToChildPath(const std::string_view& _String)
{
	while (false == IsRoot())
	{
		//찾는 경로가 현재 위치에서 자식으로 존재한다면 return
		if (true == IsExistsToPlusString(_String))
		{
			return;
		}

		//없다면 멤버변수 Path를 부모위치로 이동
		MoveParent();
	}

	//최상위 경로까지 갔는데로 찾지 못했다면 Assert
	MsgAssert("이런 경로를 자식으로 가진 부모는 존재하지 않습니다.");
}


//현재 위치에서 인자로 주어진 자식경로로 이동
bool GameEnginePath::Move(const std::string_view& _Path)
{
	Path += _Path;

	if (false == IsExists())
	{
		MsgAssert("존재하지 않는 경로로 이동하려고 했습니다.");
		return false;
	}

	return true;
}


//멤버변수 Path가 최상위 폴더인지 확인
bool GameEnginePath::IsRoot()
{
	return Path.root_path() == Path;
}


//멤버변수 Path가 유효한 경로인지 확인
bool GameEnginePath::IsExists()
{
	//현재 위치의 경로가 유효한가
	return 0 == _access(Path.string().c_str(), 0);
}


//인자로 주어진 String과 멤버변수 Path를 더했을때의 경로가 유효한지 체크
bool GameEnginePath::IsExistsToPlusString(const std::string_view& _String)
{
	//(멤버변수 Path)현재 경로 + 인자로 받은 경로
	std::string Str = GetPathToString() + _String.data();
	return 0 == _access(Str.c_str(), 0);
}


//인자로 받은 string으로 주소를 설정
void GameEnginePath::SetPath(const std::string_view& _Path)
{
	Path = _Path.data();
}