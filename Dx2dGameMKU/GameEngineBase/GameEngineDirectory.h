#pragma once
#include <string_view>
#include <vector>
#include "GameEnginePath.h"


class GameEngineFile;

//Path를 래핑하는 클래스
class GameEngineDirectory
{
public:
	GameEngineDirectory();
	~GameEngineDirectory();

	GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory(GameEngineDirectory&& _Other) noexcept = delete;
	GameEngineDirectory& operator=(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory&& _Other) noexcept = delete;

	//디렉토리 상에서 부모 경로로 이동
	bool MoveParent();

	//인자로 받은 _String이 있는 곳 까지 부모 경로로 이동
	void MoveParentToDirectory(const std::string_view& _String);

	//디렉토리 상에서 인자로 받은 자식 경로로 이동
	bool Move(const std::string_view& _String);

	//멤버변수 Path와 인자로 받은 _String를 합친 경로를 새로 만들어 반환
	GameEnginePath GetPlusFileName(const std::string_view& _String);

	//이 파일에 있는 경로들을 벡터에 담아 리턴
	std::vector<GameEngineFile> GetAllFile(const std::string_view& _Ext = "");

protected:

private:
	GameEnginePath Path;
};

