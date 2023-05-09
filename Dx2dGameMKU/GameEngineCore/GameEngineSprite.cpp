#include "PrecompileHeader.h"
#include "GameEngineSprite.h"

GameEngineSprite::GameEngineSprite()
{

}

GameEngineSprite::~GameEngineSprite()
{

}

std::shared_ptr<GameEngineSprite> GameEngineSprite::LoadFolder(const std::string_view& _Path)
{
	GameEngineDirectory Dir = _Path;

	if (false == Dir.GetPath().IsDirectory())
	{
		MsgAssert("���丮�� �ƴ� ����Դϴ�. : \n" + std::string(_Path));
	}

	std::vector<GameEngineFile> AllFile = Dir.GetAllFile({ ".png", ".jpg" });

	if (0 >= AllFile.size())
	{
		MsgAssert("�̹����� �������� �ʴ� ����Դϴ�. : \n" + std::string(_Path));
	}

	std::string FileName = Dir.GetPath().GetFileName();
	std::shared_ptr<GameEngineSprite> NewSprite = GameEngineResource::Create(FileName);

	//TODO

	return NewSprite;
}
