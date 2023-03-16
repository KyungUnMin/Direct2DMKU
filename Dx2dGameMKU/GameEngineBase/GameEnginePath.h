#pragma once
#include <filesystem>

class GameEnginePath
{
public:
	friend class GameEngineFile;
	friend class GameEngineDirectory;

	GameEnginePath();
	GameEnginePath(std::filesystem::path _Path);
	GameEnginePath(const std::string& _Path);
	~GameEnginePath();

	GameEnginePath(const GameEnginePath& _Other);
	GameEnginePath(GameEnginePath&& _Other);
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;

	//멤버변수 Path의 말단경로만 반환
	std::string GetFileName() const;

	//멤버변수 Path를 string으로 변환하는 함수
	std::string GetPathToString() const;

	//상위 경로로 이동
	void MoveParent();

	//특정 경로가 존재할때 까지 상위폴더로 이동
	void MoveParentToChildPath(const std::string_view& _String);

	//멤버변수 Path가 유효한 경로인지 확인
	bool IsExists();

	//인자로 주어진 String과 멤버변수 Path를 더했을때의 경로가 유효한지 체크
	bool IsExistsToPlusString(const std::string_view& _String);

	// bool MoveParentToChildPath(const std::string_view& _IOName );

	//멤버변수 Path가 최상위 폴더인지 확인
	bool IsRoot();

	//현재 위치에서 인자로 주어진 자식경로로 이동
	bool Move(const std::string_view& _Path);

	//인자로 받은 string으로 주소를 설정
	void SetPath(const std::string_view& _Path);


protected:

private:
	std::filesystem::path Path;

};

